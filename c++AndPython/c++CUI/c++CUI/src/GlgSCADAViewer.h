#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950
#endif


#include <iostream>
#include <string.h>
#include <stdio.h>

#include "Utility.h"
#include "data_feed.h"

#include "VDT_Position.h"
#include "GlgAlarms.h"
#include "GlgAlarmData.h"

using namespace std;

class Utility;
class CDataFeed;
class CVdtPosition;
class CGlgAlarms;
class CAlarmDemo;

typedef enum _MenuLocation
{
   NO_POPUP_MENU = 0,
   TOP_POPUP_MENU,
   DIALOG_POPUP_MENU
} MenuLocation;

class GlgSCADAViewer : public GlgObjectC
{
 public:
   GlgSCADAViewer(void);
   ~GlgSCADAViewer(void);
   
 public:

   GlgObjectC ControlIndicator;
   GlgObjectC LogAllDataBasePointButton;   
   GlgAppContext AppContext;

   /* Array of menu items used to populate MainMenu at the top and
      SubMenu on the left. 
   */
   MainMenuRecord * MainMenuArray;

   /* Array of tag records. */
   GlgTagRecord ** TagRecordArray;

   /* Number of tags records in TagRecordArray. */
   GlgLong NumTagRecords;

   /* Number of menu items in MainMenuArray. */
   GlgLong NumMainMenuItems;

   GlgLong UpdateInterval; // update interval in msec
   GlgLong AlarmUpdateInterval; // alarm update interval in msec
	
   GlgLong TimerID;
   GlgLong AlarmTimerID;

   GlgLong MainMenuIndex;        // MainMenu selection, 0-based
   //GlgLong UtilityMenuIndex;        // MainMenu selection, 0-based
   //int DigitalPageMenuIndex;     // Utility selection Index
   //int AnalogPageMenuIndex;     // Utility selection Index
   GlgLong SubMenuIndex;         // SubMenu selection, 0-based

   GlgObjectC MainMenu;          // MainMenu object at the top
   GlgObjectC SubMenu;           // SubMenu object on the left
   GlgDrawingArea DrawingArea;   // Subwindow object in top level drawing
   GlgObjectC AlarmDialog;       // AlarmDialog viewport	
   GlgObjectC AlarmList;         // Viewport containing the alarm list
   GlgObjectC PopupDialog;       // Popup Dialog
   GlgObjectC PopupDialog0;       // Popup Dialog
   GlgObjectC PopupMenuTop;      // Top level PopupMenu
   GlgObjectC PopupMenuDialog;   // Dialog's PopupMenu



   GlgDrawingArea DrawingAreaDialog;     // Subwindow object in the PopupDialog
   GlgDrawingArea DrawingAreaDialog0;     // Subwindow object in the PopupDialog
   GlgDrawingArea DrawingAreaMenuTop;    // Subwindow object of top popup menu
   GlgDrawingArea DrawingAreaMenuDialog; // Subwindow object of the dialog's


                                         // popup menu
   bool PopupDialogVisible;
   MenuLocation ActivePopupMenuType;
   
   // Input callback, enabled in SCADAViewerView.cpp::OnInitialUpdate
   virtual void Input( GlgObjectC& callback_viewport, GlgObjectC& message);
   
   virtual void Trace( GlgObjectC& callback_viewport, 
                       GlgTraceCBStruct * trace_info );

   // Hierarchy callback, enabled in SCADAViewerView.cpp::OnInitialUpdate.
   virtual void Hierarchy( GlgObjectC& callback_viewport,
			   GlgHierarchyCBStruct * hierarchy_info );

   bool LoadDrawing( void );
   void CreateTagRecords( GlgObjectC& drawing_vp); 
   void DeleteTagRecords( void ); 
   void QueryTags( GlgObjectC& drawing_vp );
   void UpdateData();
   void ProcessTakeCtrl();
   void ProcessInCtrl();
   void Init( void );
   void DisplayAlarmDialog( void );
   void CloseAlarmDialog( void );
   void DisplayPopupMenu( GlgDrawingArea * drawing_area, 
                          GlgObjectC& selected_obj, GlgObjectC& command_obj );
   void PositionPopupMenu( GlgObjectC& selected_obj );
   void ConfigurePopupMenu( GlgObjectC& menu_vp, GlgObjectC& selected_obj, 
                            GlgObjectC& command_obj, CONST char * menu_title );
   void HidePopupMenu( void );

   void DisplayPopupDialog( GlgObjectC& selected_obj, GlgObjectC& command_obj );
   void ClosePopupDialog( void );
   int getUtilityMenuIndex();
   void RemapTags( GlgObjectC& drawing_vp );
   void RemapTagObject( GlgObjectC& tag_obj, CONST char * new_tag_source );
   GlgLong RemapNamedTags( GlgObjectC& object, 
                           CONST char * tag_name, CONST char * tag_source );
   void StartUpdates( void );
   void StopUpdates( void );	
   double GetDTagData( GlgTagRecord * tag_record );
   CONST char * GetSTagData( GlgTagRecord * tag_record );
   void GetAlarms( void );
   void GetDemoAlarms( GlgSCADAViewer * scada_viewer );
   void GetAlarmList( GlgSCADAViewer * scada_viewer );
   void GetDDSAlarmRecord( CGlgAlarmData::AlarmTable *Alarm_Demo_Table, AlarmID_Type AlarmID);   
   void FillAlarmTbleRow( CGlgAlarmData *AlarmDataRecord,
	                  CGlgAlarmData::AlarmTable *Alarm_Demo_Table);
   void DisplayAlarmList( GlgSCADAViewer * scada_viewer );
   void ClearAlarmDisplays( GlgSCADAViewer * scada_viewer,
	                    double PrevNumAlarms, 
	                    double CurrNumAlarms);   
   
   void DisplayBottomAlarmLine( CGlgAlarmData *AlarmDataRecord );
   void HideBottomAlarmLine(); 
   void OffPageAlarm( GlgSCADAViewer * scada_viewer );
   void AckAlarmFromList( GlgSCADAViewer * scada_viewer );   
   bool SearchAlarmList( GlgSCADAViewer * scada_viewer,
   	                 int StartIndex, int CurrNumAlarms );
   bool SearchAlarmAckList( GlgSCADAViewer * scada_viewer,
   	                 int StartIndex, int CurrNumAlarms );   
   void DisplayBeforeOffPageAlarm( GlgSCADAViewer * scada_viewer );
   int  CalcPageNumFromIndex( int MainMenuIndex, int SubMenuIndex ); 
   void OpenPageFromNum( int PageNum );
   void AckAlarmListEntry( GlgSCADAViewer * scada_viewer, char *PointId ); 
   void WriteTagData( CONST char * tag_source, double value );
   void Quit();
   void FillMainMenuArray( char * exe_path, char * config_filename );
   void InitMainMenu( void );
   void InitSubMenu( void );
   void SelectMainMenuItem( GlgLong menu_index, GlgLong increment, 
			    bool update_menu );
   void SelectSubMenuItem( GlgLong menu_index, GlgLong increment, 
			   bool update_menu );
   void ShowSubMenu( bool show );
   void error( GlgErrorType message_type, CONST char * message, bool app_exit );
   void errorS( GlgErrorType msg_type, 
                CONST char * message1, CONST char * message2, bool app_exit );
   GlgSCADAViewer& operator= ( const GlgObjectC& object );

   double GetCurrTime();
   
   int setSystemTime(char *newdate, char *newtime);
   void *setTimeHndlr(void *args);		

   static void settimethread();
   void timer(int d,  void (*f)(void ));
   /////////////////////////////////////////////////////////////////////////////
   /////// Local Code
   CDataFeed *pDataFeed;
   Utility *utility;
   CVdtPosition *VDTNumber;
   CGlgAlarms *Alarm_data;
   CAlarmDemo *Alarm_Demo_Data;
//   GlgObject **Rows;

};

