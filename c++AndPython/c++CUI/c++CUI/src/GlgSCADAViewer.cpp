#include "scada.h"
#include "menu_table.h"
#include "CWlbLogger.h"
#include <iostream>
#include "Dialog.cpp"
#include "AlarmDemo.h"
#include "GlgSCADAViewer.h"
//#include "GlgAlarmData.h"
//#include "Calibrations.h"

#define ERASE_DIALOG_ON_POPUP_MENU     0

// If set to 1, RemapTags() will be invoked to reassign tag sources
// programatically based on a custom application logic, if needed.
//
#define REMAP_TAGS   0

// Function prototypes
void PollTagData( GlgSCADAViewer * glg_viewer, GlgLong * timer_id );
void PollAlarms( GlgSCADAViewer * glg_viewer, GlgLong * timer_id);
static char * GetNewTagSource( CONST char * tag_name, CONST char * tag_source );
char * GetTime( void );

using namespace std;
/*----------------------------------------------------------------------
| Construction/Destruction
*/
GlgSCADAViewer::GlgSCADAViewer(void)
{
   UpdateInterval = 5000; 
   AlarmUpdateInterval = 3000; 
   TimerID = 0;
   AlarmTimerID = 0;
   TagRecordArray = NULL;
   MainMenuArray = NULL;
   NumTagRecords = 0;
   NumMainMenuItems = 0;
   PopupDialogVisible = false;
   ActivePopupMenuType = NO_POPUP_MENU;
   MainMenuIndex = -1;     // MainMenu selection, undefined
   SubMenuIndex = -1;      // SubMenu selection, undefined
   utility = 0;
   timer(0,&settimethread);
   //tempt.print();
}

 void GlgSCADAViewer::settimethread()
 {
      system( "./hensettime.x");
 }
 
 void GlgSCADAViewer::timer(int d,  void (*f)(void ))
 {

     std::thread([d,f](){
         std::this_thread::sleep_for(std::chrono::seconds(d));
         f();
     }).detach();
 }
 
/*----------------------------------------------------------------------
| 
*/
GlgSCADAViewer::~GlgSCADAViewer(void)
{
   /* Clear TagRecordArray. */
   DeleteTagRecords();
   delete utility;
   delete pDataFeed;
    system("pkill -9 hensettime.x");
}

/*----------------------------------------------------------------------

*/
void GlgSCADAViewer::Init( void )
{     
/////////////////////////////////////////////////
// clock functions
/////////////////////////////////////////////////
   pthread_t tid;
   pthread_attr_t attr;		
		
    /* Start up DDS middleware  */	
    pDataFeed = new CDataFeed();
    pDataFeed->InitializeDDS();

    /* Callbacks must be enabled before  hierarchy setup. */

   /* Input callback handles user interaction such as mouse clicks. */
   EnableCallback( GLG_INPUT_CB, NULL );

   /* Trace callback is used to process native events, such as F keys
      or Page Up/Down keys.
   */
   EnableCallback( GLG_TRACE_CB, NULL );
   
   /* Hierarchy callback is invoked when a new drawing 
      is loaded into the subwindow object. 
   */
   EnableCallback( GLG_HIERARCHY_CB, NULL );
   
   /* Store an object ID of the viewport named MainMenu, containing navigation
      buttons for the main menu.
   */
   MainMenu = GetResourceObject( "AreaTop/MainMenu" );
   AlarmDialog = GetResourceObject("AlarmDialog");  
   if( MainMenu.IsNull() )
     error( GLG_USER_ERROR, "MainMenu object not found", true /*exit*/);

   /* Store an object ID of the viewport named SubMenu, containing navigation
      buttons to switch drawings in the DrawingArea.
   */
   SubMenu = GetResourceObject( "AreaLeft/SubMenu" );
   if( SubMenu.IsNull() )
     error( GLG_USER_ERROR, "SubMenu object not found", true /*exit*/);

   /* Store object ID of the DrawingArea subwindow object. */
   DrawingArea = GetResourceObject( "DrawingArea" );
   DrawingArea.Init( this ); /* Initialize DrawingArea. */
     
   /* Object ID of the PopupDialog and PopupMenu viewports. */
   PopupDialog = GetResourceObject( "PopupDialog" );
   PopupDialog0 = GetResourceObject( "PopupDialog0" );

   PopupMenuTop = GetResourceObject( "PopupMenu" );
   PopupMenuDialog = PopupDialog.GetResourceObject( "PopupMenu" );
   if( PopupDialog.IsNull() || PopupDialog0.IsNull() || PopupMenuTop.IsNull() ||
       PopupMenuDialog.IsNull() )
     error( GLG_WARNING, "PopupDialog or PopupMenu objects not found", false );

   /* Object ID of the DrawingArea subwindow object inside PopupDialog or
      PopupMenu . */
   DrawingAreaDialog = PopupDialog.GetResourceObject( "DrawingArea" );
   DrawingAreaDialog0 = PopupDialog0.GetResourceObject( "DrawingArea" );

   DrawingAreaMenuTop = PopupMenuTop.GetResourceObject( "DrawingArea" );
   //GlgObject p = CopyObject((GlgObject)0);
   DrawingAreaMenuDialog = PopupMenuDialog.GetResourceObject( "DrawingArea" );

   DrawingAreaDialog.Init( this );
   DrawingAreaDialog0.Init( this );
   DrawingAreaMenuTop.Init( this );
   DrawingAreaMenuDialog.Init( this );

   /* Make PopupDialog and PopupMenu initially invisible. */
   PopupDialog.SetResource( "Visibility", 0. );
   PopupDialog0.SetResource( "Visibility", 0. );

   PopupMenuTop.SetResource( "Visibility", 0. );
   PopupMenuDialog.SetResource( "Visibility", 0. );

   PopupDialogVisible = false;
   ActivePopupMenuType = NO_POPUP_MENU;

   /* Make it a top-level dialog. */
   PopupDialog.SetResource( "ShellType", GLG_DIALOG_SHELL ); 
   PopupDialog0.SetResource( "ShellType", GLG_DIALOG_SHELL );


   utility = new Utility();
   utility->Init(this,&PopupDialog,&PopupDialog0);

   ControlIndicator = GetResourceObject("AreaTop/ControlIndicator");
   LogAllDataBasePointButton=GetResourceObject("AreaTop/LogAllDataButton");

   /* Store an object ID of the AlarmDialog viewport. */
   AlarmDialog = (GlgObjectC) GetResourceObject( "AlarmDialog" );
     
   AlarmList = 
     (GlgObjectC) AlarmDialog.GetResourceObject( "AlarmListVp/Table" );
     
   /* Make AlarmDialog initially invisible. */
   AlarmDialog.SetResource( "Visibility", 0. );
   
   /* Set title for the AlarmDialog. */
   AlarmDialog.SetResource( "ScreenName", "Alarm List" );

   /* Make it a top-level dialog. */
////   AlarmDialog.SetResource( "ShellType", GLG_DIALOG_SHELL ); 
   
   AlarmList.GetResource("NumRows",&Alarm_data->MaxNumberOfAlarmsInList); 
   PRINTF_VDT("MaxNumberOfAlarmsInList = %i\n", (int)Alarm_data->MaxNumberOfAlarmsInList); 

   Alarm_data->CGlgAlarmsInit(&AlarmDialog);
   HideBottomAlarmLine();
  
   /* Set the number of menu items. It must be done BEFORE hierarchy setup. */
   MainMenu.SetResource( "NumColumns", NumMainMenuItems );

//#define VDT_MSCC     20
//#define VDT_QTR_DECK 21
//#define VDT_ECCC_1   23
//#define VDT_ECCC_2   24
//#define VDT_ECCC_3   25
//CVdtPosition *VDTNumber
   int iVdtId;
   iVdtId = VDTNumber->GetVdtPosition();
   PRINTF_VDT("iVdtId = %i\n", iVdtId);
   if( (iVdtId != VDT_QTR_DECK) && (iVdtId != VDT_ECCC_1) &&
       (iVdtId != VDT_ECCC_2) && (iVdtId != VDT_ECCC_3))
     ControlIndicator.SetResource( "Visibility", 0. );  

   ControlIndicator.SetResource( "State", (double)0 );
   
   SetupHierarchy();
   
   /* Initialize the main menu. */
   InitMainMenu();
}

/*----------------------------------------------------------------------
| Initialize the main navigation menu, a viewport named "MainMenu".
*/
void GlgSCADAViewer::InitMainMenu()
{
   GlgObjectC button;
   char* button_name;

   /* Populate menu buttons based on the MainMenuArray. */
   for( int i=0; i<NumMainMenuItems; ++i )
   {
      button_name = GlgCreateIndexedName( (char*) "Button%", i );
      button = MainMenu.GetResourceObject( button_name );
      GlgFree( button_name );

      button.SetResource( "LabelString", MainMenuArray[ i ].label_string );
      //cout << MainMenuArray[ i ].label_string << endl;
      std::string str1(MainMenuArray[ i ].label_string);

      utility->InitUtilitiesData(str1,GlgObjectC(GlgObject(0)),i,1);

      button.SetResource( "TooltipString", MainMenuArray[ i ].tooltip_string );
   }

 //  SelectMainMenuItem( -1, 0, true );
   SelectMainMenuItem( 0, 0, true );
}

/*----------------------------------------------------------------------
| Initialize the SubMenu, based on the MainMenu selection. 
*/
void GlgSCADAViewer::InitSubMenu()
{
   GlgObjectC button;
   char* button_name;
   GlgLong num_submenu_items;
   SubMenuRecord * submenu_array;

   utility->ANALOG_STATUS_PAGE_NAME.clear();
   utility->DIGITAL_STATUS_PAGE_NAME.clear();

   utility->ReadPagesFromDB();

   if( MainMenuIndex != -1 )   
     num_submenu_items = MainMenuArray[ MainMenuIndex ].num_submenu_items;
   else
     num_submenu_items = 0;

   if( num_submenu_items )
   {
      submenu_array = MainMenuArray[ MainMenuIndex ].submenu_array;
      if( !submenu_array )
      {
	 error( GLG_USER_ERROR, "Null SubMenu array.", false );
	 num_submenu_items = 0;
      }
   }

   /* Set number of items (NumRows) in SubMenu */   
   SubMenu.SetResource( "NumRows", (double) num_submenu_items );
   
   if( num_submenu_items )
   {
      /* Re-set the menu handler to initialize it with the new number of 
	 items. */
      SubMenu.SuspendObject();
      SubMenu.ReleaseObject();

      /* Populate menu buttons in the SubMenu */
      for( int i=0; i<num_submenu_items; ++i )
      {
		 button_name = GlgCreateIndexedName( (char*) "Button%", i );
		 button = SubMenu.GetResourceObject( button_name );
		 GlgFree( button_name );

		 button.SetResource( "LabelString", submenu_array[ i ].label_string );
		 std::string str1(submenu_array[ i ].label_string);
         utility->InitUtilitiesData(str1,GlgObjectC(GlgObject(button)),i,2);
		 button.SetResource( "TooltipString", submenu_array[ i ].tooltip_string );
      }

      /* Show SubMenu */
      ShowSubMenu( true );
   }
   else
     /* Hide SubMenu */
     ShowSubMenu( false );
    
   /* Initialize SubMenu selection to -1 (undefined) */
   SelectSubMenuItem( 0, 0, true );
}

/*----------------------------------------------------------------------
| Select MainMenu item with a specified index.
*/
void GlgSCADAViewer::SelectMainMenuItem( GlgLong menu_index, GlgLong increment,
					 bool update_menu )
{
    if(PopupDialogVisible &&  utility->currentPopupDialog != 0)
    {
          /* utility->currentPopupDialog->CloseDialog(this,1,-1);
           PopupDialogVisible = false;
           utility->currentPopupDialog =0;*/
         utility->currentPopupDialog->mainMenuIndexPrevious = menu_index;
         if( utility->currentPopupDialog->type == UTILITY_PERMISSIONS)
         {
               MainMenu.SetResource( "SelectedIndex",utility->currentPopupDialog->mainMenuIndex);
         }
         else
         {
               MainMenu.SetResource( "SelectedIndex",-1);
         }
         SubMenu.SetResource( "SelectedIndex",-1);

    }
    else
    {
        if( increment )
        {
            menu_index += increment;

            /* Wrap around */
            if( menu_index >= NumMainMenuItems )
                menu_index = 0;
            else if( menu_index < 0 )
            menu_index = NumMainMenuItems - 1;
        }

        /* Check validity (if invoked with no increment). */
        if( menu_index < -1 || menu_index >= NumMainMenuItems )
        {
            error( GLG_WARNING, "Invalid main menu index.", false );
            MainMenuIndex = -1;
        }
        else
        MainMenuIndex = menu_index;
   
        if( update_menu )
            MainMenu.SetResource( "SelectedIndex", MainMenuIndex );

        /* Populate SubMenu based on the main menu selection. */
        InitSubMenu();
  
        //  SelectSubMenuItem( (GlgLong) menu_index, 0,
        //                     true /*don't update menu object*/ );
        SelectSubMenuItem( (GlgLong) 0, 0,
                      true /*don't update menu object*/ );
    }

}

/*----------------------------------------------------------------------
| Select SubMenu item with a specified index.
*/
void GlgSCADAViewer::SelectSubMenuItem( GlgLong menu_index, GlgLong increment,
					bool update_menu )
{

    if(PopupDialogVisible &&  utility->currentPopupDialog != 0)
    {
             utility->currentPopupDialog->subMenuIndexPrevious = menu_index;
             if(utility->currentPopupDialog->type == ADMINISTRATOR_PERMISSTIONS)
             {
                   SubMenu.SetResource( "SelectedIndex", utility->currentPopupDialog->subMenuIndex );
             }
             else
             {
                   SubMenu.SetResource( "SelectedIndex", -1);
             }
            //utility->currentPopupDialog->CloseDialog(this,2,-1);
            //PopupDialogVisible = false;
            //utility->currentPopupDialog =0;
    }
    else
    {
        GlgLong num_submenu_items;

        if( MainMenuIndex == -1 )
            num_submenu_items = 0;
        else
        {
            if( MainMenuIndex < -1 || MainMenuIndex >= NumMainMenuItems )
            {
                error( GLG_USER_ERROR, "Invalid main menu index.", false );
                    return;
            }
            num_submenu_items = MainMenuArray[ MainMenuIndex ].num_submenu_items;
        }

        if( increment )
        {
            menu_index += increment;

             /* Wrap around */
            if( menu_index >= num_submenu_items )
                menu_index = 0;
            else if( menu_index < 0 )
                menu_index = num_submenu_items - 1;
        }

        /* Check validity (if invoked with no increment). */
        if( menu_index < -1 || menu_index >= num_submenu_items )
        {
            error( GLG_WARNING, "Invalid submenu index.", false );
            SubMenuIndex = -1; /* unselect */
        }
        else
            SubMenuIndex = menu_index;
   
        if( update_menu )
            SubMenu.SetResource( "SelectedIndex", (double) SubMenuIndex );

        /* Load the drawing associated with the selected menu button and
        display it in the DrawingArea.
        */

        LoadDrawing();
    }
}

/*----------------------------------------------------------------------
| Show or hide the SubMenu.
*/
void GlgSCADAViewer::ShowSubMenu( bool show )
{
   if( SubMenu.IsNull() )
   {
      error( GLG_USER_ERROR, "Null SubMenu.", false );
      return;
   }

   /* Show or hide if changed. */
   SubMenu.SetResource( "Visibility", show ? 1. : 0., true );
}

/*----------------------------------------------------------------------
| GLG Input callback.
*/
class Security;
//
void GlgSCADAViewer::Input(GlgObjectC& viewport, GlgObjectC& message)
{
   CONST char
      * format,
      * action,
      * origin;
   GlgObjectC event_obj;
   double menu_index;
   double submenu_index;
   /* Get the message's format, action and origin. */
   //
   message.GetResource( "Format", &format );
   message.GetResource( "Action", &action );
   message.GetResource( "Origin", &origin );
      
 //  PRINTF_VDT("GlgSCADAViewer::Input, format = %s \n", format);
 //  PRINTF_VDT("GlgSCADAViewer::Input, action = %s \n", action);
 //  PRINTF_VDT("GlgSCADAViewer::Input, origin = %s \n", origin);
   
   event_obj = message.GetResourceObject( "Object" );
      //
   /* Handle events from the screen navigation menu, named "MainMenu" */

//
   if( strcmp( format, "Menu" ) == 0 &&
       strcmp( action, "Activate" ) == 0 )
   {
      /* Handle button selection in the MainMenu. */
      if( strcmp( origin, "MainMenu" ) == 0 )
        {

        //************* reset zoom here **********
        /* Reset zoom state for AreaLeft viewport containing SubMenu. */
	    viewport.SetZoom( "AreaLeft", 'n', 0. );

	    /* Retrieve menu selection and process it. */
	    message.GetResource( "SelectedIndex", &menu_index );
	    //SelectMainMenuItem( (GlgLong) menu_index, 0, false /*don't update menu object*/ );
        //************* reset zoom here **********
        utility->InitUtilitiesData("",GlgObjectC(GlgObject(0)),menu_index,3);
        }
		  /* Handle button selection in the SubMenu. Load and display
		 a corresponding .g file in the DrawingArea.
		  */
     else if( strcmp( origin, "SubMenu" ) == 0 )
       {
       /* Retrieve menu selection and process it. */
	   message.GetResource( "SelectedIndex", &menu_index );
	   //SelectSubMenuItem( (GlgLong) menu_index, 0, false /*don't update menu object*/ );	   
       message.GetResource( "SelectedIndex", &submenu_index );
       utility->InitUtilitiesData("",GlgObjectC(GlgObject(0)),submenu_index,4);
       }
   }

         if( strcmp( origin , "ControlIndicator" ) == 0 )
         {
         PRINTF_VDT("GlgSCADAViewer::Input, format = %s \n", origin);
         ProcessTakeCtrl();
         }
		 
         if( strcmp( origin , "AlarmDialog" ) == 0 )
         {
//         PRINTF_VDT("GlgSCADAViewer::Input, format = %s \n", origin);
//         ProcessTakeCtrl();
         }   
   /* Handle events from the GLG input objects, such as button.*/
   if( strcmp( format, "Button" ) == 0  &&
       strcmp( action, "Activate" ) == 0 )
   {
      /* Handle events from the Quit button.*/
      if( strcmp( origin , "QuitButton" ) == 0 )
        Quit();   /* Exit application */

      /* Handle events from tDrawingAreaDialog.Viewport.SetResource( "ScreenName", dialog_title );the AlarmList Button.*/
      else if( strcmp( origin , "AlarmsButton" ) == 0 )
         DisplayAlarmDialog();
      else if( strcmp( origin , "OffPageAlarmsButton" ) == 0 )
         OffPageAlarm( this ); 
      utility->ProcessInput((char *)"",origin, &DrawingArea);
	  
#if 0
      /* Handle events from Previous and Next navigation buttons. */
      else if( strcmp( origin , "PrevMainMenuItem" ) == 0 )
	SelectMainMenuItem( MainMenuIndex, -1, true /*update menu object */ );
      else if( strcmp( origin , "NextMainMenuItem" ) == 0 )
	SelectMainMenuItem( MainMenuIndex, +1, true );
      else if( strcmp( origin , "PrevSubMenuItem" ) == 0 )
	SelectSubMenuItem( SubMenuIndex, -1, true );
      else if( strcmp( origin , "NextSubMenuItem" ) == 0 )
	SelectSubMenuItem( SubMenuIndex, +1, true ); 
#endif
   }

   /* Handle window closing. May use viewport's name.*/
   else if( strcmp( format, "Window" ) == 0 &&
       strcmp( action, "DeleteWindow" ) == 0 )
   {
      if( event_obj.Same( AlarmDialog ) )
         CloseAlarmDialog();
      else if ( event_obj.Same( PopupDialog ) || event_obj.Same(PopupDialog0))
      {
          switch(utility->currentPopupDialog->type)
    	  {
    	      case UTILITY_PERMISSIONS:
    	      case ADMINISTRATOR_PERMISSTIONS:
    	      case USER_DEFINED_DIGITAL:
    	      case USER_DEFINED_ANALOG:
                  utility->currentPopupDialog->CloseDialog(this,0,-1);
                  //utility->currentPopupDialog = 0;

    	      break;
    	      default:
    	    	  ClosePopupDialog();
    	    	  break;
    	  };

      }
      else if( event_obj.Same( viewport ) ) /* Exit application */
        Quit();
   }

   /* Make changes visible. */
   viewport.Update();
}

#define TEXT_BUFFER_LENGTH  32

/*----------------------------------------------------------------------
| GLG Trace callback to handle low-level window system events.
*/
void GlgSCADAViewer::Trace( GlgObjectC& callback_viewport, 
                            GlgTraceCBStruct * trace_info )
{
   XEvent * event;
   KeySym keysym;
   XComposeStatus status;
   char buf[ TEXT_BUFFER_LENGTH ];
   int length;

   event = trace_info->event;

   switch( event->type )
   {
    default: break;
	 
    case KeyPress:
      /* Using XLookupString instead of XLookupKeysym to properly handle
         Shift. */
      length = XLookupString( &event->xkey, buf, TEXT_BUFFER_LENGTH,
                              &keysym, &status );
      buf[ length ] = '\0';
      PRINTF_VDT("GlgSCADAViewer::Trace, keysym = %i \n", keysym);

      switch( keysym )
      {
       case XK_a:
         printf( "Pressed: a\n" );
         break;

       case XK_A:
         printf( "Pressed: A\n" );
         break; 

       case XK_Escape:
         DisplayBeforeOffPageAlarm( this );  
		 
         break; 
       case XK_Return:
         utility->ProcessEnter();
          break;
       case XK_Page_Up:

         utility->PageUp();
         break; 
    
       case XK_Page_Down:

          utility->PageDown();
         break; 
       case XK_Up:

         utility->PageErrowUp();
          break;
       case XK_Down:

          utility->PageErrorDown();
          break;
       case XK_Left:
           utility->PageErrorLeft();
          break;
       case XK_Right:
           utility->PageErrorRight();
          break;
       case XK_F1:
         AckAlarmFromList( this );
         break; 
       case XK_F2:
         printf( "Pressed: F2\n" );
         break; 
       case XK_F3:
         PRINTF_VDT("GlgSCADAViewer::Trace, Pressed F3 \n");       	       
//         DisplayAlarmDialog(); 
         OffPageAlarm( this );
         break;
       case XK_F12:
           PRINTF_VDT("GlgSCADAViewer::Trace, Pressed F12 \n");       	       
           SelectMainMenuItem( 0, 0,true );
           SelectSubMenuItem( SubMenuIndex, 0,true );
         break;         
      }
   }
}

/*----------------------------------------------------------------------
| Hierarchy callback. It is added to the control and invoked when a 
| new drawing is loaded into any subwindow object displayed in the control.
*/
void GlgSCADAViewer::Hierarchy( GlgObjectC& callback_viewport, 
				GlgHierarchyCBStruct * hierarchy_info )
{
   /* Handle events only for the DrawingArea, DrawingAreaDialog and
      DrawingAreaMenu subwindow objects.
   */
   if( hierarchy_info->object != DrawingArea &&
       hierarchy_info->object != DrawingAreaDialog &&
       hierarchy_info->object != DrawingAreaDialog0 &&
       hierarchy_info->object != DrawingAreaMenuTop && 
       hierarchy_info->object != DrawingAreaMenuDialog )
     return;
   
   /* This callback is invoked twice: one time before hierarchy setup
      for the new drawing, and the second time after hierarchy setup.
   */
   switch( hierarchy_info->condition )
   {
    case GLG_BEFORE_SETUP_CB:
      if( !hierarchy_info->subobject )
	break; /* Drawing loading error, will be reported in LoadDrawing */
      
      /* Enable Input callback for the new viewport loaded into the subwindow.
       */
      if( hierarchy_info->object == DrawingArea )
        DrawingArea.EnableCallback( GLG_INPUT_CB, hierarchy_info->subobject );

      else if( hierarchy_info->object == DrawingAreaDialog )
      {
        DrawingAreaDialog.EnableCallback( GLG_INPUT_CB, 
                                          hierarchy_info->subobject );
      }
      else if( hierarchy_info->object == DrawingAreaDialog0 )
      {
        DrawingAreaDialog0.EnableCallback( GLG_INPUT_CB,
                                          hierarchy_info->subobject );
      }

      else if( hierarchy_info->object == DrawingAreaMenuTop )
        DrawingAreaMenuTop.EnableCallback( GLG_INPUT_CB, 
                                           hierarchy_info->subobject );

      else if( hierarchy_info->object == DrawingAreaMenuDialog )
        DrawingAreaMenuDialog.EnableCallback( GLG_INPUT_CB, 
                                              hierarchy_info->subobject );
      break;

    case GLG_AFTER_SETUP_CB:
    default:
      break;
   }
}

/*----------------------------------------------------------------------
| Load a new drawing and display it in the Subwindow object
| (DrawingArea). Rebuild TagRecordsArray to include tag
| information for the newly loaded drawing.
*/
bool GlgSCADAViewer::LoadDrawing()
{
   CONST char * drawing_name;
   CONST char * drawing_title;

   if( MainMenuIndex == -1 || SubMenuIndex == -1 )
   {
      drawing_name = "empty_drawing.g";
      drawing_title = "";
   }
   else
   {
     drawing_name = 
       MainMenuArray[ MainMenuIndex ].submenu_array[ SubMenuIndex ].drawing_name;

     if( drawing_name == NULL )
       return false;

     drawing_title = 
       MainMenuArray[ MainMenuIndex ].submenu_array[ SubMenuIndex ].drawing_title;
   }
   ClosePopupDialog();  // Close PopupDialog if it is visible.
   HidePopupMenu();     // Erase previous drawing's popups, if any.

   /* Set new TitleString */
/*   if( drawing_title )
     SetResource( "AreaBottom/TitleString", drawing_title );
  */  
   /* Assign a new drawing name to the subwindow object DrawingArea.  */
   if( !DrawingArea.LoadDrawing( drawing_name ) )
   {
      DeleteTagRecords();   // Delete tags of the previous drawing.
      return false;
   }

   /* Initialize loaded drawing. */
   DrawingArea.InitDrawing();


   utility->DisplayPages((int)MainMenuIndex,(int)SubMenuIndex);


   /* Query a list of tags using a newly loaded drawing and build a new
      TagRecordsArray.
   */
   QueryTags( *this );
   
   return true;
}

/*----------------------------------------------------------------------
|  Query tags for a given viewport.
*/
void GlgSCADAViewer::QueryTags( GlgObjectC& drawing_vp )
{
   if( drawing_vp.IsNull() )
      return;
   
#if REMAP_TAGS
   /* Reassign tag sources if needed. */
   RemapTags( drawing_vp );
#endif   

   /* Delete existing tag records from TagRecordArray */
   DeleteTagRecords();
   
   /* Build TagRecordArray, an array of tag records containing 
      tags information. TagRecordArray will be used for data animation.
   */
   CreateTagRecords( drawing_vp );
}

/*--------------------------------------------------------------------
| Create an array of tag records containing tag information.
*/
void GlgSCADAViewer::CreateTagRecords( GlgObjectC& drawing_vp )
{
   GlgObjectC 
      tag_list,
      tag_obj;
   CONST char
     * tag_source,
     * tag_name,
     * tag_comment;
   int
      i,
      size;
   double dtype;
   
   /* Obtain a list of tags with unique tag sources. */
   tag_list = 
     drawing_vp.CreateTagList( /* List each tag source only once */ true );

   /* CreateTagList creates an object (a group containing a list of tags).
      The returned object has to be explicitly dereferenced to prevent a 
      memory leak. The object is still referenced by the tag_list variable 
      instance.
   */
   tag_list.Drop();

   if( tag_list.IsNull() )
      return;   
   
   size = tag_list.GetSize();
   if( !size )
      return; /* no tags found */
   
   TagRecordArray = 
     (GlgTagRecord **) GlgAlloc( sizeof( GlgTagRecord *) * size );
   
   for( i=0; i<size; ++i )
   {
      tag_obj = tag_list.GetElement( i );
      
      /* Retrieve TagSource attribute from the tag object.
	 TagSource represents the data source variable used 
	 for data animation.
      */
      tag_obj.GetResource( "TagSource", &tag_source );
      tag_obj.GetResource( "TagName", &tag_name );
      tag_obj.GetResource( "TagComment", &tag_comment );     
 // printf("TagSource = %s, TagName = %s, TagComment = %s\n", 
 // 	  tag_source, tag_name, tag_comment);  
       if( !tag_source || !*tag_source ||
//	  strcmp( tag_source, "unset") == 0 )
	  strcmp( tag_source, "unset") == 0 || 
	  ( tag_comment && strcmp (tag_comment, "Write" ) == 0 ) )
	 /* Skip empty tag sources and tag sources with a 
	    keyword "unset".
	 */
	 continue; 
      
      /* Get tag object's data type: GLG_D, GLG_S or GLG_G */
      tag_obj.GetResource( "DataType", &dtype );
      
      /* Create a new tag record. */
      GlgTagRecord * tag_record = new GlgTagRecord();
      tag_record->tag_source = GlgStrClone( (char*) tag_source );
      tag_record->tag_name = GlgStrClone( (char*) tag_name );
      tag_record->data_type = (int) dtype;
      tag_record->tag_obj = tag_obj;
      
      /* Add a new tag record to TagRecordArray */
      TagRecordArray[ NumTagRecords ] = tag_record;
      ++NumTagRecords; 
   }
   
   if( !NumTagRecords )
   {
      GlgFree( TagRecordArray );
      TagRecordArray = NULL;
   }
}

/*-----------------------------------------------------------------------
| Clear TagRecordArray
*/
void GlgSCADAViewer::DeleteTagRecords()
{
   if( !NumTagRecords )
      return;

   /* Free memory for the array elements  */
   for( int i = 0; i < NumTagRecords; ++i )
      delete TagRecordArray[i];
   
   /* Free memory allocated for the TagRecordArray */
   GlgFree( TagRecordArray );
   
   TagRecordArray = NULL;
   NumTagRecords = 0;
}


/*----------------------------------------------------------------------
| Display AlarmDialog containing a scrolling list of application
| alarms.
*/
void GlgSCADAViewer::DisplayAlarmDialog()
{
   double dAlarmDialogVisibility;
   int    iToggle;
   AlarmDialog.GetResource( "Visibility", &dAlarmDialogVisibility );
   PRINTF_VDT("dAlarmDialogVisibility = %i\n", (int)dAlarmDialogVisibility);   
   iToggle = (int)dAlarmDialogVisibility;
   iToggle ^= 1;
   dAlarmDialogVisibility = iToggle;
   AlarmDialog.SetResource( "Visibility", dAlarmDialogVisibility );
   AlarmDialog.GetResource( "Visibility", &dAlarmDialogVisibility );
   PRINTF_VDT("dAlarmDialogVisibility = %i, iToggle = %i\n", 
   	      (int)dAlarmDialogVisibility, iToggle);      
}

/*----------------------------------------------------------------------
| Close AlarmDialog.
*/
void GlgSCADAViewer::CloseAlarmDialog()
{
   AlarmDialog.SetResource( "Visibility", 0. );
}

// Processes custom command with CommandType="PopupMenu":
// configures, positions and shows popup menu.
// The drawing_area parameter is the drawing area containing the 
// selected object.
//
void GlgSCADAViewer::DisplayPopupMenu( GlgDrawingArea * drawing_area,
                                       GlgObjectC& selected_obj,
                                       GlgObjectC& command_obj )
{
   GlgObjectC menu_vp, fill_color_obj;
   GlgDrawingArea * menu_drawing_area;
   GlgObjectC * popup_menu;
   MenuLocation new_popup_menu_type;
   CONST char
     * menu_drawing,
     * menu_title = "";

   int iVdtId;
   iVdtId = VDTNumber->GetVdtPosition();
   PRINTF_VDT("DisplayPopupMenu iVdtId = %i\n", iVdtId);
   if( (iVdtId != VDT_QTR_DECK) && (iVdtId != VDT_ECCC_1) &&
       (iVdtId != VDT_ECCC_2) && (iVdtId != VDT_ECCC_3))
     return;

   double dmode;
   dmode =  selected_obj.GetResource("Mode",  &dmode);
   PRINTF_VDT("DisplayPopupMenu dmode = %i\n", (int)dmode); 
   if( dmode == int(0) )
     return;
   
   double dtype;
   ControlIndicator.GetResource( "State", &dtype );
   PRINTF_VDT("DisplayPopupMenu dtype = %i\n", (int)dtype);
   if( (dtype == (int)0) ||  (dtype == (int)2) ) // VDT not in Control, do not display Popup
     return; 
 
    if( drawing_area->Same( DrawingAreaDialog ) )
   {
      new_popup_menu_type = DIALOG_POPUP_MENU;
      menu_drawing_area = &DrawingAreaMenuDialog;
      popup_menu = &PopupMenuDialog;
   }
   else
   {
      new_popup_menu_type = TOP_POPUP_MENU;
      menu_drawing_area = &DrawingAreaMenuTop;
      popup_menu = &PopupMenuTop;
   }   
  
#if ERASE_DIALOG_ON_POPUP_MENU
   if( new_popup_menu_type == TOP_POPUP_MENU )
     ClosePopupDialog();   // Close popup dialog if visible.
#endif

   // Hide previous popup menu if it is of a different type 
   // (in a different viewport).   
   if( ActivePopupMenuType && new_popup_menu_type != ActivePopupMenuType )
     HidePopupMenu();

   // Obtain popup menu name.
   if( !command_obj.GetResource( "MenuDrawing", &menu_drawing ) )
   {
      error( GLG_USER_ERROR, "MenuDrawing resource is missing", false );
      ActivePopupMenuType = NO_POPUP_MENU;
      return;
   }
 
   if( !menu_drawing || !*menu_drawing ) // MenuDrawing is unset.
   {
      ActivePopupMenuType = NO_POPUP_MENU;
      return;
   }
  
   ActivePopupMenuType = new_popup_menu_type;

   if( !menu_drawing_area->LoadDrawing( menu_drawing ) )
     return;

   menu_drawing_area->InitDrawing();

   // Configure popup menu, by setting its parameters as needed.
   command_obj.GetResource( "MenuTitle", &menu_title );
   ConfigurePopupMenu( menu_drawing_area->Viewport, selected_obj,
   	               command_obj, menu_title );

 //   // DEBUG START
 //  CONST char* tag0, *tag1;
 //  menu_drawing_area->Viewport.GetResource( "Tag0", &tag0 );
 //  menu_drawing_area->Viewport.GetResource( "Tag1", &tag1 );
 //  printf( "popup info: tag0 = %s  tag1 = %s\n", tag0, tag1 );
 //  // DEBUG END


   // Position the popup.
   PositionPopupMenu( selected_obj );    

   // Set the fill color of the popup menu container to match the fill color
   // of the loaded popup menu to decrease flickering.
   //
   fill_color_obj = 
     menu_drawing_area->Viewport.GetResourceObject( "FillColor" );
   popup_menu->SetResource( "FillColor", fill_color_obj, true );  

   // Update position and fill color before making the popup visible to avoid
   // flickering.
   popup_menu->SetupHierarchy(); 

   popup_menu->SetResource( "Visibility", 1. );
   popup_menu->Update();
}

enum PopupType
{
   MENU_POPUP = 1,
   SPINNER_POPUP = 2,
   PASSWORD_POPUP = 3
};

// Configures popup menu with name menu_name.
//
void GlgSCADAViewer::ConfigurePopupMenu( GlgObjectC& menu_vp, 
                                         GlgObjectC& selected_obj, 
                                         GlgObjectC& command_obj,
                                         CONST char * menu_title )
{
   CONST char
     * menu_widget_type,
     * data_var,
     * menu_name,
     * tag_source;

    char * res_name1, * res_name2;
   
   PopupType popup_type;
   double value;
   int num_menu_tags;

   if( menu_vp.IsNull() )
     return;

   // Retrieve WidgetType of the popup menu.
   menu_vp.GetResource( "WidgetType", &menu_widget_type );

   if( strcmp( menu_widget_type, "PopupMenu2" ) == 0)
     num_menu_tags = 2;

   if( strcmp( menu_widget_type, "PopupMenu3" ) == 0)
     num_menu_tags = 3;

   if( strcmp( menu_widget_type, "PopupMenu2" ) == 0 ||
       strcmp( menu_widget_type, "PopupMenu3" ) == 0 )
     popup_type = MENU_POPUP;
   else if( strcmp( menu_widget_type, "PopupSpeedSpinner" ) == 0 ||
            strcmp( menu_widget_type, "PopupValueSpinner" ) == 0 )
     popup_type = SPINNER_POPUP;
   else
   {
      error( GLG_USER_ERROR, "Unknown popup menu type.", false );
      return;
   }

   // Assign menu parameters from the corresponding parameters 
   // of the selected object.
   switch( popup_type )
   {
    case MENU_POPUP:
     for( int i=0; i<num_menu_tags; ++i )
       {
       res_name1 = GlgCreateIndexedName( (char *) "Tag%", i);
       res_name2 = GlgConcatResNames( res_name1, (char *)"TagSource");
       command_obj.GetResource( res_name2, &tag_source );
       menu_vp.SetResource( res_name1, tag_source );
       PRINTF_VDT("res_name1 = %s, res_name2 = %s, tag_source = %s\n", 
       res_name1, res_name2, tag_source);    	
       GlgFree( (void *)res_name1 );
       GlgFree( (void *)res_name2 );      	
      }
      break;

    case SPINNER_POPUP:
      selected_obj.GetResource( "Value/TagSource", &data_var );
      
      // Set spinner's initial value from the selected object.
      selected_obj.GetResource( "Value", &value );
      menu_vp.SetResource( "Value", value );
      // Assign menu parameters from the selected valve object.
      menu_vp.SetResource( "DataVar", data_var );
      //cout << "SPINNER_POPUP Value/TagSource = "<< data_var << " Value = " << value << endl;
      break;

    default: error( GLG_USER_ERROR, "Unknown popup menu type.", false ); break;
   }

   menu_vp.SetResource( "Title/String", menu_title ? menu_title : "" );

}

// Positions popup menu embedded into the loaded drawing.
//
void GlgSCADAViewer::PositionPopupMenu( GlgObjectC& selected_obj )
{
   GlgObjectC 
     popup_menu,      // Popup menu container.
     selected_obj_vp, // Viewport that contains selected object.
     menu_vp,         // Viewport of the popup menu.
     parent_vp;       // Parent viewport that contains the popup menu.
   GlgCube
     * sel_obj_box,
     converted_box;
   double 
     x, y,
     offset = 5., // offset in pixels.
     menu_width, menu_height,
     parent_width, parent_height;
   int x_anchor, y_anchor; 
   
   selected_obj_vp = GlgGetParentViewport( selected_obj );
   if( ActivePopupMenuType == DIALOG_POPUP_MENU )     
   {
      menu_vp = DrawingAreaMenuDialog.Viewport;
      popup_menu = PopupMenuDialog;
      parent_vp = DrawingAreaDialog.Viewport;    // parent of the popup menu 
   }
   else    // TOP_POPUP_MENU
   {
      menu_vp = DrawingAreaMenuTop.Viewport;
      popup_menu = PopupMenuTop;
      parent_vp = this;      // parent of the popup menu
   }

   // Obtain the object's bounding box in screen coordinates.
   sel_obj_box = selected_obj.GetBoxPtr();   

   // Convert screen coordinates of the selected object box
   // from the viewport of the selected object to the viewport
   // that contains the popup menu.
   converted_box = *sel_obj_box;
   GlgTranslatePointOrigin( selected_obj_vp, parent_vp, &converted_box.p1 );
   GlgTranslatePointOrigin( selected_obj_vp, parent_vp, &converted_box.p2 );

   parent_vp.GetResource( "Screen/Width", &parent_width );
   parent_vp.GetResource( "Screen/Height", &parent_height );

   menu_vp.GetResource( "Width", &menu_width );
   menu_vp.GetResource( "Height", &menu_height );

   popup_menu.SetResource( "Width", menu_width );
   popup_menu.SetResource( "Height", menu_height );

   // Position the popup at the upper right or lower left corner of 
   // the selected object, if possible. Otherwise (viewport is too small), 
   // position it in the center of the viewport.
   //   
   if( converted_box.p2.x + menu_width > parent_width )
   {
      // Outside of window right edge.
      // Position right edge of the popup to the left of the selected object.
      // Always use GLG_HLEFT anchor to simplify out-of-the-window check.
      //
      x =  converted_box.p1.x - offset - menu_width;
      x_anchor = GLG_HLEFT;
   }
   else 
   {
      // Position left edge of the popup to the right of the selected object.
      x = converted_box.p2.x + offset; 
      x_anchor = GLG_HLEFT;
   }

   // Anchor is always GLG_HLEFT here to make checks simpler.
   if( x < 0 || x + menu_width > parent_width )
   {
      // Not enough space: place in the center.
      x = parent_width / 2.;
      x_anchor = GLG_HCENTER;
   }

   if( converted_box.p1.y - menu_height < 0. ) 
   {
      // Outside of window top edge.
      // Position the top edge of the popup below the selected object.
      y =  converted_box.p2.y + offset;
      y_anchor = GLG_VTOP;
   }
   else 
   {
      // Position bottom edge of the popup above the selected object.
      // Always use GLG_VTOP achor to simplify out-of-the-window check.
      //
      y = converted_box.p1.y - offset - menu_height; 
      y_anchor = GLG_VTOP;
   }

   // Anchor is always GLG_VTOP here to make checks simpler.
   if( y < 0 || y + menu_height > parent_height )
   {
      // Not enough space: place in the center.
      y = parent_height / 2.;
      y_anchor = GLG_HCENTER;
   }

   popup_menu.PositionObject( GLG_SCREEN_COORD, x_anchor | y_anchor, x, y, 0. );
}
   
// Erases the active popup menu.
//

// put code in here to not use DataVar
void GlgSCADAViewer::HidePopupMenu()
{
   CONST char * menu_widget_type;
   char * res_name;
   int num_menu_tags;      
   GlgObjectC menu_vp;
   GlgObjectC menu_obj;
      
   if( !ActivePopupMenuType )
     return;
    
   if( ActivePopupMenuType == TOP_POPUP_MENU )
   {
     menu_vp = DrawingAreaMenuTop.Viewport;
     menu_obj = PopupMenuTop;
   }
   else
   {
     menu_vp = DrawingAreaMenuDialog.Viewport;
     menu_obj = PopupMenuDialog;
   }

   if( menu_vp.IsNull() )
     return;
   
   // Retrieve WidgetType of the popup menu.
   menu_vp.GetResource( "WidgetType", &menu_widget_type );     
 
   DEBUGF_VDT("HidePopupMenu: menu_widget_type = %s\n", menu_widget_type);
   
   if( strcmp( menu_widget_type, "PopupMenu2" ) == 0)
     num_menu_tags = 2;

   if( strcmp( menu_widget_type, "PopupMenu3" ) == 0)
     num_menu_tags = 3;

   DEBUGF_VDT("HidePopupMenu: num_menu_tags = %i\n", num_menu_tags); 

   for( int i=0; i<num_menu_tags; ++i )
   {
       res_name = GlgCreateIndexedName( (char *) "Tag%", i);
       menu_vp.SetResource( (CONST char*) res_name, "unset" );
       GlgFree( (void *)res_name ); 
   } 
   
   menu_obj.SetResource( "Visibility", 0. );
   menu_obj.Update();
   ActivePopupMenuType = NO_POPUP_MENU;
}   

/*----------------------------------------------------------------------
| Processes custom command with CommandType="PopupDialog":
*/
void GlgSCADAViewer::DisplayPopupDialog( GlgObjectC& selected_obj,
                                         GlgObjectC& command_obj )
{
   CONST char
     * drawing_name,
     * dialog_title = "";   

   HidePopupMenu();    // Erase active popup menu, if any

   if( !command_obj.GetResource( "DialogDrawing", &drawing_name ) )
   {
      error( GLG_USER_ERROR, "Missing PopupDrawingName resource", false );
      return;
   }

   if( !drawing_name || !*drawing_name ) // DialogDrawing is unset
     return;

   if( !DrawingAreaDialog.LoadDrawing( drawing_name ) )
     return;

   DrawingAreaDialog.InitDrawing();

   command_obj.GetResource( "DialogTitle", &dialog_title );
   DrawingAreaDialog.Viewport.SetResource( "ScreenName", dialog_title );

   /* Rebuild TagRecordArray to include tags both for the
      drawing displayed in the main drawing area and drawing 
      displayed in the popup dialog.
   */
   QueryTags( *this );

   /* Poll new data to fill the popup dialog with current values. */
   UpdateData();

   // Set the fill color of the popup menu container to match the fill color
   // of the loaded popup menu to decrease flickering.
   //
   GlgObjectC fill_color_obj;
   fill_color_obj = DrawingAreaDialog.Viewport.GetResourceObject( "FillColor" );
   PopupDialog.SetResource( "FillColor", fill_color_obj, true );  
   // Update fill color before making ithe dialog visible to avoid flickering.
   PopupDialog.SetupHierarchy();

   /* Display the popup dialog if it is not up already. */
   PopupDialog.SetResource( "Visibility", 1., true );
   PopupDialogVisible = true;

   PopupDialog.Update();
}

/*----------------------------------------------------------------------
| Close PopupDialog.
*/
void GlgSCADAViewer::ClosePopupDialog()
{
   if( !PopupDialogVisible )
     return;

   /* Make PopupDialog invisible */
   PopupDialog.SetResource( "Visibility", 0. );
   PopupDialogVisible = false;
   PopupDialog.Update();   // Erase before setting an empty drawing.

   /* Destroy the drawing displayed in a subwindow. */
   DrawingAreaDialog.LoadDrawing( "empty_drawing.g" );

   /* Rebuild a list of tags to exclude the tags from the PopupDialog. */
   QueryTags( *this );

   // Hide popup menu that may be active in the dialog.
   if( ActivePopupMenuType == DIALOG_POPUP_MENU )
     HidePopupMenu();
}

/*----------------------------------------------------------------------
| Start dynamic updates.
*/
void GlgSCADAViewer::StartUpdates()
{
   /* Start update timer. */
   TimerID = GlgAddTimeOut( AppContext, UpdateInterval, 
			    (GlgTimerProc)PollTagData, this );

   AlarmTimerID = GlgAddTimeOut( AppContext, AlarmUpdateInterval, 
				 (GlgTimerProc)PollAlarms, this );
}

/*----------------------------------------------------------------------
| Stop dynamic updates.
*/
void GlgSCADAViewer::StopUpdates()
{
   /* Stop update timers */
   if( TimerID )
   {
      GlgRemoveTimeOut( TimerID );
      TimerID = 0;
   }

   if( AlarmTimerID )
   {
      GlgRemoveTimeOut( AlarmTimerID );
      AlarmTimerID = 0;
   }
}

/*----------------------------------------------------------------------
| Animates the drawing. 
*/
void PollTagData( GlgSCADAViewer* glg_viewer, GlgLong * timer_id )
{
   if( glg_viewer->NumTagRecords )
     glg_viewer->UpdateData();
   
   /* Reinstall the timeout to continue updating.
      Reinstall even if no tags to keep the timer going: the next loaded 
      drawing may have tags, need to keep updating. Most SCADA drawings 
      will have tags anyway.
   */
   glg_viewer->TimerID =
     GlgAddTimeOut( glg_viewer->AppContext, glg_viewer->UpdateInterval, 
                    (GlgTimerProc)PollTagData, glg_viewer );
}

/*----------------------------------------------------------------------
| Traverses the array of tag records, 
| gets new data for each tag and updates the drawing with new values.
*/
void GlgSCADAViewer::UpdateData()
{
   GlgTagRecord * tag_record;
   double d_value;
   CONST char * s_value;
   //cout << "Number of Tag Records = "<< NumTagRecords << endl;
   if( !NumTagRecords )
     return;
	 
/*
   // Read all datapoints from DDS
   pDataFeed->ReadDataPoints();
*/
   if(MainMenuIndex == utility->ptrDialogs[1]->mainMenuIndex || MainMenuIndex == utility->ptrDialogs[2]->mainMenuIndex)
     { 
     utility->UpdateUserPages(MainMenuIndex,SubMenuIndex);
     }
   else
     {
     for( int i=0; i < NumTagRecords; ++i )
       {
       tag_record = TagRecordArray[ i ];
					 
       switch( tag_record->data_type )
         {
         case GLG_D:
           /* Get random data value in the range (0,1) */

           d_value = GetDTagData( tag_record );
						
           /* Push a new data value into a given tag. The last argument 
              indicates whether or not to set the value depending if the 
              value has changed. If set to true, push the value only if 
              it has changed. Otherwise, a new value is always pushed 
              into the object.*/
          // if(MainMenuIndex == utility->menues[3][0]->mainMenuIndex)
            // {
                utility->ProcessTags(this,tag_record,d_value,false,i,static_cast<int>(NumTagRecords));
            // }
          // else
             //{
                SetTag( tag_record->tag_source, d_value, false );
            // }
           break;
           
        case GLG_S:         
          s_value = GetSTagData( tag_record );
          SetTag( tag_record->tag_source, s_value, false );
          break;
      }
   }
}
/*
   // Return memory loaned from DDS
   pDataFeed->ReturnMemory();
*/
    
   /* Update the drawing with new data if it has tags. */
   Update();
   Sync();
}

/*----------------------------------------------------------------------
| Polls for alarms and displays them in the alarm dialog.
*/
void PollAlarms( GlgSCADAViewer* glg_viewer, GlgLong * timer_id )
{
   glg_viewer->GetAlarms();

   // Reinstall the timeout to continue updating. 
   glg_viewer->AlarmTimerID = 
     GlgAddTimeOut( glg_viewer->AppContext, 
		    glg_viewer->AlarmUpdateInterval, 
		    (GlgTimerProc)PollAlarms, glg_viewer );
}

/*----------------------------------------------------------------------
| Queries new D tag value from the database.
*/
double GlgSCADAViewer::GetDTagData( GlgTagRecord * tag_record )
{
    double value;
#if RANDOM_DEMO_DATA
//printf("GetDTagData: tag_record->tag_source, tag_record->tag_name Random = %s, %s\n",tag_record->tag_source, tag_record->tag_name);
   if( strstr( tag_record->tag_name, "Valve" ) ||
            strstr( tag_record->tag_name, "Breaker" ) )
     return GlgRand( 0., 1. ) > 0.5;     /* Valve or breaker state data. */

   else if( strstr( tag_record->tag_name, "State" ) )
     return GlgRand( 0., 4. );           /* Discrete state display widgets. */

   else if( strstr( tag_record->tag_name, "Speed" ) )
     return GlgRand( 0., 4. );           /* Propeller speed data. */

   else
     return GlgRand( 0., 200. );
#else
//printf("GetDTagData: tag_record->tag_source, tag_record->tag_name Production = %s, %s \n", tag_record->tag_source, tag_record->tag_name);
int nPage;
nPage = (MainMenuIndex * 100) + SubMenuIndex;
//printf("GetDTagData: %s/%i\n", tag_record->tag_source, nPage);
   if( !pDataFeed->ReadDBValueD( tag_record, &value ) )
   {
      ERRORF_DATABASE("GlgSCADAViewer::GetDTagData: Fail to read D tag: tag_record->tag_source %s\n", tag_record->tag_source);   
      errorS( GLG_USER_ERROR, "Fail to read D tag: ", tag_record->tag_source,
              false );
     return 0.;
   }
   PRINTF_DATABASE("GetDTagData: tag_record->tag_source, tag_record->tag_name DDS = [%s], [%s], %f\n", tag_record->tag_source, tag_record->tag_name, value);   
   if( strcmp(tag_record->tag_source, "VdtInCtrl") == 0 )
     ProcessInCtrl();
   return value;
#endif
}

/*----------------------------------------------------------------------
| Queries new S tag value from the database.
*/
CONST char * GlgSCADAViewer::GetSTagData( GlgTagRecord * tag_record )
{   
#if RANDOM_DEMO_DATA
//printf("GetSTagData: tag_record->tag_source, tag_record->tag_name Random = %s, %s\n", tag_record->tag_source, tag_record->tag_name);
   return ( GlgRand( 0., 1. ) > 0.5 ? "On" : "Off" );
#else

   char * string_ptr = NULL;
//printf("GetSTagData: tag_record->tag_source, tag_record->tag_name Production = %s, %s \n", tag_record->tag_source, tag_record->tag_name);
int nPage;
nPage = (MainMenuIndex * 100) + SubMenuIndex;
//printf("GetSTagData: %s/%i\n", tag_record->tag_source, nPage);
   if( !pDataFeed->ReadDBValueS( tag_record, string_ptr ) )
   {
      ERRORF_DATABASE("GlgSCADAViewer::GetSTagData: Fail to read S tag: tag_record->tag_source %s\n", tag_record->tag_source);
      errorS( GLG_USER_ERROR, "Fail to read S tag: ", tag_record->tag_source,
              false );
      return "";
   }
  PRINTF_DATABASE("GetSTagData: tag_record->tag_source, tag_record->tag_name DDS = [%s], [%s], [%s]\n", tag_record->tag_source, tag_record->tag_name, string_ptr);
   return string_ptr;
#endif
}

/*----------------------------------------------------------------------
| Queries alarm data from the controlled process, uses simulated alarms
| for the demo.
*/
void GlgSCADAViewer::GetAlarms()
{
#if RANDOM_ALARM_DEMO_DATA
   GetDemoAlarms( this );
#else
   GetAlarmList( this );
#endif

   DisplayAlarmList( this );
}

#define RESET_THRESHOLD   0.7
#define RAISE_THRESHOLD   0.8

#if RANDOM_ALARM_DEMO_DATA
void GlgSCADAViewer::GetDemoAlarms( GlgSCADAViewer * scada_viewer )
{
  CGlgAlarmData *AlarmDataRecord;
  CGlgAlarmData::AlarmTable    *Alarm_Demo_Table;

  double MaxNumAlarms;
  double PrevNumAlarms;
  double CurrNumAlarms;
  
  int DemoCount;
  int DemoIndex;

  MaxNumAlarms  = scada_viewer->Alarm_data->GetMaxNumAlarmsInList();
  PrevNumAlarms = scada_viewer->Alarm_data->GetPrevNumAlarmsInList(); 
  CurrNumAlarms = scada_viewer->Alarm_data->GetNumAlarmsInList(); 
  
  PRINTF_VDT("GetDemoAlarms: MaxNumAlarms = %i\n", (int)MaxNumAlarms);
  PRINTF_VDT("GetDemoAlarms: PrevNumAlarms = %i\n", (int)PrevNumAlarms);
  PRINTF_VDT("GetDemoAlarms: CurrNumAlarms = %i\n", (int)CurrNumAlarms);
  
  DemoCount = scada_viewer->Alarm_Demo_Data->GetDemoCount();
  DemoCount++;
  if( DemoCount > 40 )
    DemoCount = 0;
  scada_viewer->Alarm_Demo_Data->SetDemoCount(DemoCount);
 // scada_viewer->Alarm_data->SetOffPageAlarmIndex( 0 );  
  PRINTF_VDT("GetDemoAlarms: DemoCount = %i\n", (int)DemoCount);  
  
  if (DemoCount <= 10 )
    {
    CurrNumAlarms = scada_viewer->Alarm_Demo_Data->GetList1Num();
    scada_viewer->Alarm_data->SetNumAlarmsInList(CurrNumAlarms);
    PRINTF_VDT("GetDemoAlarms: CurrNumAlarms = %i\n", (int)CurrNumAlarms);      

    for (int i = 0, DemoIndex = (CurrNumAlarms-1); 
    	 i < CurrNumAlarms; 
    	 i++, DemoIndex--)
      {
      AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
      Alarm_Demo_Table = &scada_viewer->Alarm_Demo_Data->List_1_Line_[DemoIndex];
      FillAlarmTbleRow( AlarmDataRecord, Alarm_Demo_Table );
      }
    PRINTF_VDT("GetDemoAlarms: End List\n\n");      
    }
  else if (DemoCount <= 20 )
    {
    CurrNumAlarms = scada_viewer->Alarm_Demo_Data->GetList2Num();
    scada_viewer->Alarm_data->SetNumAlarmsInList(CurrNumAlarms);    
    PRINTF_VDT("GetDemoAlarms: CurrNumAlarms = %i\n", (int)CurrNumAlarms);      

    for (int i = 0, DemoIndex = (CurrNumAlarms-1); 
    	 i < CurrNumAlarms; 
    	 i++, DemoIndex--)
      {
      AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
      Alarm_Demo_Table = &scada_viewer->Alarm_Demo_Data->List_2_Line_[DemoIndex];
      FillAlarmTbleRow( AlarmDataRecord, Alarm_Demo_Table );
      }
    PRINTF_VDT("GetDemoAlarms: End List\n\n");      	    
    }
  else if (DemoCount <= 30 )
    {
    CurrNumAlarms = scada_viewer->Alarm_Demo_Data->GetList3Num();
    scada_viewer->Alarm_data->SetNumAlarmsInList(CurrNumAlarms);    
    PRINTF_VDT("GetDemoAlarms: CurrNumAlarms = %i\n", (int)CurrNumAlarms);      

    for (int i = 0, DemoIndex = (CurrNumAlarms-1); 
    	 i < CurrNumAlarms; 
    	 i++, DemoIndex--)
      {
      AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
      Alarm_Demo_Table = &scada_viewer->Alarm_Demo_Data->List_3_Line_[DemoIndex];
      FillAlarmTbleRow( AlarmDataRecord, Alarm_Demo_Table );
      }
    PRINTF_VDT("GetDemoAlarms: End List\n\n");  
    } 
  else
    return;
   
}

/*----------------------------------------------------------------------
| Returns an allocated time stamp string.
*/
char * GetTime()
{
#define BUFFER_SIZE  256   
   char buffer[ BUFFER_SIZE ];
   
   GlgULong sec, msec;
   struct tm * time_struct;
   time_t time;
   
   GlgGetTime( &sec, &msec );
   time = sec;
   time_struct = localtime( &time );
   if( !time_struct )
      return NULL;
   
   /* Format a time stamp string */
   strftime( buffer, BUFFER_SIZE, "%H:%M:%S", time_struct );

   return GlgStrClone( buffer );
}

#endif

double GlgSCADAViewer::GetCurrTime()
{
  GlgULong sec, microsec;

  GlgGetTime ( &sec, &microsec );
  return sec + microsec / 1000000.0;
}
void GlgSCADAViewer::GetAlarmList( GlgSCADAViewer * scada_viewer )
{
  CGlgAlarmData *AlarmDataRecord;
  CGlgAlarmData::AlarmTable    Alarm_Table_Record;

  double MaxNumAlarms;
  double PrevNumAlarms;
  double CurrNumAlarms;

  Alarm_Table_Record.PointId = GlgStrClone( (char*) "");
  Alarm_Table_Record.Description = GlgStrClone( (char*) "");
                
  MaxNumAlarms  = scada_viewer->Alarm_data->GetMaxNumAlarmsInList();
  PrevNumAlarms = scada_viewer->Alarm_data->GetPrevNumAlarmsInList(); 
  CurrNumAlarms = scada_viewer->Alarm_data->GetNumAlarmsInList(); 
  
  PRINTF_VDT("GetAlarms: MaxNumAlarms = %i\n", (int)MaxNumAlarms);
  PRINTF_VDT("GetAlarms: PrevNumAlarms = %i\n", (int)PrevNumAlarms);
  PRINTF_VDT("GetAlarms: CurrNumAlarms = %i\n", (int)CurrNumAlarms);

/////////////////////////////////
  std::vector<AlarmID_Type> vAlarms;
  if (pDataFeed->GetAlarmList(&vAlarms)) /// get Alarm List from DDS
  {
    CurrNumAlarms = (double) vAlarms.size(); 	/// get CurrNumAlarms from DDS  
  }
  else
  {
    CurrNumAlarms = 0;
  }
//  CurrNumAlarms = pDataFeed->GetNumAlarms();  /// get CurrNumAlarms from DDS
/////////////////////////////////

  scada_viewer->Alarm_data->SetNumAlarmsInList(CurrNumAlarms);
//  scada_viewer->Alarm_data->SetOffPageAlarmIndex( 0 );   
  PRINTF_VDT("GetAlarms: CurrNumAlarms = %i\n", (int)CurrNumAlarms);      

  for (int i = 0; i < CurrNumAlarms; i++)
    {
    AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
    GetDDSAlarmRecord( &Alarm_Table_Record, vAlarms.at(i) );
    FillAlarmTbleRow( AlarmDataRecord, &Alarm_Table_Record );
    }
  PRINTF_VDT("GetAlarms: End List\n\n");      
}

void GlgSCADAViewer::GetDDSAlarmRecord( CGlgAlarmData::AlarmTable *Alarm_Table_Record, AlarmID_Type AlarmID)
{
   int iStatus = 0;
   long long Annunciation_Time = 0;
   char longname[256];
   int iPointType=0;
   double dDisplayState = 0;
   double dValue = -1;
   Contact_States_Type eValue = CST_NULL_STATE;
   Alarm_States_Type eState = AST_CLEAR;
   
   iStatus = pDataFeed->GetAlarmAnnunciationTime(AlarmID, &Annunciation_Time);
   int iPgNum = pDataFeed->GetPageNum(AlarmID.PointID);
   iStatus = pDataFeed->ReadLongName(AlarmID.PointID, longname, 256);
   iPointType = pDataFeed->GetPointType(AlarmID.PointID);
//   iStatus = pDataFeed->GetAlarmState(AlarmID, &eState);   

/////////////////////////////////////////
// replace the right side of the assignment with the call ro DDS for that item
/////////////////////////////////////////
   Alarm_Table_Record->TimeDate = Annunciation_Time;
   GlgFree(Alarm_Table_Record->PointId);
   Alarm_Table_Record->PointId = GlgStrClone(AlarmID.PointID);
   Alarm_Table_Record->PageNum = iPgNum;
   GlgFree(Alarm_Table_Record->Description);      
   Alarm_Table_Record->Description = GlgStrClone((char *)longname); 
   switch (iPointType)
   {
     case ANALOG:
	 iStatus = pDataFeed->ReadRTUDAnalogValue(AlarmID.PointID, dValue);   
//	 iStatus = pDDS_RealTimeData->GetAnalogValue(AlarmID->PointID, &dValue);   
	 Alarm_Table_Record->value = dValue;
	 dDisplayState = pDataFeed->GetAnalogDisplayState(AlarmID.PointID);
	 break;
	 
     case STATUS_POINT:
     case CONTACT_ALARM:
     case AI_FRAME_FAILURE:
     case AO_FRAME_FAILURE:
     case RTU_FAILURE:
     case RTU_CMD_DISABLE_ALARM:
     case STATUS_INPUT_FRAME_FAILURE:
     case DO_FRAME_FAILURE:
	 iStatus = pDataFeed->ReadRTUDDigitalValue(AlarmID.PointID, &eValue);   
//	 iStatus = pDDS_RealTimeData->GetDigitalValue(AlarmID->PointID, *eValue);   
	 Alarm_Table_Record->value = (double) eValue;
	 dDisplayState = pDataFeed->GetDigitalDisplayState(AlarmID.PointID);
	 break;

     default:
       WARNF_DATABASE("GlgSCADAViewer.GetDDSAlarmRecord: PointID = [%s] Point Type = %d\n",
	   AlarmID.PointID, iPointType);                 
       WARNF_VDT("GlgSCADAViewer.GetDDSAlarmRecord: PointID = [%s] Point Type = %d\n",
	   AlarmID.PointID, iPointType);                 
   } 
   Alarm_Table_Record->AlarmType = AlarmID.Type;
   Alarm_Table_Record->AlarmState = dDisplayState;     
//   Alarm_Table_Record->AlarmState = eState;     
	
   PRINTF_VDT("GetDDSAlarmRecord: PointId = %s\n", (char *)Alarm_Table_Record->PointId);
   PRINTF_VDT("GetDDSAlarmRecord: PageNum = %i\n", (int)Alarm_Table_Record->PageNum);
   PRINTF_VDT("GetDDSAlarmRecord: Description = %s\n", (char *)Alarm_Table_Record->Description);
   PRINTF_VDT("GetDDSAlarmRecord: value = %i\n", (int)Alarm_Table_Record->value);
   PRINTF_VDT("GetDDSAlarmRecord: AlarmType = %i\n", (int)Alarm_Table_Record->AlarmType);
   PRINTF_VDT("GetDDSAlarmRecord: AlarmState = %i\n", (int)Alarm_Table_Record->AlarmState);			
}

void GlgSCADAViewer::FillAlarmTbleRow( CGlgAlarmData *AlarmDataRecord,
	                            CGlgAlarmData::AlarmTable *Alarm_Demo_Table)
{
      AlarmDataRecord->AlarmTableData.TimeDate = Alarm_Demo_Table->TimeDate;
//      GlgFree(Alarm_Demo_Table->PointId); orig
//      GlgFree(AlarmDataRecord->AlarmTableData.PointId);
      AlarmDataRecord->AlarmTableData.PointId = GlgStrClone(Alarm_Demo_Table->PointId);
      AlarmDataRecord->AlarmTableData.PageNum = Alarm_Demo_Table->PageNum;
//      GlgFree(Alarm_Demo_Table->Description); orig     
//      GlgFree(AlarmDataRecord->AlarmTableData.PointId);      
      AlarmDataRecord->AlarmTableData.Description = GlgStrClone(Alarm_Demo_Table->Description);
      AlarmDataRecord->AlarmTableData.value = Alarm_Demo_Table->value;
      AlarmDataRecord->AlarmTableData.AlarmType = Alarm_Demo_Table->AlarmType;
      AlarmDataRecord->AlarmTableData.AlarmState = Alarm_Demo_Table->AlarmState;      
	
      PRINTF_VDT("FillAlarmTbleRow: TimeDate = %i\n", (int)AlarmDataRecord->AlarmTableData.TimeDate);
      PRINTF_VDT("FillAlarmTbleRow: PointId = %s\n", (char *)AlarmDataRecord->AlarmTableData.PointId);
      PRINTF_VDT("FillAlarmTbleRow: PageNum = %i\n", (int)AlarmDataRecord->AlarmTableData.PageNum);
      PRINTF_VDT("FillAlarmTbleRow: Description = %s\n", (char *)AlarmDataRecord->AlarmTableData.Description);
      PRINTF_VDT("FillAlarmTbleRow: value = %i\n", (int)AlarmDataRecord->AlarmTableData.value);
      PRINTF_VDT("FillAlarmTbleRow: AlarmType = %i\n", (int)AlarmDataRecord->AlarmTableData.AlarmType);
      PRINTF_VDT("FillAlarmTbleRow: AlarmState = %i\n", (int)AlarmDataRecord->AlarmTableData.AlarmState);	
}

void GlgSCADAViewer::DisplayAlarmList( GlgSCADAViewer * scada_viewer )
{
  CGlgAlarmData *AlarmDataRecord;
  CGlgAlarmData::AlarmTable    *Alarm_Demo_Table;
  GlgObjectC    *Row_Data;

  bool bFoundBottomAlarm;  

  double MaxNumAlarms;
  double PrevNumAlarms;
  double CurrNumAlarms;
  
  bFoundBottomAlarm = FALSE;
  
  MaxNumAlarms  = scada_viewer->Alarm_data->GetMaxNumAlarmsInList();
  PrevNumAlarms = scada_viewer->Alarm_data->GetPrevNumAlarmsInList(); 
  CurrNumAlarms = scada_viewer->Alarm_data->GetNumAlarmsInList(); 
  PRINTF_VDT("DisplayAlarmList: MaxNumAlarms = %i\n", (int)MaxNumAlarms);
  PRINTF_VDT("DisplayAlarmList: PrevNumAlarms = %i\n", (int)PrevNumAlarms);
  PRINTF_VDT("DisplayAlarmList: CurrNumAlarms = %i\n", (int)CurrNumAlarms);

  if ( CurrNumAlarms == 0 )
    ClearAlarmDisplays( scada_viewer, PrevNumAlarms, CurrNumAlarms); 
  else
  {
    for (int i = 0;  i < CurrNumAlarms; i++)
        {
        AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
        Row_Data = scada_viewer->Alarm_data->Rows[ i ];
 
        Row_Data->SetResource( "TimeInput", AlarmDataRecord->AlarmTableData.TimeDate);
        Row_Data->SetResource( "PointId", AlarmDataRecord->AlarmTableData.PointId);
        Row_Data->SetResource( "Description", AlarmDataRecord->AlarmTableData.Description);
        Row_Data->SetResource( "Value", AlarmDataRecord->AlarmTableData.value);
        Row_Data->SetResource( "AlarmType", AlarmDataRecord->AlarmTableData.AlarmType);
        Row_Data->SetResource( "AlarmState", AlarmDataRecord->AlarmTableData.AlarmState); 
      
        Row_Data->SetResource( "/Label0/Visibility", (double)1);
        Row_Data->SetResource( "/Label1/Visibility", (double)1);
        Row_Data->SetResource( "/Label2/Visibility", (double)1);
        Row_Data->SetResource( "/Label3/Visibility", (double)1);
        Row_Data->SetResource( "/Label4/Visibility", (double)1); 

	PRINTF_VDT("DisplayAlarmList: Record: TimeDate = %i\n", (int)AlarmDataRecord->AlarmTableData.TimeDate);
	PRINTF_VDT("DisplayAlarmList: Record: PointId = %s\n", (char *)AlarmDataRecord->AlarmTableData.PointId);
	PRINTF_VDT("DisplayAlarmList: Record: PageNum = %i\n", (int)AlarmDataRecord->AlarmTableData.PageNum);
	PRINTF_VDT("DisplayAlarmList: Record: Description = %s\n", (char *)AlarmDataRecord->AlarmTableData.Description);
	PRINTF_VDT("DisplayAlarmList: Record: value = %i\n", (int)AlarmDataRecord->AlarmTableData.value);
	PRINTF_VDT("DisplayAlarmList: Record: AlarmType = %i\n", (int)AlarmDataRecord->AlarmTableData.AlarmType);
	PRINTF_VDT("DisplayAlarmList: Record: AlarmState = %i\n", (int)AlarmDataRecord->AlarmTableData.AlarmState);	

	PRINTF_VDT("DisplayAlarmList: Table: TimeDate = %i\n", (int)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.TimeDate);
	PRINTF_VDT("DisplayAlarmList: Table: PointId = %s\n", (char *)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.PointId);
	PRINTF_VDT("DisplayAlarmList: Table: PageNum = %i\n", (int)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.PageNum);
	PRINTF_VDT("DisplayAlarmList: Table: Description = %s\n", (char *)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.Description);
	PRINTF_VDT("DisplayAlarmList: Table: value = %i\n", (int)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.value);
	PRINTF_VDT("DisplayAlarmList: Table: AlarmType = %i\n", (int)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.AlarmType);
	PRINTF_VDT("DisplayAlarmList: Table: AlarmState = %i\n", (int)scada_viewer->Alarm_data->AlarmDataArray[ i ]->AlarmTableData.AlarmState);	

      if (!bFoundBottomAlarm )
          {
          if( (AlarmDataRecord->AlarmTableData.AlarmState == 1) ||
              (AlarmDataRecord->AlarmTableData.AlarmState == 4 ) )
            {
            DisplayBottomAlarmLine( AlarmDataRecord );
            bFoundBottomAlarm = TRUE;        
            }
          }                
        }  
 
     // hide extra alarm list lines from previous list   
     if ( PrevNumAlarms > CurrNumAlarms )
       {
       for (int i = CurrNumAlarms; i < PrevNumAlarms; i++) 
         {
         PRINTF_VDT("DisplayAlarmList: CurrNumAlarms = %i, PrevNumAlarms = %i\n", 
       	           (int)CurrNumAlarms, PrevNumAlarms);
         AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
         Row_Data = scada_viewer->Alarm_data->Rows[ i ];       	       
         Row_Data->SetResource( "/Label0/Visibility", (double)0);
         Row_Data->SetResource( "/Label1/Visibility", (double)0);
         Row_Data->SetResource( "/Label2/Visibility", (double)0);
         Row_Data->SetResource( "/Label3/Visibility", (double)0);
         Row_Data->SetResource( "/Label4/Visibility", (double)0); 
         Row_Data->SetResource( "AlarmState", (double)0);        

//       Alarm_Demo_Table = &scada_viewer->Alarm_Demo_Data->List_3_Line_[DemoIndex];       
//       if ( Alarm_Demo_Table->PointId != NULL )
//         GlgFree(Alarm_Demo_Table->PointId);
//       GlgFree(Alarm_Demo_Table->Description);              
         }
       }
     }
     scada_viewer->Alarm_data->SetPrevNumAlarmsInList(CurrNumAlarms);  
}

void GlgSCADAViewer::ClearAlarmDisplays( GlgSCADAViewer * scada_viewer,
	                                 double PrevNumAlarms, 
	                                 double CurrNumAlarms)
{
   CGlgAlarmData *AlarmDataRecord;
   GlgObjectC    *Row_Data;  
   
   HideBottomAlarmLine();
 
   if ( PrevNumAlarms > CurrNumAlarms )
     for (int i = CurrNumAlarms; i < PrevNumAlarms; i++) 
       {
       PRINTF_VDT("ClearAlarmDisplays: CurrNumAlarms = %i, PrevNumAlarms = %i\n", 
       	         (int)CurrNumAlarms, PrevNumAlarms);
       AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
       Row_Data = scada_viewer->Alarm_data->Rows[ i ];       	       
       Row_Data->SetResource( "/Label0/Visibility", (double)0);
       Row_Data->SetResource( "/Label1/Visibility", (double)0);
       Row_Data->SetResource( "/Label2/Visibility", (double)0);
       Row_Data->SetResource( "/Label3/Visibility", (double)0);
       Row_Data->SetResource( "/Label4/Visibility", (double)0); 
       Row_Data->SetResource( "AlarmState", (double)0);        
   
       }
}

void GlgSCADAViewer::DisplayBottomAlarmLine( CGlgAlarmData *AlarmDataRecord )
{
   SetResource( "AreaBottom/BottomTimeInput", AlarmDataRecord->AlarmTableData.TimeDate);
   SetResource( "AreaBottom/BottomPtId", AlarmDataRecord->AlarmTableData.PointId );
   SetResource( "AreaBottom/BottomDescription", AlarmDataRecord->AlarmTableData.Description ); 
   SetResource( "AreaBottom/BottomValue", AlarmDataRecord->AlarmTableData.value );        
   SetResource( "AreaBottom/AlarmType", AlarmDataRecord->AlarmTableData.AlarmType ); 
   SetResource( "AreaBottom/AlarmState", AlarmDataRecord->AlarmTableData.AlarmState );  
   SetResource( "AreaBottom/AlarmInfoVisibility", (double)1 );
}

void GlgSCADAViewer::HideBottomAlarmLine()
{
   SetResource( "AreaBottom/AlarmState", (double)0 ); 
   SetResource( "AreaBottom/AlarmInfoVisibility", (double)0 );  
}

void GlgSCADAViewer::OffPageAlarm( GlgSCADAViewer * scada_viewer )
{
  CGlgAlarmData *AlarmDataRecord;
  
  double CurrNumAlarms;
  int  StartIndex;
  int  CurrentPageNumber;
  char *PointId;
  bool bFoundOffPageAlarm; 

  bFoundOffPageAlarm = FALSE;
  
  CurrentPageNumber = scada_viewer->Alarm_data->GetCurrentPageNumber(); 
  CurrNumAlarms = scada_viewer->Alarm_data->GetNumAlarmsInList(); 
  StartIndex    = scada_viewer->Alarm_data->GetOffPageAlarmIndex();
  PointId       = scada_viewer->Alarm_data->GetOffPageAlarmPointId();
  
  if ( CurrentPageNumber == -1 )
  {
    CurrentPageNumber = CalcPageNumFromIndex( MainMenuIndex, SubMenuIndex );
    scada_viewer->Alarm_data->SetCurrentPageNumber( CurrentPageNumber );   
  }

  PRINTF_VDT("OffPageAlarm: CurrNumAlarms = %i\n", (int)CurrNumAlarms);
  printf("OffPageAlarm: CurrentPageNumber = %i\n", (int)CurrentPageNumber );
  printf("OffPageAlarm: CurrNumAlarms = %i, StartIndex = %i\n", 
         (int)CurrNumAlarms, StartIndex);
  AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ StartIndex ];  
  printf("OffPageAlarm1: CurrNumAlarms = %s, AlarmDataRecord->AlarmTableData.PointId = %s\n", 
         (char *)PointId, (char *)AlarmDataRecord->AlarmTableData.PointId);  
  if (! strcmp( PointId,  AlarmDataRecord->AlarmTableData.PointId ) )
    StartIndex++;
  else
    StartIndex = 0;

  printf("OffPageAlarm2: CurrNumAlarms = %i, StartIndex = %i\n", 
         (int)CurrNumAlarms, StartIndex);  
  
  bFoundOffPageAlarm = SearchAlarmList( scada_viewer, StartIndex, CurrNumAlarms ); 

  if( !bFoundOffPageAlarm )
     bFoundOffPageAlarm = SearchAlarmList( scada_viewer, 0, CurrNumAlarms );  	  

  StartIndex    = scada_viewer->Alarm_data->GetOffPageAlarmIndex();    
  printf("OffPageAlarm3: CurrNumAlarms = %i, StartIndex = %i\n", 
        (int)CurrNumAlarms, StartIndex);     
  printf("OffPageAlarm\n");
}

bool GlgSCADAViewer::SearchAlarmList( GlgSCADAViewer * scada_viewer,
	int StartIndex, int CurrNumAlarms )
{
  CGlgAlarmData *AlarmDataRecord;
  bool 	bFoundOffPageAlarm;
  
  bFoundOffPageAlarm = FALSE;
  
  for (int i = StartIndex; i < CurrNumAlarms; i++)
    {
    AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
    
    if (!bFoundOffPageAlarm )
      {
      if( (AlarmDataRecord->AlarmTableData.AlarmState == 1) ||
          (AlarmDataRecord->AlarmTableData.AlarmState == 4 ) )
        {
        OpenPageFromNum( AlarmDataRecord->AlarmTableData.PageNum );
        scada_viewer->Alarm_data->SetOffPageAlarmIndex( i );
        scada_viewer->Alarm_data->SetOffPageAlarmPointId( AlarmDataRecord->AlarmTableData.PointId );        
        bFoundOffPageAlarm = TRUE;        
        }
      }                
    }
    
    return bFoundOffPageAlarm;
}

void GlgSCADAViewer::DisplayBeforeOffPageAlarm( GlgSCADAViewer * scada_viewer )
{
  int  CurrentPageNumber;

  CurrentPageNumber = scada_viewer->Alarm_data->GetCurrentPageNumber(); 
  printf("DisplayBeforeOffPageAlarm: page = %i\n", CurrentPageNumber);
   
  if ( CurrentPageNumber == -1 )
    return;

  OpenPageFromNum( CurrentPageNumber );
  scada_viewer->Alarm_data->SetCurrentPageNumber( -1 );
  printf("DisplayBeforeOffPageAlarm1: page = %i\n", CurrentPageNumber);
}

int GlgSCADAViewer::CalcPageNumFromIndex( int MainMenuIndex, int SubMenuIndex )
{
  int nPage;
  
  nPage = (MainMenuIndex * 100) + SubMenuIndex;

  printf("CalcPageNumFromIndex: page = %i\n", nPage);
  return nPage;
}

void GlgSCADAViewer::OpenPageFromNum( int PageNum )
{
   double iMainIndex;
   double iSubIndex;

   iMainIndex = PageNum / 100;
   iSubIndex  = PageNum - ( iMainIndex * 100 );
 
   MainMenuIndex = iMainIndex;
   
   SelectMainMenuItem( MainMenuIndex, 0, true );
   
   SubMenuIndex =  iSubIndex;   
   SelectSubMenuItem( SubMenuIndex, 0, true );
   CloseAlarmDialog(); 
   printf("OpenPageFromNum: PageNum = %i, iMainIndex = %f, iSubIndex = %f\n",
   	   PageNum, iMainIndex, iSubIndex);
}

void GlgSCADAViewer::AckAlarmFromList( GlgSCADAViewer * scada_viewer )
{
  CGlgAlarmData *AlarmDataRecord;
  
  double CurrNumAlarms;
  int  StartIndex;
  char *PointId;
  bool bFoundOffPageAlarm; 

  bFoundOffPageAlarm = FALSE;
  
  CurrNumAlarms = scada_viewer->Alarm_data->GetNumAlarmsInList(); 
  StartIndex    = scada_viewer->Alarm_data->GetAlarmAckIndex();
  PointId       = scada_viewer->Alarm_data->GetAlarmAckPointId();
  
  PRINTF_VDT("AckAlarmFromList: CurrNumAlarms = %i\n", (int)CurrNumAlarms);
  printf("AckAlarmFromList: CurrNumAlarms = %i, StartIndex = %i\n", 
         (int)CurrNumAlarms, StartIndex);
  AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ StartIndex ];  
  printf("AckAlarmFromList1: CurrNumAlarms = %s, AlarmDataRecord->AlarmTableData.PointId = %s\n", 
         (char *)PointId, (char *)AlarmDataRecord->AlarmTableData.PointId);  

  if (! strcmp( PointId,  AlarmDataRecord->AlarmTableData.PointId ) )
    StartIndex++;
  else
    StartIndex = 0;

  printf("AckAlarmFromList2: CurrNumAlarms = %i, StartIndex = %i\n", 
         (int)CurrNumAlarms, StartIndex);  
 
  bFoundOffPageAlarm = SearchAlarmAckList( scada_viewer, StartIndex, CurrNumAlarms ); 

  if( !bFoundOffPageAlarm )
     bFoundOffPageAlarm = SearchAlarmAckList( scada_viewer, 0, CurrNumAlarms );  	  

  StartIndex    = scada_viewer->Alarm_data->GetAlarmAckIndex();  
  printf("AckAlarmFromList3: CurrNumAlarms = %i, StartIndex = %i\n", 
        (int)CurrNumAlarms, StartIndex);     
  printf("AckAlarmFromList\n");
}

bool GlgSCADAViewer::SearchAlarmAckList( GlgSCADAViewer * scada_viewer,
	int StartIndex, int CurrNumAlarms )
{
  CGlgAlarmData *AlarmDataRecord;
  bool 	bFoundOffPageAlarm;
  
  bFoundOffPageAlarm = FALSE;

  for (int i = StartIndex; i < CurrNumAlarms; i++)
    {
    AlarmDataRecord = scada_viewer->Alarm_data->AlarmDataArray[ i ];
 
    if (!bFoundOffPageAlarm )
      {
      if( (AlarmDataRecord->AlarmTableData.AlarmState == 1) ||
          (AlarmDataRecord->AlarmTableData.AlarmState == 4 ) )
        {
        AckAlarmListEntry( this, AlarmDataRecord->AlarmTableData.PointId );
        scada_viewer->Alarm_data->SetAlarmAckIndex( i );
        scada_viewer->Alarm_data->SetAlarmAckPointId( AlarmDataRecord->AlarmTableData.PointId );        
        bFoundOffPageAlarm = TRUE;        
        }
      }                
    }
    
    return bFoundOffPageAlarm;
}

enum
{
   ALARM_NONE   = 0,
   ALARM_RESET  = 1,
   ALARM_ACK    = 2,   /* Acknowledged by the operator */
   ALARM_RAISED = 3
};

void GlgSCADAViewer::AckAlarmListEntry( GlgSCADAViewer * scada_viewer, char *PointId )
{

   char * res_name1, * res_name2;
   
   res_name1 = GlgStrClone( PointId );
   res_name2 = GlgConcatResNames( res_name1, (char *)"AlarmAck");

   printf("AckAlarmListEntry: res_name2 = %s\n", res_name2);
   printf("AlarmAck_tag_source = %s\n", res_name2); 
 //  selected_obj.SetResource( "AlarmAck", ALARM_ACK );
   WriteTagData( res_name2, ALARM_ACK );   
   GlgFree(res_name1);  
   GlgFree(res_name2);   
}

// Writes tag data into the database.
//
void GlgSCADAViewer::WriteTagData( CONST char * tag_source, double value )
{
   // Place code here to write the value to the specified tag.   
   pDataFeed->WriteDBValue( tag_source, value );

#if RANDOM_DEMO_DATA
   // In the demo, update the display with the entered value.
   // In the real application, there will be a round trip and 
   // the display will be updated by the new data value coming from
   // database.
   parent->SetTag( tag_source, value, true );
   parent->Update();
#endif
}

/*----------------------------------------------------------------------
| Quit the application.
*/
void GlgSCADAViewer::Quit( void )
{
   system( "pkill hensettime.x");
   exit( GLG_EXIT_OK );
}

/*----------------------------------------------------------------------
| Generate an error message.
*/
void GlgSCADAViewer::error( GlgErrorType msg_type, CONST char * message, 
			    bool app_exit )
{
   GlgError( msg_type, (char*) message );
   if( app_exit )
     Quit();
}

void GlgSCADAViewer::errorS( GlgErrorType msg_type, CONST char * message1, 
                             CONST char * message2, bool app_exit )
{
   char * message = GlgConcatStrings( (char*)message1, (char*)message2 );

   error( msg_type, message, app_exit );

   GlgFree( message );
}

// Assignment operator
GlgSCADAViewer& GlgSCADAViewer::operator= ( const GlgObjectC& object )
{
   GlgObjectC::operator=( object );
   return *this;
}

/*--------------------------------------------------------------------
| Fill MainMenuArray from a configuration file. If configuration file 
| is not supplied, use predefined MainMenuTable array.
*/
void GlgSCADAViewer::FillMainMenuArray( char * exe_path, char * config_filename )
{
   SubMenuRecord * submenu_array;
   int
     i, j,
     num_submenu_items;

   MainMenuArray = ReadMenuConfig( exe_path, config_filename );   

   if( !MainMenuArray )
   { 
      error( GLG_INFO, 
             "Can't read config file: using predefined MainMenu Table.", 
             False );

      /* Use predefined MainMenuTable */
      MainMenuArray = MainMenuTable;
   }

   /* Find and store the number of items in the main menu and submenus.
      Menu arrays are terminated with a record containing null fields.
   */
   NumMainMenuItems = 0;
   for( i=0; MainMenuArray[i].label_string; ++i )
   {
      ++NumMainMenuItems;
      
      submenu_array = MainMenuArray[i].submenu_array;
      if( submenu_array )
      {
         num_submenu_items = 0;
         for( j=0; submenu_array[j].label_string; ++j )
           ++num_submenu_items;

         MainMenuArray[i].num_submenu_items = num_submenu_items;
      }
      else
        MainMenuArray[i].num_submenu_items = 0;       
   }
}

///////////////////////////////////////////////////////////////
void GlgSCADAViewer::ProcessTakeCtrl()
{
//#define VDT_MSCC     20
//#define VDT_QTR_DECK 21
//#define VDT_ECCC_1   23
//#define VDT_ECCC_2   24
//#define VDT_ECCC_3   25

   int iVdtId;
   double dVdtId;
   iVdtId = VDTNumber->GetVdtPosition();   
   PRINTF_VDT("ProcessTakeCtrl: iVdtId = %i\n", iVdtId);
   ControlIndicator.SetResource( "ClickCtrl", iVdtId );
   ControlIndicator.SetResource( "State", 2 );
   ControlIndicator.GetResource( "ClickCtrl", &dVdtId );
   PRINTF_VDT("ProcessTakeCtrl1: dVdtId = %i\n", (int)dVdtId);
   
   pDataFeed->WriteDBValue( "ControlIndicator/VdtTakeCtrl/unset", iVdtId );   

}
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
void GlgSCADAViewer::ProcessInCtrl()
{

//#define VDT_MSCC     20
//#define VDT_QTR_DECK 21
//#define VDT_ECCC_1   23
//#define VDT_ECCC_2   24
//#define VDT_ECCC_3   25
   int    iVdtId, iCpyVdtId;
   double dVdtInCtrl;
  iVdtId = VDTNumber->GetVdtPosition();
  PRINTF_VDT("ProcessInCtrl: iVdtId = %i\n", iVdtId);
   
   pDataFeed->GetVdtSIC(&dVdtInCtrl);

   PRINTF_VDT("ProcessInCtrl: dVdtInCtrl = %f\n", dVdtInCtrl);
   if (iVdtId == (int) dVdtInCtrl) 
     ControlIndicator.SetResource( "State", (double)1 ); 
   else
     ControlIndicator.SetResource( "State", (double)0 );  	   

}

///////////////////////////////////////////////////////////////
#if REMAP_TAGS
/*--------------------------------------------------------------------
| Reassign tag sources in the supplied viewport.
| In the RANDOM_DEMO_DATA mode it sets unset tag sources to test data updates.
| Otherwise, it invokes 
*/
void GlgSCADAViewer::RemapTags( GlgObjectC& drawing_vp )
{
   GlgObjectC 
      tag_list,
      tag_obj;
   int
      size, 
      i;
   CONST char 
      * tag_name,
      * tag_source,
      * tag_comment;
   
   /* Obtain a list of all tags defined in the drawing and remap them
      as needed. 
   */
   tag_list = drawing_vp.CreateTagList( /* List all tags */ false );  

   /* CreateTagList creates an object (a group containing a list of tags).
      The returned object has to be explicitly dereferenced to prevent a 
      memory leak. The object is still referenced by the tag_list variable 
      instance.
   */
   tag_list.Drop();

   if( tag_list.IsNull() )
      return;

   size = tag_list.GetSize();
   if( !size )
      return; /* no tags found */
   
   /* Traverse the tag list and remap each tag as needed. */
   for( i=0; i<size; ++i )
   {
      tag_obj = tag_list.GetElement( i );
      
      /* Retrieve TagName and TagSource attributes from the
	 tag object. TagSource represents the data source variable
	 used to supply real-time data. This function demonstrates
	 how to reassign the TagSource at run-time.
      */
      tag_obj.GetResource( "TagName", &tag_name );
      tag_obj.GetResource( "TagSource", &tag_source );
      tag_obj.GetResource("TagComment",&tag_comment);
      
#if RANDOM_DEMO_DATA
      /* For demo purposes only, assign tag sources to be 
	 the same as tag names unlesss TagSource is already defined. 
      */
      if( !tag_source || !*tag_source || strcmp( tag_source, "unset" ) == 0 )
      {
	 /* Skip tags with undefined TagName */
	 if( !tag_name || !*tag_name || strcmp( tag_name, "unset" ) == 0 )
	    continue;
	 
	 /* Assign TagSource to be the same as TagName -- for demo purposes. */
         tag_obj.SetResource( "TagSource", tag_name );
      }
#else
      /* Reassign TagSource as needed. */      
      RemapTagObject( tag_obj, tag_name, tag_source );
#endif
   }   
}

/*--------------------------------------------------------------------
| Reassign TagSource parameter for a given tag object to a new
| TagSource value.
*/
void GlgSCADAViewer::RemapTagObject( GlgObjectC& tag_obj, CONST char * tag_name,
                                     CONST char * tag_source )
{
   CONST char * new_tag_source;

   // Get a new tag source to remap the tag to based on the application logic.
   //
   new_tag_source = GetNewTagSource( tag_name, tag_source );

   tag_obj.SetResource( "TagSource", new_tag_source );
}

/*--------------------------------------------------------------------
| Used to remap tag sources based the application logic.
| Given a tag name and a tag source, returns a new tag source to use.
*/
static char * GetNewTagSource( CONST char * tag_name, CONST char * tag_source )
{
   // Change the next line to assign a new tag source based on application 
   // logic, using tag_name and tag_source as input.
   // For now, assigns the tag source to be the same as tag name for demo
   // purposes.

   return tag_name;
}

/*----------------------------------------------------------------------
| Utility function foir using in an application:
| Remaps all object tags with the specified tag_name to use a new tag_source.
*/
GlgLong GlgSCADAViewer::RemapNamedTags( GlgObjectC& object, 
                                        CONST char * tag_name,
                                        CONST char * tag_source )
{
   GlgObjectC 
      tag_list,
      tag_obj;
   int i, size;
   
   /* Obtain a list of tags with TagName attribute matching 
      the specified tag_name.
   */ 
   tag_list = object.GetTagObject( tag_name, /* by name */ true, 
				   /* list all tags */ false, 
				   /* multiple tags mode */ false, 
				   /* Data tag */ GLG_DATA_TAG );

   /* In the multiple tags mode, GetTagObject creates and returns a list of 
      tags. The returned list object has to be explicitly dereferenced to 
      prevent a memory leak. The object is still referenced by the tag_list 
      variable instance.
   */
   tag_list.Drop();

   if( tag_list.IsNull() )
      size = 0;
   else
      size = tag_list.GetSize( );
   
   for( i=0; i<size; ++i )
   {
      tag_obj = tag_list.GetElement( i );
      RemapTagObject( tag_obj, tag_name, tag_source );
   }
   
   return size;
}

#endif
