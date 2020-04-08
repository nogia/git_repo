#include "Utility.h"

Utility::Utility()
{
   startup[0] = true;
   startup[1] = true;
   loginstatus = false;
   previousMainIndex = -1;
   previousSubIndex = -1;
   vdtstates.push_back(VDT_ECCC_1);
   vdtstates.push_back(VDT_ECCC_2);
   vdtstates.push_back(VDT_ECCC_3);
   vdtstates.push_back(VDT_MSCC);

}

Utility::~Utility()
{
     for(int i=0;i<menues.size();i++)
         menues.clear();

     analogStatusPages.clear();
     digitalStatusPages.clear();
     vdtstates.clear();
     delete parent;
     delete currentPopupDialog;
     delete changePasswordScreen;

}
void Utility::Init( GlgSCADAViewer * parent_p, GlgObjectC  *p1, GlgObjectC  *p2)
{
   parent = parent_p;
   parent->pDataFeed->InitDDS(1);
   parent->pDataFeed->InitDDSLogging(1);
   currentPopupDialog = 0;
   changePasswordScreen = 0;

   GlgObjectC * p = new GlgObjectC();
   *p = *p1;
   dialogWidgets.insert(p);
   p = new GlgObjectC();
   *p = *p2;
   dialogWidgets.insert(p);
   InitUtilitiesData("",GlgObjectC(GlgObject(0)),-1,0);
   //static vector<int> cdate;static vector<int> ctime;
   curdate.push_back(0);
   curdate.push_back(0);
   curdate.push_back(0);
   curtime.push_back(0);
   curtime.push_back(0);
   curtime.push_back(0);
   previousdate= curdate;
   previoustime =curtime;

}
vector<int> Utility::splitDate(string date,char delimiter)
{
    vector<int> result;
    string word;
    stringstream stream(date);
    while( getline(stream, word, delimiter) )
    {
        int numb;
        istringstream ( word ) >> numb;
        result.push_back(numb);
    }
    return result;
}
time_t Utility::getTime_T(vector<int> value)
{
   time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime( &rawtime );
  cout << value[2]<<" "<<value[0]<<" " <<value[1]<<endl;
  timeinfo->tm_year = value[2] - 1900;
  timeinfo->tm_mon = value[0] - 1;
  timeinfo->tm_mday = value[1];
  return  mktime ( timeinfo );
}

string Utility::convertToUpper(string value)
{
        string result = value;
        char c;
        for(int y=0;y<value.size();y++)
        {
           c = value[y];
           result[y] = (char)toupper(c);
        }
     return result;
}
bool Utility::Validate(vector<int> elems)
{

    int validdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

     int leapyear = 2012;
     bool result = true;


         if(elems.size() < 3 || elems[0] <= 0 || elems[0] > 12 ||  elems[1] <= 0 || elems[1] > 31 || elems[2] < 1900)
            return false;

         if(elems[0] != 2)
         {
            if(elems[1] > validdays[(int)elems[0] - 1])
            {
                  return false;
            }
         }
         else
         {
            bool leapY =  (((int)elems[2] - leapyear) % 4 ) == 0;
            if(leapY )
            {
                if(  elems[1] > (validdays[(int)elems[0] - 1]) + 1 )
                  return false;
            }
            else
            {
                if(  elems[1] > (validdays[(int)elems[0] - 1]))
                  return false;
            }
         }

         if(elems.size() > 3)
         {
              if(elems.size() != 6 || elems[3] < 0 || elems[3] > 23 ||  elems[4] < 0 || elems[4] > 59 || elems[5] < 0 || elems[5] > 59)
                 return false;

         }

     return true;
}
void Utility::InitUtilitiesData(string str,GlgObjectC button,int index,int inittype)
{

    if(inittype == 0)
    {
        ptrDialogs[0] = new PassowrdDialog(parent);
        ptrDialogs[0]->subMenuName = "";
        //ptrDialogs[0]->subMenuIndex = 0;

        ptrDialogs[1] = new StatusDialog(NUMBER_OF_ANALOG_ELEMENTS,parent);
        //ptrDialogs[1] = new StatusDialog();
        ptrDialogs[1]->subMenuName = USER_DEFINED_ANALOG_DIALOG_SCREEN_NAME;
        ptrDialogs[1]->mainMenuName = ANALOG_STATUS_LABEL_STRING;
        ptrDialogs[1]->filename = USER_DEFINED_ANALOG_DIALOG;
        ptrDialogs[2] = new StatusDialog(NUMBER_OF_DIGITAL_ELEMENTS,parent);

        //ptrDialogs[2] = new StatusDialog();
        ptrDialogs[2]->subMenuName = USER_DEFINED_DIGITAL_DIALOG_SCREEN_NAME;
        ptrDialogs[2]->mainMenuName = DIGITAL_STATUS_LABEL_STRING;
        ptrDialogs[2]->filename = USER_DEFINED_DIGITAL_DIALOG;

        ptrDialogs[3] = new PassowrdDialog(parent);

        //Calibration calibration;
        vector<MenuBase*> temp;
        temp.push_back(new ThrottleCalibrationType());//  menues[0][0]
        temp.push_back(new ThrusterCalibrationType());//  menues[0][1]
        temp.push_back(new PitchCalibrationType());    // menues[0][3]
        //for(int i=0;i<3;i++)
           // temp[i]->printData();
        menues.push_back(temp); // menues[0] -> calibrations
        temp.clear();
        temp.push_back(new AdjustPitchControlVariables());     // menues[1][0]
        temp.push_back(new EditThrottleProfiles());            // menues[1][1]
        temp.push_back(new HardwareDiagnostics());             // menues[1][2]
        temp.push_back(new ChangeSystemDate());                // menues[1][3]
        temp.push_back(new CommentEntryScreen());              // menues[1][4]
        temp.push_back(new AnalogAlarmVariableModification(NUMBER_OF_ANALOG_SETPOINT_NAMES,NUMBER_OF_ANALOG_SETPOINTS_IN_EACH_NAME)); // menues[1][5]
        temp.push_back(new DigitalAlarmVariableModification(NUMBER_OF_DIGITAL_SETPOINT_NAMES,NUMBER_OF_DIGITAL_SETPOINTS_IN_EACH_NAME));// menues[1][6]
        temp.push_back(new Diagnostics());
        temp.push_back(new ChangeSerialConfiguration());//menues[1][7]
        menues.push_back(temp); // menues[1] -> utilities menues except calibrations
        temp.clear();
        temp.push_back(new MachineryLogInterval());  // menues[2][0]
        temp.push_back(new SelectableLogGroup());    // menues[2][1]
        temp.push_back(new SerialMapping());         // menues[2][2]
        temp.push_back(new LogRetrievalPage());          // menues[2][3]

        menues.push_back(temp); // menues[2] -> datalogging menues
        temp.clear();

        changePasswordScreen = new ChangePassword();
        for(int i = 0;i < NUMBER_OF_TANK_PAGES; i++)
        {
             temp.push_back(new Tank(TANKS[i]));
        }
        menues.push_back(temp); // menues[3] -> Tank Pages
        temp.clear();
       

    }
    else if(inittype  == 2)
    {
        for(int i=0;i<4;i++)
        {
               if( strcmp(str.c_str() , string(ptrDialogs[i]->subMenuName).c_str()) == 0 )
               {
                   ptrDialogs[i]->subMenuIndex = index;
                   //ptrDialogs[i]->printData();
               }
        }

        for(int i=0;i<menues.size();i++)
        {
            for(int j=0;j<menues[i].size();j++)
            {
                  if( strcmp(str.c_str() , string(menues[i][j]->subMenuName).c_str()) == 0 )
                      menues[i][j]->subMenuIndex = index;
            }
        }
        if(strcmp(str.c_str() , changePasswordScreen->subMenuName.c_str()) == 0)
        {
             changePasswordScreen->subMenuIndex = index;
        }
        else if(parent->MainMenuIndex  == ptrDialogs[1]->mainMenuIndex && str.find(DEFAULT_STATUS_PAGE_NAME)  != string::npos)
        {
                  ANALOG_STATUS_PAGE_NAME.push_back(std::to_string(index + 1) + " " + DEFAULT_STATUS_PAGE_NAME + " " + std::to_string(index + 1));
                  //cout << DIGITAL_STATUS_PAGE_NAME[index] << endl;
                  if(analogStatusPages.size() != 0 )
                  {
                      StatusPage temp = getStatusPage(index, ANALOG_TYPE);
                      if(temp.name != "")
                                button.SetResource( "LabelString", temp.name.c_str());
                      else
                                button.SetResource( "LabelString", ANALOG_STATUS_PAGE_NAME[index].c_str());
                  }
        }
        else if(parent->MainMenuIndex  == ptrDialogs[2]->mainMenuIndex && str.find(DEFAULT_STATUS_PAGE_NAME)  != string::npos)
        {
                  DIGITAL_STATUS_PAGE_NAME.push_back(std::to_string(index + 1) + " " + DEFAULT_STATUS_PAGE_NAME + " " + std::to_string(index + 1));
                               //cout << DIGITAL_STATUS_PAGE_NAME[i] << "  digitalStatusPages.size = " << digitalStatusPages.size() << endl;
                 if(digitalStatusPages.size() != 0 )
                 {
                       StatusPage temp = getStatusPage(index, DIGITAL_TYPE);
                       if(temp.name != "")
                                 button.SetResource( "LabelString", temp.name.c_str());
                       else
                                 button.SetResource( "LabelString", DIGITAL_STATUS_PAGE_NAME[index].c_str());
                 }
         }
    }
    else if(inittype == 1)
    {
        for(int i = 0;i<4;i++)
        {
            if( strcmp(str.c_str() , string(ptrDialogs[i]->mainMenuName).c_str()) == 0)
                ptrDialogs[i]->mainMenuIndex = index;
        }
        if( strcmp(str.c_str() , string(changePasswordScreen->mainMenuName).c_str()) == 0)
        {
             changePasswordScreen->mainMenuIndex = index;
        }
        for(int i =0 ;i<menues.size();i++)
        {
            for(int j =0;j<menues[i].size();j++)
            {
                 if( strcmp(str.c_str() , string(menues[i][j]->mainMenuName).c_str()) == 0)
                     menues[i][j]->mainMenuIndex = index;
            }
        }

    }
    else if(inittype == 3)
    {
        if(index == ptrDialogs[0]->mainMenuIndex)
        {
                       if(parent->PopupDialogVisible)
                       {
                           //currentPopupDialog->CloseDialog(parent,0,-1);
                           //parent->SelectMainMenuItem( index, 0, true );
                       }
                       else
                       {
                        ptrDialogs[0]->type = UTILITY_PERMISSIONS;
                        currentPopupDialog = ptrDialogs[0];
                        set<GlgObjectC *>::iterator it = dialogWidgets.begin();
                        currentPopupDialog->DisplayDialog(parent,(*it));
                       }
        }

        else
        {

                       parent->SelectMainMenuItem( (GlgLong) index, 0,false  );
        }
    }
    else if(inittype == 4)
    {
        if(index == ptrDialogs[2]->subMenuIndex && parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex)
        {
                         if(parent->PopupDialogVisible)
                         {
                              // currentPopupDialog->CloseDialog(parent,0,-1);
                              // parent->SelectMainMenuItem( parent->MainMenuIndex, 0, true );
                         }
                         else
                         {
                            ptrDialogs[2]->type = USER_DEFINED_DIGITAL;
                            ptrDialogs[2]->screenname = "Digital Status Page";
                            currentPopupDialog = ptrDialogs[2];
                            set<GlgObjectC *>::iterator it = dialogWidgets.begin();
                            it++;
                            currentPopupDialog->DisplayDialog(parent,(*it));
                                    //currentPopupDialog->printData();
                            currentPopupDialog->DisplayPage(1,DIGITAL_TYPE,analogStatusPages,&parent->DrawingAreaDialog0,parent);
                         }
        }
        else if(index == ptrDialogs[1]->subMenuIndex  && parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex)
        {
                        if(parent->PopupDialogVisible)
                        {
                           //currentPopupDialog->CloseDialog(parent,0,-1);
                           //parent->SelectMainMenuItem( parent->MainMenuIndex, 0, true );
                        }
                        else
                        {
                            ptrDialogs[1]->type = USER_DEFINED_ANALOG;
                            ptrDialogs[1]->screenname = "Analog Status Page";
                            currentPopupDialog = ptrDialogs[1];
                            set<GlgObjectC *>::iterator it = dialogWidgets.begin();
                            it++;
                            currentPopupDialog->DisplayDialog(parent,(*it));
                            currentPopupDialog->DisplayPage(1,ANALOG_TYPE,analogStatusPages,&parent->DrawingAreaDialog0,parent);
                        }
       }
        else if(index == ptrDialogs[3]->subMenuIndex  && parent->MainMenuIndex == ptrDialogs[3]->mainMenuIndex)
        {
                       if(parent->PopupDialogVisible)
                       {
                            //currentPopupDialog->CloseDialog(parent,0,-1);
                            //parent->SelectMainMenuItem( parent->MainMenuIndex, 0, true );
                       }
                       else
                       {
                            ptrDialogs[3]->type = ADMINISTRATOR_PERMISSTIONS;
                            currentPopupDialog = ptrDialogs[3];
                            set<GlgObjectC *>::iterator it = dialogWidgets.begin();
                            currentPopupDialog->DisplayDialog(parent,(*it));
                            //currentPopupDialog->printData();
                       }
        }
       else
       {
                           parent->SelectSubMenuItem( (GlgLong) index, 0,false );
       }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatusPage Utility::getStatusPage(int pNumber, STATUS_PAGE_TYPE pType)
{
    std::set<StatusPage>::iterator i;
    std::set<StatusPage>::iterator k;
    StatusPage result;
    switch(pType)
    {
        case ANALOG_TYPE:
            i = analogStatusPages.begin();
            k = analogStatusPages.end();
            break;
        case DIGITAL_TYPE:
            i=digitalStatusPages.begin();
            k=digitalStatusPages.end();
            break;
    };
    for(;i != k;i++)
    {
        //cout << (*i).type <<" "<<(*i).name<< " "<<(*i).pageNumber<< "  NumberOfElements  =  "<< (*i).elements.size() << endl;
        if((*i).pageNumber == pNumber + 1)
        {
            result = *i;
        }
    }

    return result;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Utility::printStatusPages()
{
                    std::set<StatusPage>::iterator i;
                    std::set<StatusPage>::iterator k;
                    StatusPage result;
                    STATUS_PAGE_TYPE pType[2] = {ANALOG_TYPE,DIGITAL_TYPE};

                    for(int a=0;a<2;a++)
                    {
                        STATUS_PAGE_TYPE  currentType = pType[a];
                        switch(currentType)
                        {
                            case ANALOG_TYPE:
                                cout << "Analog Pages  = "<< analogStatusPages.size() << endl;
                                i = analogStatusPages.begin();
                                k = analogStatusPages.end();
                                break;
                            case DIGITAL_TYPE:
                                cout << "Digital Pages  = "<< digitalStatusPages.size() << endl;
                                i=digitalStatusPages.begin();
                                k=digitalStatusPages.end();
                                break;
                        };
                        for(;i != k;i++)
                        {
                            cout << (*i).type <<" "<<(*i).name<< " "<<(*i).pageNumber<< "  NumberOfElements  =  "<< (*i).elements.size() << endl;
                            std::set<StatusPageElement *>::iterator j;
                            j = (*i).elements.begin();
                            for( j = (*i).elements.begin();j != (*i).elements.end();j++)
                            {
                                (*j)->printData();//" "<< (*j)->elementIndex << " " << (*j)->elementTag << endl;
                            }

                        }

                    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Utility::DisplayPages(int mainindex,int subindex)
{
   // if(parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex && parent->SubMenuIndex == ptrDialogs[1]->subMenuIndex)
        DisplayStatusPages(ANALOG_TYPE,NUMBER_OF_ANALOG_ELEMENTS,ptrDialogs[1]->mainMenuIndex, subindex,NumberOfAnalogData,analogdata);
   // else if(parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex && parent->SubMenuIndex == ptrDialogs[2]->subMenuIndex)
        DisplayStatusPages(DIGITAL_TYPE,NUMBER_OF_DIGITAL_ELEMENTS,ptrDialogs[2]->mainMenuIndex,subindex,NumberOfDigitalData,digitaldata);
   // else
       DisplayUtilityPages(mainindex, subindex);

}
void Utility::DisplayUtilityPages(int mainindex,int subindex)
{
    if(mainindex == menues[1][4]->mainMenuIndex && subindex == menues[1][4]->subMenuIndex) // || (commentbuttonclicked))  // CommentEntryScreen
    {
       ;
    }
    else if(mainindex == menues[1][0]->mainMenuIndex && subindex == menues[1][0]->subMenuIndex) // Ajust Pitch Control Variable Pages
    {
        AdjustPitchControlVariables * ins = static_cast<AdjustPitchControlVariables *>(menues[1][0]);
        ins->receiveFromDDS(ins->pitchVariables[0].second, ins->pitchVariables[1].second,ins->pitchVariables[2].second,ins->pitchVariables[3].second,parent->pDataFeed);

        for(int i=0;i< NUM_OF_INPUT_VALUES;i++)
        {
            parent->DrawingArea.Viewport.SetResource(ins->pitchVariables[i].first.c_str(),ins->pitchVariables[i].second);
        }
    }
    else if(mainindex == menues[1][1]->mainMenuIndex && subindex == menues[1][1]->subMenuIndex)  // Edit Throttle Profile Pages
    {
        throttleProfileStr currentProfile;
        EditThrottleProfiles* ins = static_cast<EditThrottleProfiles*>(menues[1][1]);
        parent->DrawingArea.Viewport.GetResource(ins->option.first.c_str(),&ins->option.second);
        currentProfile.profileType = (int)ins->option.second;

        for(int i = 0;i < MAXNUMTHROTTLEENTRIES; i++)
        {
            currentProfile.profile[i].pitch = 0;
            currentProfile.profile[i].rpm = 0;
            ins->pitch[i].second = 0;
            ins->rpm[i].second = 0;
        }

        parent->pDataFeed->ReadThrottleProfile(currentProfile.profileType, &currentProfile);
        ins->printsendData(currentProfile,1);

        for(int i = 0;i < NUMBER_OF_THROUTTLE_PROFILES; i++)
        {
            int index = currentProfile.profile[i].ndx + 10;
            if(index > -1 && index <  NUMBER_OF_THROUTTLE_PROFILES)
            {
              ins->pitch[index].second = currentProfile.profile[index].pitch;
              ins->rpm[index].second = currentProfile.profile[index].rpm;
            }  
        }
        for(int i = 0;i < MAXNUMTHROTTLEENTRIES; i++)
        {
            parent->DrawingArea.Viewport.SetResource(ins->pitch[i].first.c_str(),currentProfile.profile[i].pitch);
            parent->DrawingArea.Viewport.SetResource(ins->rpm[i].first.c_str(),currentProfile.profile[i].rpm);
        }
        ins->status.second = "Wait Processing Transaction";
        parent->DrawingArea.Viewport.SetResource(ins->status.first.c_str(),ins->status.second.c_str());
        parent->DrawingArea.Viewport.SetResource(STATUS_VISIBILITY.c_str(),0.0);
        parent->DrawingArea.Viewport.SetResource(BTN_FINISH_VISIBILITY1.c_str(),1.0);

    }
    else if(mainindex == menues[1][2]->mainMenuIndex && subindex == menues[1][2]->subMenuIndex)  //HardwareDiagnostics
    {

    }
    else if(mainindex == menues[1][3]->mainMenuIndex && subindex == menues[1][3]->subMenuIndex)  // ChangeSystemDate
    {
        char * date;
        char * time;
        static_cast<ChangeSystemDate *>(menues[1][3])->receiveFromDDS( &date,&time);
    }

    else if(mainindex == menues[1][5]->mainMenuIndex && subindex == menues[1][5]->subMenuIndex || mainindex == menues[1][6]->mainMenuIndex && subindex == menues[1][6]->subMenuIndex)  // AnalogAlarmVariableModification
    {

    }
    else if(mainindex == menues[1][7]->mainMenuIndex && subindex == menues[1][7]->subMenuIndex)  // Administrator Page
    {
        Diagnostics *ins = static_cast<Diagnostics *>(menues[1][7]);
        ins->opt[0].second = 1.0;
        parent->DrawingArea.Viewport.SetResource(ins->opt[0].first.c_str(),ins->opt[0].second);

        string SvrDiagStr;
        int DiagStrID = 0,status = -1,statusD[5];

           int j =0;

             parent->DrawingArea.Viewport.GetResource(ins->opt[0].first.c_str(),&ins->opt[0].second);
             if(ins->opt[0].second == 1)
             {
                 j=0;
                 parent->DrawingArea.Viewport.SetResource(ins->opt[1].first.c_str(),0.0);
             }
             else  if(ins->opt[1].second == 1)
             {
                 j=1;
                 parent->DrawingArea.Viewport.SetResource(ins->opt[0].first.c_str(),0.0);
             }


                 MPCMS_ServerType ServerID;
                 if(j == 0)
                 {
                      ServerID = MST_PRIMARY;
                      parent->DrawingArea.Viewport.SetResource(ins->opt[1].first.c_str(),0.0);
                 }
                 else if(j==1)
                 {
                     ServerID = MST_SECONDARY;
                     parent->DrawingArea.Viewport.SetResource(ins->opt[0].first.c_str(),0.0);
                 }
                 for(int a=0; a <  ins->statusdisplays.size();a++)
                 {
                    statusD[a] =-1;
                 }
                  bool pr = false;

                    statusD[0] = parent->pDataFeed->ReadSvrIsPrimary(ServerID,&pr);
                    if(statusD[0] != -1)
                    {
                        if(pr)
                        {
                            ins->statusdisplays[0].second  = 1;
                             parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[0].first.c_str(),"TRUE");
                        }
                        else
                        {
                            ins->statusdisplays[0].second  = 0;
                            parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[0].first.c_str(),"FALSE");
                        }
                    }


                  bool ac =false;
                    statusD[1] = parent->pDataFeed->ReadSvrIsActive(ServerID,&ac);
                  if(statusD[1] != -1)
                  {
                      if(ac)
                      {
                          ins->statusdisplays[1].second  = 1;
                          parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[1].first.c_str(),"TRUE");
                      }
                      else
                      {
                          ins->statusdisplays[1].second  = 0;
                         parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[1].first.c_str(),"FALSE");
                      }
                  }
                   bool hb =false;
                    statusD[2] = parent->pDataFeed->ReadSvrReceiveHeartbeat(ServerID,&hb);
                    if(statusD[2] != -1)
                    {
                        if(hb)
                        {
                            ins->statusdisplays[2].second  = 1;
                             parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[2].first.c_str(),"TRUE");
                        }
                        else
                        {
                            ins->statusdisplays[2].second  = 2;
                           parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[2].first.c_str(),"FALSE");
                        }
                    }

                  long pcTemp =-1;
                     statusD[3] = parent->pDataFeed->ReadSvrTemp(ServerID,&pcTemp);
                     if(statusD[3] != -1)
                     {

                             ins->statusdisplays[3].second  = pcTemp;
                             parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[3].first.c_str(), ins->statusdisplays[3].second);
                      }


                  long cycleTime =-1;
                     statusD[4] = parent->pDataFeed->ReadSvrCycleTime(ServerID,&cycleTime);
                     if(statusD[4] != -1)
                     {

                             ins->statusdisplays[4].second  = cycleTime;
                             parent->DrawingArea.Viewport.SetResource(ins->statusdisplays[4].first.c_str(), ins->statusdisplays[4].second);
                     }


                 for(int i=0;i<ins->memory.first.size();i++)
                 {
                    status = ins->receiveFromDDS(ServerID, SvrDiagStr, i, parent->pDataFeed);
                    if(status == -1)
                    {
                             ins->memory.first[i].second = "DataFeed::ReadSvrDiagnosticStr: ServerID ERROR";
                    }
                    else
                    {
                        if(strlen(SvrDiagStr.c_str()) != 0)
                        {
                                ins->memory.first[i].second = SvrDiagStr;//string(SvrDiagStr);
                        }
                        else
                        {
                             ins->memory.first[i].second = string("");
                        }
                    }
                    parent->DrawingArea.Viewport.SetResource(ins->memory.first[i].first.c_str(),ins->memory.first[i].second.c_str());
                 }

                 for(int i = 0;i < ins->channels.size();i++)
                 {
                     status = -1;
                     ins->channels[i].first.second = -1;
                     status = parent->pDataFeed->ReadSvrSerialErrCount(ServerID, &ins->channels[i].first.second, i);
                     parent->DrawingArea.Viewport.SetResource(ins->channels[i].first.first.c_str(), (double)ins->channels[i].first.second);

                     status = -1;
                     ins->channels[i].second.second = -1;
                     status = parent->pDataFeed->ReadSvrSerialTimeout(ServerID, &ins->channels[i].second.second, i);
                     if(ins->channels[i].second.second)
                     {
                        parent->DrawingArea.Viewport.SetResource(ins->channels[i].second.first.c_str(), "TRUE");
                     }
                     else
                     {
                         parent->DrawingArea.Viewport.SetResource(ins->channels[i].second.first.c_str(), "FALSE");
                     }

                 }

    }
    else if(mainindex == menues[1][8]->mainMenuIndex && subindex == menues[1][8]->subMenuIndex) // Change Serial Configuration
    {
        ChangeSerialConfiguration * ins =  static_cast<ChangeSerialConfiguration *>(menues[1][8]);
        ins->receiveFromDDS(parent);
    }
    else if(mainindex == menues[2][0]->mainMenuIndex && subindex == menues[2][0]->subMenuIndex)  // MachineryPantStatus Logging
    {
        //double interval=-1;
        MachineryLogInterval * ins = static_cast<MachineryLogInterval *>(menues[2][0]);

        ins->receiveFromDDS( intervalTxt.second ,parent->pDataFeed);
        parent->DrawingArea.Viewport.SetResource(ins->periodTxt.first.c_str(),0.0);
        const char * interv = to_string((int)intervalTxt.second).c_str();
        parent->DrawingArea.Viewport.SetResource("intervalTxt/TextString",interv);

    }
    else if(mainindex == menues[2][1]->mainMenuIndex && subindex == menues[2][1]->subMenuIndex)  // Selectable Log
    {
        SelectableLogGroup * ins = static_cast<SelectableLogGroup *>(menues[2][1]);
         /*parent->DrawingArea.Viewport.GetResource(ins->optionindex.first.c_str(),&ins->optionindex.second);
         parent->DrawingArea.Viewport.GetResource(ins->lognumber.first.c_str(),&ins->lognumber.second);

         for(int i =0;i< NUMBER_OF_LOG_ELEMENTS;i++)
         {
                ins->logElements[i].second = "";
                parent->DrawingArea.Viewport.SetResource(ins->logElements[i].first.c_str(),ins->logElements[i].second.c_str());
         }*/
         ins->receiveFromDDS(parent);




    }
    else if(mainindex == menues[2][2]->mainMenuIndex && subindex == menues[2][2]->subMenuIndex)  // Serial Mapping
    {
        parent->DrawingArea.Viewport.SetResource(static_cast<SerialMapping *>(menues[2][2])->checkboxDPS.first.c_str(),0.0);
        parent->DrawingArea.Viewport.SetResource(static_cast<SerialMapping *>(menues[2][2])->checkboxDDS.first.c_str(),0.0);
        for(int i = 0;i< NUMBER_OF_DPS_ROWS;i++)
        {
             parent->DrawingArea.Viewport.SetResource(static_cast<SerialMapping *>(menues[2][2])->dpsraws[i].first.c_str(),"");
        }
        for(int i = 0;i< NUMBER_OF_DDS_ROWS;i++)
        {
             parent->DrawingArea.Viewport.SetResource(static_cast<SerialMapping *>(menues[2][2])->ddsraws[i].first.c_str(),"");
        }
    }
    else if(mainindex == menues[2][3]->mainMenuIndex && subindex == menues[2][3]->subMenuIndex)  // Log Retrieval
    {
        /* char * pdaterangelow = (char *)"";
         char * pdaterangehigh = (char *)"";
         double check0[2], check1[3], check2[1],check3[7];

         LogRetrievalPage * ins = static_cast<LogRetrievalPage *>(menues[2][3]);
         ins->receiveFromDDS(&pdaterangelow,&pdaterangehigh,check0,check1,check2,check3,parent->pDataFeed);
         parent->DrawingArea.Viewport.SetResource(ins->daterangelow.first.c_str(),pdaterangelow);
         parent->DrawingArea.Viewport.SetResource(ins->daterangehigh.first.c_str(),pdaterangehigh);
         for(int i=0;i< ins->checkBoxes.size();i++)
         {
             for(int j =0;j< ins->checkBoxes[i].size();j++)
             {
                 switch(i)
                 {
                    case 0:
                       parent->DrawingArea.Viewport.SetResource(ins->checkBoxes[i][j].first.c_str(),check0[j]);
                    break;
                    case 1:
                       parent->DrawingArea.Viewport.SetResource(ins->checkBoxes[i][j].first.c_str(),check1[j]);
                    break;
                    case 2:
                        parent->DrawingArea.Viewport.SetResource(ins->checkBoxes[i][j].first.c_str(),check2[j]);
                    break;
                    case 3:
                        parent->DrawingArea.Viewport.SetResource(ins->checkBoxes[i][j].first.c_str(),check3[j]);
                    break;


                 }
             }
         }*/
    }

}
void Utility::DisplayStatusPages(STATUS_PAGE_TYPE pType,int TotalNumberOfPages,int mainMenuIndex, int subMenuIndex,int NumberOfData,string * data)
{
    /*if(currentPopupDialog != 0 )
    {
        currentPopupDialog->CloseDialog(parent,3,-1);
    }*/

    if(currentPopupDialog == 0 || (currentPopupDialog != 0 && !currentPopupDialog->popupactive) )
    {
        string elem;
        string boxNumber;


       if(parent->MainMenuIndex == mainMenuIndex && parent->SubMenuIndex == subMenuIndex)
       //if(parent->MainMenuIndex == mainMenuIndex && subMenuIndex != -1)
       {
           for(int i =0;i<TotalNumberOfPages;i++)
           {
               boxNumber = "elem" + to_string(i + 1) + "/" + METER_NUMBER;
               //cout << "ELEMENT boxNumber ="<< boxNumber << endl;
               parent->DrawingArea.Viewport.SetResource(boxNumber.c_str(),double(i + 1));
               for(int k=0;k<NumberOfData;k++)
               {
                   elem = "elem" + to_string(i + 1) + "/" + data[k];
                   if(k == NumberOfData - 1 && pType == ANALOG_TYPE)
                   {
                       //parent->DrawingArea.Viewport.SetResource(elem.c_str(),"");
                   }
                   else
                   {

                      elem = elem + "/Visibility";
                      //cout << elem << endl;
                      parent->DrawingArea.Viewport.SetResource(elem.c_str(),0.);

                   }
               }

           }
           //StatusPage temp = getStatusPage(subMenuIndex, pType);
           StatusPage temp = ReadPageFromDB(  subMenuIndex,  pType);
           //cout << "Current main menu Index = "<< MainMenuIndex << "Type = " << pType << endl;
          // cout << " Page Number = " << temp.pageNumber - 1 << " SubMenuIndex   = "<< SubMenuIndex  <<endl;
           if(temp.pageNumber - 1 == subMenuIndex)
           {
                  // parent->DrawingArea.Viewport.SetResource(elem.c_str(),1.);
                   set<StatusPageElement*>::iterator i = temp.elements.begin();
                   set<StatusPageElement*>::iterator j = temp.elements.end();


                        string dbNumber;
                        for(;i!= j;i++)
                        {
                            elem = "elem" + to_string((*i)->elementIndex.second + 1) + "/" + (*i)->dbNumber.first + "/String";
                            parent->DrawingArea.Viewport.SetResource(elem.c_str(),(*i)->dbNumber.second.c_str());

                            elem = "elem" + to_string((*i)->elementIndex.second + 1) + "/" + PAGE_TEXT + "/String";
                            parent->DrawingArea.Viewport.SetResource(elem.c_str(),"");

                            elem = "elem" + to_string((*i)->elementIndex.second + 1) + "/" + (*i)->pageNumber.first + "/String";
                            parent->DrawingArea.Viewport.SetResource(elem.c_str(),"");

                            elem = "elem" + to_string((*i)->elementIndex.second + 1)  + "/Instance/PageText/String";
                            parent->DrawingArea.Viewport.SetResource(elem.c_str(),"");

                            if(pType == ANALOG_TYPE)
                            {

                                AnalogStatusPageElement * ins = static_cast<AnalogStatusPageElement *>(*i);

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/" + ins->unit.first;
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->unit.second.c_str());

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/Instance/ParameterNameTextTag1";
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->parameterName[0].second.c_str());

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/Instance/ParameterNameTextTag2";
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->parameterName[1].second.c_str());

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/" + ins->minValue.first + "/Low";
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->minValue.second);

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/" + ins->maxValue.first + "/High";
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->maxValue.second);

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/" + ins->currentValue.first + "/Value";
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->currentValue.second);
                            }
                            else if(pType == DIGITAL_TYPE)
                            {
                                DigitalStatusPageElement * ins = static_cast<DigitalStatusPageElement *>(*i);

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/" + ins->currentValue.first + "/String";

                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->currentValue.second.c_str());

                                elem = "elem" + to_string(ins->elementIndex.second + 1) + "/Instance/ParameterNameTextTag1";
                                parent->DrawingArea.Viewport.SetResource(elem.c_str(),ins->parameterName.second.c_str());
                            }

                        }


                   i = temp.elements.begin();
                   j = temp.elements.end();
                   for(;i!= j;i++)
                   {
                      for(int k=0;k<NumberOfData;k++)
                      {
                       elem = "elem" + to_string((*i)->elementIndex.second + 1) + "/" + data[k];
                       if(k == NumberOfData - 1 && pType == ANALOG_TYPE)
                       {
                           //cout << "ELEMENT String ="<< elem << endl;
                           //parent->DrawingArea.Viewport.SetResource(elem.c_str(),"");
                       }
                       else
                       {
                         //cout << elem << endl;
                         elem = elem + "/Visibility";
                         parent->DrawingArea.Viewport.SetResource(elem.c_str(),1.);
                       }

                      }

                  }

                  //temp.printData();
           }
       }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Utility::ReadPagesFromDB()
{
    int a =-1;
    if(startup[0] && ptrDialogs[1]->mainMenuIndex)

        a = 0;

    else if(startup[1] && parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex)
        a = 1;

   //if(startup[0])
   //{
    if((startup[0] && parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex) || (startup[1] && parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex))
    {
        if(startup[0] && parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex)
            startup[0] =false;
        else if(startup[1] && parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex)
            startup[1] =false;

        //startup = false;
       // insert into   analogStatusPages;
       // insert into   digitalStatusPages;
        std::set<StatusPage>::iterator i;
        std::set<StatusPage>::iterator k;
        const char * t1;
        char * t2=0 ;
        char * t3=0;
        set<StatusPageElement *> pCurrentElements;
        StatusPageElement *currentElement;
        STATUS_PAGE_TYPE pType[2] = {ANALOG_TYPE,DIGITAL_TYPE};
        string datapoint[2] = {"ua","ud"};
        int amount[2] = {NUMBER_OF_ANALOG_ELEMENTS,NUMBER_OF_DIGITAL_ELEMENTS};

        analogStatusPages.clear();
        digitalStatusPages.clear();

        //for(int a=0;a<2;a++)
        if(a != -1)
        {

            for(int b=0;b < NUMBER_OF_PAGES;b++)
            {

                STATUS_PAGE_TYPE currentType = pType[a];
                char  * pageName = 0;
                pCurrentElements.clear();
                for(int c = 0; c < amount[a]; c++)
                {
                    string currentdatapoint;// = datapoint[a] + to_string(b + 1) + "c" + to_string(c);
                    if( (b + 1) < 10 && (c + 1) < 10)
                                    currentdatapoint = datapoint[a] + "0" + to_string(b + 1) + "c" + "0" + to_string(c+1);
                    else if(  (b + 1) < 10 && (c + 1) >= 10)
                                    currentdatapoint = datapoint[a] + "0" + to_string(b + 1) + "c" + to_string(c+1);
                    else if( (b + 1) >= 10 && (c + 1) < 10)
                                    currentdatapoint = datapoint[a]  + to_string(b + 1)  + "c" + "0" + to_string(c+1);
                    else if( (b + 1) >= 10 && (c + 1) >= 10)
                                    currentdatapoint = datapoint[a]  + to_string(b + 1)  + "c" + to_string(c+1);

                    char * pTag = (char *)currentdatapoint.c_str();
                    char  pid[20] ;
                    char  pTitle[50];
                    for(int x=0;x<20;x++)
                    {
                        pid[x] = '\0';
                    }
                    for(int x=0;x<50;x++)
                    {
                        pTitle[x] = '\0';
                    }
                    char * pId = &pid[0];
                    pageName = &pTitle[0];
                    DEBUGF_VDT("START READING PAGE FROM DB CDataFeed.ReadPageToDB: PointID = [%s], TAG = %s, PAGE NAME = %s\n",pTag, pId, pageName);
                    parent->pDataFeed->ReadUserConfigPage(pTag,pId,pageName);
                    DEBUGF_VDT("RESPONCE FROM CDataFeed.ReadPageToDB: PointID = [%s], TAG = %s, PAGE NAME = %s\n",pTag, pId, pageName );
                    //cout << endl;
                    //cout << "RECEIVED Page = " << strlen(pId )<< "  : " << strlen(pageName) << " " << pTag << " "<< pId << " " << pageName << endl;
                    //cout << endl;
                    if(strlen(pId ) != 0)
                    {
                        pair<string,int> tempElemIndex(ELEMENT_NUMBER[c],c);
                        pair<string,string> tempelementTag(TAG_NAME[c],pId);
                        switch(currentType)
                        {
                            case ANALOG_TYPE:
                                    currentElement = new AnalogStatusPageElement(tempElemIndex,tempelementTag );
                                    break;
                            case DIGITAL_TYPE:
                                   currentElement = new DigitalStatusPageElement(tempElemIndex,tempelementTag);
                                    break;
                        };
                        pCurrentElements.insert(currentElement);

                    }
                }
                StatusPage temppage;
                if(strlen(pageName) != 0)
                {
                    StatusPage t(pType[a],pageName,b + 1, pCurrentElements);
                    temppage = t;
                }
                else
                {
                    string name = std::to_string(b + 1) + " " + DEFAULT_STATUS_PAGE_NAME + " " + std::to_string(b + 1);
                    pageName = (char*)name.c_str();
                    StatusPage t(pType[a],pageName,b + 1, pCurrentElements);
                    temppage = t;
                }
                switch(currentType)
                {
                    case ANALOG_TYPE:
                        analogStatusPages.insert(temppage);
                    break;
                    case DIGITAL_TYPE:
                        digitalStatusPages.insert(temppage);
                    break;
                };

            }
        }
        //printStatusPages();
   }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Utility::WritePageToDB( StatusPage *i,STATUS_PAGE_TYPE currentType,string &status)
{
      cout <<"Start writing the pages"<<endl;

        std::set<StatusPageElement *>::iterator j;
        string statuslbl[3]={"In Progress","Completed", "Server Error"};
        string validid = "";
        string notvalidid = "";
        string datapoint="u";
        bool isvalidid = true;
        int countid =0,count=-1;
        switch(currentType)
        {
            case ANALOG_TYPE:

                datapoint = datapoint + "a";
                count = 12;
                break;
            case DIGITAL_TYPE:

                   datapoint = datapoint + "d";
                   count = 20;
                   break;
        };

        j = (*i).elements.begin();
        string currentdatapoint = datapoint;
        int el[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        for(int v=0;v<count;v++)
        {
            for( j = (*i).elements.begin();j != (*i).elements.end();j++)
            {
                el[(*j)->elementIndex.second] = 1;
            }
        }

        for( j = (*i).elements.begin();j != (*i).elements.end();j++)
        {
            if((*i).pageNumber < 10 && (*j)->elementIndex.second < 10)
                currentdatapoint = datapoint + "0" + to_string((*i).pageNumber) + "c" + "0" + to_string((*j)->elementIndex.second + 1);
            else if((*i).pageNumber < 10 && (*j)->elementIndex.second >= 10)
                currentdatapoint = datapoint + "0" + to_string((*i).pageNumber) + "c" + to_string((*j)->elementIndex.second + 1);
            else if((*i).pageNumber >= 10 && (*j)->elementIndex.second < 10)
                currentdatapoint = datapoint  + to_string((*i).pageNumber) + "c" + "0" + to_string((*j)->elementIndex.second + 1);
            else if((*i).pageNumber >= 10 && (*j)->elementIndex.second >= 10)
                currentdatapoint = datapoint  + to_string((*i).pageNumber) + "c" + to_string((*j)->elementIndex.second + 1);

            char * tagname =  (char *)currentdatapoint.c_str();
            string tempid = convertToUpper((*j)->elementTag.second);
            char * pointid = (char *)tempid.c_str();
            char * title = (char *)((*i).name.c_str());

            DEBUGF_VDT("START SENDING CDataFeed.WritePageToDB: PointID = [%s], TAG = %s, PAGE NAME = %s\n",tagname, pointid, title );

            isvalidid = parent->pDataFeed->ValidateDataPoint(tempid);
            if(isvalidid)
            {
                countid++;
                validid = validid + "[" + tempid + "]";
            }
            else
            {
                 notvalidid = notvalidid + "[" + tempid + "]";
            }
            if(isvalidid)
            {
                cout << "Sending Page : "<< tagname << "  pointid = [" << pointid << "]  "<<  title << endl;
                parent->pDataFeed->WriteUserConfigPage(tagname,pointid,title);
            }

            DEBUGF_VDT("RESPONCE FROM CDataFeed.WritePageToDB: PointID = [%s], TAG = %s, PAGE NAME = %s\n",tagname, pointid, title );

        }
        status = status + "Complete. ";
        if(validid != "")
        {
             status = status + "Valid PointIDs " + validid;
        }
        if(notvalidid != "")
        {
             status = status + " Invalid PointIDs  " + notvalidid;
        }

        for(int v=0;v<count;v++)
        {
            if(el[v] == 0)
            {
                if((*i).pageNumber < 10 && v + 1  < 10)
                    currentdatapoint = datapoint + "0" + to_string((*i).pageNumber) + "c" + "0" + to_string(v + 1);
                else if((*i).pageNumber < 10 && v + 1 >= 10)
                    currentdatapoint = datapoint + "0" + to_string((*i).pageNumber) + "c" + to_string(v + 1);
                else if((*i).pageNumber >= 10 && v + 1 < 10)
                    currentdatapoint = datapoint  + to_string((*i).pageNumber) + "c" + "0" + to_string(v + 1);
                else if((*i).pageNumber >= 10 && v + 1 >= 10)
                    currentdatapoint = datapoint  + to_string((*i).pageNumber) + "c" + to_string(v + 1);

                char * tagname =  (char *)currentdatapoint.c_str();
                char * pointid = (char*)"";
                char * title = (char *)((*i).name.c_str());

                cout << "Sending Page : "<< tagname << "  pintid = [" << pointid << "]  "<<  title << endl;
                parent->pDataFeed->WriteUserConfigPage(tagname,pointid,title);

            }
        }
        cout <<"Finished writing the pages"<<endl;

}
StatusPage Utility::ReadPageFromDB(  int pNumber, STATUS_PAGE_TYPE currentType)
{

 const char * t1;
 char * t2=0 ;
 char * t3=0;
 set<StatusPageElement *> pCurrentElements;
 StatusPageElement *currentElement;
 STATUS_PAGE_TYPE pType[2] = {ANALOG_TYPE,DIGITAL_TYPE};
 string datapoint[2] = {"ua","ud"};
 int amount[2] = {NUMBER_OF_ANALOG_ELEMENTS,NUMBER_OF_DIGITAL_ELEMENTS};

    int count = -1;
    string dpoint;
    if(currentType == ANALOG_TYPE)
    {
       count = amount[0];
       dpoint = datapoint[0];
    }
    else if(currentType == DIGITAL_TYPE)
    {
       count = amount[1];
       dpoint = datapoint[1];
    }
    char  * pageName = 0;

         for(int c = 0; c < count ; c++)
         {
             string currentdatapoint;
             if( (pNumber + 1) < 10 &&  (c + 1) < 10)
                                 currentdatapoint = dpoint + "0" + to_string(pNumber + 1) + "c" + "0" + to_string(c + 1);
             else if(  (pNumber + 1) < 10 && (c + 1) >= 10)
                                 currentdatapoint = dpoint + "0" + to_string(pNumber + 1) + "c" + to_string(c + 1);
             else if( (pNumber + 1) >= 10 && (c + 1) < 10)
                                 currentdatapoint = dpoint  + to_string(pNumber + 1)  + "c" + "0" + to_string(c + 1);
             else if( (pNumber + 1) >= 10 && (c + 1) >= 10)
                                 currentdatapoint = dpoint  + to_string(pNumber + 1)  + "c" + to_string(c + 1);

             char * pTag = (char *)currentdatapoint.c_str();
             char  pid[20] ;
             char  pTitle[50];
             for(int x=0;x<20;x++)
             {
                 pid[x] = '\0';
             }
             for(int x=0;x<50;x++)
             {
                 pTitle[x] = '\0';
             }
             char * pId = &pid[0];
             pageName = &pTitle[0];


             parent->pDataFeed->ReadUserConfigPage(pTag,pId,pageName);
             cout << endl;
             cout << "RECEIVED Page = " << strlen(pId )<< "  : " << strlen(pageName) << " " <<pTag << " "<< pId << " : " << pageName << endl;
             cout << endl;
             //DEBUG_VDT("GetUSERDEFINEDTagData: tag_record->tag_source, tag_record->tag_name DDS = [%s], [%s], [%s]\n", tag_record->tag_source, tag_record->tag_name, string_ptr);
             if(strlen(pId ) != 0)
             {
                 pair<string,int> tempElemIndex(ELEMENT_NUMBER[c],c);
                 pair<string,string> tempelementTag(TAG_NAME[c],pId);
                 int len;
                 float maxValue=-1;
                 double currentValue=-1;
                 Contact_States_Type evalue;
                 float minValue=-1;
                 int status;

                 char  units[20] ;
                 char  longname[150];
                 for(int x=0;x<20;x++)
                 {
                     units[x] = '\0';
                 }
                 for(int x=0;x<150;x++)
                 {
                     longname[x] = '\0';
                 }

                 switch(currentType)
                 {
                         case ANALOG_TYPE:
                                 currentElement = new AnalogStatusPageElement(tempElemIndex,tempelementTag );
                                 currentElement->dbNumber.second = currentElement->elementTag.second;

                                 len = 20;
                                 status = -1;
                                 status = parent->pDataFeed->ReadEngineeringUnits(pId,units,len);
                                 if(status != -1)
                                 {
                                    if(strlen(units) == 0 )
                                        static_cast<AnalogStatusPageElement *>(currentElement)->unit.second = "";
                                    else
                                        static_cast<AnalogStatusPageElement *>(currentElement)->unit.second = string(units);
                                 }
                                 len =150;
                                 status = -1;
                                 status = parent->pDataFeed->ReadLongName(pId,longname,len);
                                 if(status != -1)
                                 {
                                     int length = strlen(longname);
                                    if(length == 0)
                                        static_cast<AnalogStatusPageElement *>(currentElement)->parameterName[0].second = "";
                                    else
                                    {
                                        if(length < 25)
                                        {
                                           char temp1[26];
                                           int i=0;
                                           for( i=0;i<25;i++)
                                           {
                                               if(i<length)
                                                   temp1[i] = longname[i];
                                               else
                                                  temp1[i] = ' ';
                                           }
                                           temp1[i] = '\0';

                                           static_cast<AnalogStatusPageElement *>(currentElement)->parameterName[0].second = string(temp1);
                                           static_cast<AnalogStatusPageElement *>(currentElement)->parameterName[1].second = string("");
                                        }
                                        else
                                        {

                                            char temp1[26];
                                            const int l=length - 25;
                                            char temp2[26];
                                            int i=0;
                                            for( i=0;i<25;i++)
                                            {
                                                    temp1[i] = longname[i];
                                            }
                                            temp1[i] = '\0';
                                            for( i=0;i<25;i++)
                                            {
                                                if(i<l)
                                                    temp2[i] = longname[25 + i];
                                                else
                                                   temp2[i] = ' ';
                                            }
                                            temp2[i] = '\0';
                                           // memcpy ( temp1, longname, 26 );
                                          //  memcpy ( temp2, longname + 26,l );

                                            static_cast<AnalogStatusPageElement *>(currentElement)->parameterName[0].second = string(temp1);
                                            static_cast<AnalogStatusPageElement *>(currentElement)->parameterName[1].second = string(temp2);
                                        }
                                    }
                                 }

                                 minValue = (long)parent->pDataFeed->ReadEngineeringLow(pId);
                                 static_cast<AnalogStatusPageElement *>(currentElement)->minValue.second = minValue;

                                 maxValue =  (long)parent->pDataFeed->ReadEngineeringHigh(pId);
                                 static_cast<AnalogStatusPageElement *>(currentElement)->maxValue.second = maxValue;

                                 status = parent->pDataFeed->ReadRTUDAnalogValue(pId,currentValue);
                                 static_cast<AnalogStatusPageElement *>(currentElement)->currentValue.second = currentValue;

                                 break;

                         case DIGITAL_TYPE:
                                currentElement = new DigitalStatusPageElement(tempElemIndex,tempelementTag);
                                currentElement->dbNumber.second = currentElement->elementTag.second;

                                len =150;
                                status = -1;
                                status = parent->pDataFeed->ReadLongName(pId,longname,len);
                                if(status != -1)
                                {
                                   if(strlen(longname) == 0)
                                       static_cast<DigitalStatusPageElement *>(currentElement)->parameterName.second = "";
                                   else
                                       static_cast<DigitalStatusPageElement *>(currentElement)->parameterName.second = string(longname);
                                }
                                status = parent->pDataFeed->ReadRTUDDigitalValue(pId,&evalue);
                                if(status != -1)
                                {
                                   static_cast<DigitalStatusPageElement *>(currentElement)->currentValue.second = CURRENT_VALUE_NAMES[(int)evalue];
                                }
                                else
                                {
                                    static_cast<DigitalStatusPageElement *>(currentElement)->currentValue.second = to_string(-1);
                                }
                                break;
                 };

                 pCurrentElements.insert(currentElement);

             }
         }
         StatusPage temppage;
         if(strlen(pageName) != 0)
         {
             StatusPage t(currentType,pageName,pNumber + 1, pCurrentElements);
             temppage = t;
         }
         else
         {
             string name = std::to_string(pNumber + 1) + " " + DEFAULT_STATUS_PAGE_NAME + " " + std::to_string(pNumber + 1);
             pageName = (char*)name.c_str();
             StatusPage t(currentType,pageName,pNumber + 1, pCurrentElements);
             temppage = t;
         }

          StatusPage p;
           set<StatusPage>::iterator it;
         switch(currentType)
         {
             case ANALOG_TYPE:
                  for(it = analogStatusPages.begin();it != analogStatusPages.end();it++)
                  {
                       if(it->pageNumber == temppage.pageNumber)
                           p=*it;
                  }
                  analogStatusPages.erase(p);
                  analogStatusPages.insert(temppage);
                break;
             case DIGITAL_TYPE:
                for(it = digitalStatusPages.begin();it != digitalStatusPages.end();it++)
                {
                  if(it->pageNumber == temppage.pageNumber)
                      p=*it;
                }
                digitalStatusPages.erase(p);
                digitalStatusPages.insert(temppage);
                break;
         };

         //printStatusPages();
         int a=-1;
         return temppage;

}
void Utility::ProcessInput(MenuBase * instance,string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrGlgDrawingArea,bool option)
{
            //instance->printData();
            instance->ProcessInput(btn, viewport,message,ptrGlgDrawingArea,parent);
            instance = 0;
}

void  Utility::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrGlgDrawingArea)
{
    if(currentPopupDialog != 0)
    {
        ProcessInput(currentPopupDialog,btn, viewport,message,ptrGlgDrawingArea,true);
        if(!parent->PopupDialogVisible)
            currentPopupDialog = 0;
    }
    else
    {
        for(int i=0;i< menues.size();i++)
        {
            for(int j=0;j<menues[i].size();j++)
            {
                //menues[i][j]->printData();
                if( (parent->MainMenuIndex == menues[i][j]->mainMenuIndex &&  parent->SubMenuIndex == menues[i][j]->subMenuIndex) )//|| commentbuttonclicked)
                {
                     int a,b;
                    /* if(commentbuttonclicked)
                     {
                       a = 1;b=4;
                     }
                     else
                     {
                         a=i;b=j;
                     }*/
                     ProcessInput(menues[i][j],btn, viewport,message,ptrGlgDrawingArea,false);
                     break;
                }
            }
        }
        if( parent->MainMenuIndex == changePasswordScreen->mainMenuIndex &&  parent->SubMenuIndex == changePasswordScreen->subMenuIndex)
        {
             ProcessInput(changePasswordScreen,btn, viewport,message,ptrGlgDrawingArea,false);
        }
    }
}

void Utility::ProcessInput(string action,string origin, GlgDrawingArea * drawingArea)
{

     if(currentPopupDialog != 0 && origin == "PageNumberOption")
     {
        currentPopupDialog->ProcessInput(action, drawingArea,parent);
     }
     else if(currentPopupDialog != 0 && origin != "PageNumberOption")
     {

     }
     else if(strcmp( origin.c_str() , "LogAllDataButton" ) == 0 )
     {
         printf("Log all data points1\n");

         printf("Log all data points2\n");
         drawingArea->parent->LogAllDataBasePointButton.SetResource("Visibility",-0.3);
         timer(TIME_DELAY_LOG_ALL_DATA,  LogAllData,drawingArea->parent);
         timer(TIME_DELAY_FOR_LOG_ALL_DATA_POINTS,  DelayLog,drawingArea->parent);
         printf("Log all data points3\n");

     }
     else if(strcmp( origin.c_str() , "CommentLogButton" ) == 0)
     {

       CommentEntryScreen * inst = static_cast<CommentEntryScreen *>(menues[1][4]);

       parent->SelectMainMenuItem(inst->mainMenuIndex,0,false);
       parent->SelectSubMenuItem(inst->subMenuIndex,0,false);
       parent->MainMenu.SetResource( "SelectedIndex", parent->MainMenuIndex );
       parent->SubMenu.SetResource( "SelectedIndex", parent->SubMenuIndex );


       /////////////////////////////////////////////////////////////////////////////
     }

     else
     {
         for(int i=0;i< menues.size();i++)
         {
             for(int j=0;j<menues[i].size();j++)
             {
                 //menues[i][j]->printData();
                 if( parent->MainMenuIndex == menues[i][j]->mainMenuIndex &&  parent->SubMenuIndex == menues[i][j]->subMenuIndex)
                 {
                      menues[i][j]->ProcessInput(action,origin,drawingArea);

                      break;
                 }
             }
         }

     }
}
 void Utility::ProcessTags(GlgSCADAViewer *ptr,GlgTagRecord *tag_record,double value,bool option,int start,int end)
 {
      if(ptr->MainMenuIndex == menues[3][0]->mainMenuIndex)
      {
        for(int i=0;i<menues[3].size();i++)
        {
            if(ptr->SubMenuIndex == menues[3][i]->subMenuIndex)
            {

                static_cast<Tank *>(menues[3][i])->ProcessTags(ptr,tag_record,value,option,start,end,i);
            }
        }
      }
      else if(ptr->MainMenuIndex == menues[0][0]->mainMenuIndex)// SubMenuIndex == utility->menues[0][0]) || (MainMenuIndex == utility->menues[0][1] && SubMenuIndex == utility->menues[0][1]) || (MainMenuIndex == utility->menues[0][2] && SubMenuIndex == utility->menues[0][0]))
      {
          for(int i=0;i<menues[0].size();i++)
          {
              if(ptr->SubMenuIndex == menues[0][i]->subMenuIndex)
              {

                  //static_cast<Calibration *>(menues[0][i])->SetClutchState(ptr,tag_record,value,start,end,i);
                    static_cast<Calibration *>(menues[0][i])->SetStates(ptr,tag_record,value,start,end,i);
              }
          }
      }
      //if(curdate != previousdate && curtime != previoustime)
      // get time from DB in curdate, curtime
           //setSystemTime(curdate,curtime);
 }
 void Utility::UpdateUserPages(int mainindex,int subindex)
 {
     if(mainindex == ptrDialogs[1]->mainMenuIndex && subindex != ptrDialogs[1]->subMenuIndex)
         DisplayStatusPages(ANALOG_TYPE,NUMBER_OF_ANALOG_ELEMENTS,mainindex,subindex,NumberOfAnalogData,analogdata);
     else if(mainindex == ptrDialogs[2]->mainMenuIndex && subindex != ptrDialogs[2]->subMenuIndex)
         DisplayStatusPages(DIGITAL_TYPE,NUMBER_OF_DIGITAL_ELEMENTS,mainindex,subindex,NumberOfDigitalData,digitaldata);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Utility::setDataPoint(char ** point,char ** tag,char ** pagename)
{
    cout << " Send Data = " << point << " "<< tag << " "<< pagename << endl;
}
void Utility::getDataPoint(char ** point,char **tag,char **pagename )
{
    *tag = (char *)"DOS-103";
    *pagename = (char *)"My Page TestPage ";
    //cout << *tag << *pagename << endl;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Utility::PageDown()
{
    int index =-1;
    index = parent->MainMenuArray[parent->MainMenuIndex].num_submenu_items - 1;

    if(parent->MainMenuIndex == ptrDialogs[3]->mainMenuIndex )
    {

         /* if(previousSubIndex == ptrDialogs[3]->subMenuIndex )
          {

              parent->SelectSubMenuItem(ptrDialogs[3]->subMenuIndexPrevious,0,true);
              previousSubIndex=-1;
          }
          else
          {*/
            //ptrDialogs[3]->subMenuIndexPrevious = parent->SubMenuIndex;
            //previousSubIndex = ptrDialogs[3]->subMenuIndex;
            parent->SubMenuIndex = index;
            parent->SubMenu.SetResource( "SelectedIndex",  parent->SubMenuIndex);
            InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,4);
         // }

    }
    else if((parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex  ) || (parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex ))
    {
          InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,4);
          previousSubIndex = -1;
    }
    else
    {
        parent->SelectSubMenuItem(index,0,true);
        previousSubIndex=-1;
    }
    parent->Update();
}
//////////////////////////////////////////////////////////////////////////////////////////////////
 void Utility::PageUp()
 {
     parent->SelectSubMenuItem( 0, 0, true );

     parent->Update();
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////
 void Utility::PageErrowUp()
 {
     int index =-1;

     if(parent->SubMenuIndex == 0)
      index = parent->MainMenuArray[parent->MainMenuIndex].num_submenu_items - 1 ;
     else
      index = parent->SubMenuIndex - 1;
     if(parent->MainMenuIndex == ptrDialogs[3]->mainMenuIndex && index == ptrDialogs[3]->subMenuIndex)
     {
            //ptrDialogs[3]->subMenuIndexPrevious = parent->SubMenuIndex;
           /* if(previousSubIndex == ptrDialogs[3]->subMenuIndex)
            {
                index = previousSubIndex - 1;
                parent->SelectSubMenuItem(index,0,true);
                previousSubIndex=-1;
            }
            else
            {*/
                //previousSubIndex = parent->MainMenuArray[parent->MainMenuIndex].num_submenu_items - 1;
                parent->SubMenuIndex = index;
                parent->SubMenu.SetResource( "SelectedIndex",  parent->SubMenuIndex);
                InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,4);

            //}
     }
     else if((parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex && index == ptrDialogs[1]->subMenuIndex )|| (parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex && index == ptrDialogs[2]->subMenuIndex))
     {
           InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,4);
           //previousSubIndex = -1;
     }
     else
     {
         parent->SelectSubMenuItem(index,0,true);
         //previousSubIndex=-1;
     }
     parent->Update();
 }
 void Utility::PageErrorDown()
 {
     int index =-1;

     if(parent->SubMenuIndex == parent->MainMenuArray[parent->MainMenuIndex].num_submenu_items - 1)
      index = 0;
     else
      index = parent->SubMenuIndex + 1;
     if(parent->MainMenuIndex == ptrDialogs[3]->mainMenuIndex && index == ptrDialogs[3]->subMenuIndex)
     {
            //ptrDialogs[3]->subMenuIndexPrevious = parent->SubMenuIndex;
           /* if(previousSubIndex == ptrDialogs[3]->subMenuIndex)
            {
                index = 0;
                parent->SelectSubMenuItem(index,0,true);
                previousMainIndex=-1;
            }
            else
            {*/
               // previousSubIndex = index - 1;
                parent->SubMenuIndex = index;
                parent->SubMenu.SetResource( "SelectedIndex",  parent->SubMenuIndex);
                InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,4);
                //previousSubIndex++;
            //}
     }
     else if((parent->MainMenuIndex == ptrDialogs[1]->mainMenuIndex && index == ptrDialogs[1]->subMenuIndex )|| (parent->MainMenuIndex == ptrDialogs[2]->mainMenuIndex && index == ptrDialogs[2]->subMenuIndex))
     {
           InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,4);
           //previousSubIndex = -1;
     }
     else
     {
         parent->SelectSubMenuItem(index,0,true);
         //previousSubIndex=-1;
     }
     parent->Update();
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////
 void Utility::PageErrorLeft()
 {
     int index =-1;

     if(parent->MainMenuIndex == 0)
      index = parent->NumMainMenuItems - 1;
     else
      index = parent->MainMenuIndex - 1;
     if(index == ptrDialogs[0]->mainMenuIndex)
     {
         ptrDialogs[0]->mainMenuIndexPrevious = parent->MainMenuIndex;
         //parent->MainMenuIndex = index;
        // parent->MainMenu.SetResource( "SelectedIndex",  parent->MainMenuIndex);
        InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,3);

        /*if(previousMainIndex == ptrDialogs[0]->mainMenuIndex)
        {
            index = ptrDialogs[0]->mainMenuIndex;
            parent->SelectMainMenuItem(index - 1,0,true);
            previousMainIndex=-1;
        }
        else
        {*/
           // previousMainIndex = ptrDialogs[0]->mainMenuIndex;
            parent->MainMenuIndex = index;
            parent->MainMenu.SetResource( "SelectedIndex",  parent->MainMenuIndex);
            InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,3);
        //}
     }
     else
     {
         parent->SelectMainMenuItem(index,0,true);
     }
     parent->Update();
 }
 void Utility::PageErrorRight()
 {
     int index =-1;

     if(parent->MainMenuIndex == parent->NumMainMenuItems - 1)
      index = 0;
     else
      index = parent->MainMenuIndex + 1;
     if(index == ptrDialogs[0]->mainMenuIndex)
     {
            ptrDialogs[0]->mainMenuIndexPrevious = parent->MainMenuIndex;
           /* if(previousMainIndex == ptrDialogs[0]->mainMenuIndex)
            {
                index = 0;
                parent->SelectMainMenuItem(index,0,true);
                previousMainIndex=-1;
            }
            else
            {*/
                //previousMainIndex = index - 1;
                parent->MainMenuIndex = index;
                parent->MainMenu.SetResource( "SelectedIndex",  parent->MainMenuIndex);
                InitUtilitiesData("",GlgObjectC(GlgObject(0)),index,3);
                //previousMainIndex++;
            //}
     }
     else
     {
         parent->SelectMainMenuItem(index,0,true);
         previousMainIndex=-1;
     }
     parent->Update();

 }
  void Utility::ProcessEnter()
  {
     if(currentPopupDialog != 0 && parent->PopupDialogVisible && (currentPopupDialog->type == UTILITY_PERMISSIONS || currentPopupDialog->type == ADMINISTRATOR_PERMISSTIONS))
     {
        GlgObjectC viewport; GlgObjectC message;
        GlgDrawingArea *ptrGlgDrawingArea;
        string btn = static_cast<PassowrdDialog *>(currentPopupDialog)->btnLogin;
        currentPopupDialog->ProcessInput(btn,viewport,message,ptrGlgDrawingArea,parent);

     }
     else
     {
         if((parent->MainMenuIndex == menues[1][5]->mainMenuIndex && parent->SubMenuIndex == menues[1][5]->subMenuIndex) || (parent->MainMenuIndex == menues[1][6]->mainMenuIndex && parent->SubMenuIndex == menues[1][6]->subMenuIndex))
         {

             const char *pNumber;
             char *pName;
             char *oName;
             char * pComment;
             double **s ;
             double rl;
             double rh;

            AlarmVariableModification *i;
            AnalogAlarmVariableModification *a;
            DigitalAlarmVariableModification *b;

            if(parent->SubMenuIndex == menues[1][5]->subMenuIndex)
            {
                    a =  static_cast<AnalogAlarmVariableModification *>(menues[1][5]);
                    i = a;
            }
            else if(parent->SubMenuIndex == menues[1][6]->subMenuIndex)
            {
                    b = static_cast<DigitalAlarmVariableModification *>(menues[1][6]);
                    i = b;
            }
            parent->DrawingArea.Viewport.GetResource(i->parameterNumber.first.c_str(),&pNumber);
            i->parameterNumber.second = convertToUpper(pNumber);
            parent->DrawingArea.Viewport.SetResource(i->parameterNumber.first.c_str(),i->parameterNumber.second.c_str());
            if(i->parameterNumber.second != "")
            {
                for(int k = 0;k <i ->names; k++)
                {
                    for(int j =0; j < i->points; j++)
                    {
                        i->setpoints[k][j].second = -1;
                        parent->DrawingArea.Viewport.SetResource(i->setpoints[k][j].first.c_str(), i->setpoints[k][j].second);
                    }
                }
                i->receiveFromDDS(parent);

            }
         }
         else if(parent->MainMenuIndex  == menues[1][8]->mainMenuIndex && parent->SubMenuIndex == menues[1][8]->subMenuIndex)
         {
              ChangeSerialConfiguration * ins = static_cast<ChangeSerialConfiguration *>(menues[1][8]);
              ins->receiveFromDDS(parent);
         }

     }
  }
  void Utility::SetFocus(GlgObjectC& parentViewport)
  {
      if(currentPopupDialog != 0)
      {
          if(parent->PopupDialogVisible && (currentPopupDialog->type == UTILITY_PERMISSIONS || currentPopupDialog->type == ADMINISTRATOR_PERMISSTIONS))
          {

                const char *p;

                parentViewport.GetResource(static_cast<PassowrdDialog *>(currentPopupDialog)->passwordTxt.c_str(),&p);
                if(strcmp(p,"") == 0)
                {
                    GlgSetFocus(parentViewport, (char*)PASSWORD_BOX_NAME.c_str() );
                }

          }

      }
      else
        {
            if(parent->MainMenuIndex == menues[1][3]->mainMenuIndex && parent->SubMenuIndex == menues[1][3]->subMenuIndex)  // ChangeSystemDate
            {
                const char *date;

                parentViewport.GetResource(static_cast<ChangeSystemDate *>(menues[1][3])->datearray[0].first.c_str(),&date);

                if(strcmp(date,"") == 0)
                {
                  GlgSetFocus(parentViewport, (char*)DATE_ARRAY_NAMES[0].c_str() );
                  parentViewport.SetResource("btnFinish/Visibility",-0.3);
                }

            }
            else if((parent->MainMenuIndex == menues[1][4]->mainMenuIndex && parent->SubMenuIndex == menues[1][4]->subMenuIndex) )//|| (commentbuttonclicked)) // Comment Entry
            {
                const char *in="",*c="";

                parentViewport.GetResource(static_cast<CommentEntryScreen *>(menues[1][4])->initialsTxt.first.c_str(),&in);
                parentViewport.GetResource(static_cast<CommentEntryScreen *>(menues[1][4])->commentTxt.first.c_str(),&c);

                if(strcmp(in,"") == 0)
                {
                    GlgSetFocus(parentViewport, (char*)INITIALS_WIDGETS_NAME[0].c_str() );
                }


            }
            else if(parent->MainMenuIndex == menues[2][0]->mainMenuIndex && parent->SubMenuIndex == menues[2][0]->subMenuIndex)
            {
                double in;

                parentViewport.GetResource(static_cast<MachineryLogInterval *>(menues[2][0])->periodTxt.first.c_str(),&in);
                if(in == 0)
                {
                    GlgSetFocus(parentViewport,(char *)LOGGING_WIDGET_NAME.c_str());
                }
            }
            else if(parent->MainMenuIndex == menues[1][5]->mainMenuIndex && parent->SubMenuIndex == menues[1][5]->subMenuIndex || parent->MainMenuIndex == menues[1][6]->mainMenuIndex && parent->SubMenuIndex == menues[1][6]->subMenuIndex)
            {
             //GlgSetFocus(parentViewport,(char *)ALARM_WIDGET_NAME.c_str());
            }
            else if( parent->MainMenuIndex == changePasswordScreen->mainMenuIndex &&  parent->SubMenuIndex == changePasswordScreen->subMenuIndex)
            {

            /* const char *in;

            parentViewport.GetResource(static_cast<ChangePassword  *>(changePasswordScreen)->oldPasswordTxt[0].c_str(),&in);
            if(strcmp(in,"") == 0)
             {
                GlgSetFocus(parentViewport,(char *)PASSWORD_WIDGET_NAME.c_str());
            }*/
            }
      }
      parentViewport.Update();
  }

  void  Utility::LogAllData(GlgSCADAViewer *ptr)
  {
      DEBUGF_VDT("START Utility::LogAllData Send to Server  Input \n");
      int ReturnValue=-1;
      ReturnValue = ptr->pDataFeed->CreateLogAllDatabasePoints(1);
      if(ReturnValue == -1)
      {
            ERRORF_VDT("FINISH Responce Utility::LogAllData from the  Server   Server ERROR Received status = [%d]\n",ReturnValue);
      }
      else
      {
           ERRORF_VDT("FINISH Responce Utility::LogAllData from the  Server  Server SUCCESS Received status = [%d]\n",ReturnValue);
      }
      ptr->LogAllDataBasePointButton.SetResource("Visibility",1.0);

  }
  void Utility::timer(int d,  void (*f)(GlgSCADAViewer *ptr ),GlgSCADAViewer *ptr)
  {
      std::thread(
	  [d,f,ptr](){
            std::this_thread::sleep_for(std::chrono::seconds(d));
            f(ptr);
                 }
	  ).detach();
  }
  void  Utility::DelayLog(GlgSCADAViewer *ptr)
  {
        ptr->LogAllDataBasePointButton.SetResource("Visibility",1.0);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AdjustPitchControlVariables::AdjustPitchControlVariables()
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName =  ADJUST_PITCH_CONTROL_VARIABLES_LABEL_STRING;
    mainMenuName = UTILITY_LABEL_STRING;
    btnFinishInstate.first = BTN_FINISH_INSTATE1;
    btnFinishInstate.second = -1;
    btnCancelInstate.first = BTN_CANCEL_INSTATE1;
    btnCancelInstate.second = -1;
    pair<string,double> temp;
    for(int i=0;i < NUM_OF_INPUT_VALUES;i++)
    {
       temp.first = PITCH_VARIABLES[i];
       temp.second = 0;
       pitchVariables.push_back(temp);
    }
}

AdjustPitchControlVariables::~AdjustPitchControlVariables()
{
    pitchVariables.clear();
}

void AdjustPitchControlVariables::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{
    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
    {
        double visibility = -1;

        ptrDrawingArea->Viewport.GetResource(btnFinishInstate.first.c_str(),&btnFinishInstate.second);
        ptrDrawingArea->Viewport.GetResource(btnCancelInstate.first.c_str(),&btnCancelInstate.second);
        ptrDrawingArea->Viewport.GetResource("btnFinish/Visibility",&visibility);

        if(btnFinishInstate.second == 1 && visibility == 1.0)
        {
            for(int i = 0;i< NUM_OF_INPUT_VALUES;i++)
                ptrDrawingArea->Viewport.GetResource(pitchVariables[i].first.c_str(),&pitchVariables[i].second);
            timer(0,  sendToDDS, pitchVariables,ptr);
        }
        else if(btnCancelInstate.second == 1)
        {
            ptr->SelectMainMenuItem((GlgLong)ptr->MainMenuIndex,0,true);
        }
        //printData();
        //for(int i = 0;i< NUM_OF_INPUT_VALUES;i++)
            //ptrDrawingArea->Viewport.SetResource(pitchVariables[i].first.c_str(),0.0);
    }
}
void AdjustPitchControlVariables::sendToDDS( vector<pair<string,double>> pitchVariables,GlgSCADAViewer *ptr)
{
    DEBUGF_VDT("STARTED AdjustPitchControlVariables::sendToDDS Test\n");
    string statuslbl = MACH_STATUS_TEXT[0];
    ptr->DrawingArea.Viewport.SetResource("statuslbl/String",statuslbl.c_str());
    ptr->DrawingArea.Viewport.SetResource("statuslbl/Visibility",1.0);
    ptr->DrawingArea.Viewport.SetResource("btnFinish/Visibility",-0.3);
    int st = 1;

    PITCHVARIABLESTR  ptcs;

    ptcs.IntegralGain = pitchVariables[0].second;
    ptcs.ProportionalGain = pitchVariables[1].second;
    ptcs.OverloadCtrlGain = pitchVariables[2].second;
    ptcs.NonOverloadCtrlGain = pitchVariables[3].second;

    st = ptr->pDataFeed->WritePitchVariable(&ptcs);

    for(int i=0;i<pitchVariables.size();i++)
    {
        DEBUGF_VDT("[%f]  ",pitchVariables[i].second);
    }
    DEBUGF_VDT("\n");
    if(st == -1)
    {
        statuslbl =  MACH_STATUS_TEXT[2];

        ERRORF_VDT(" AdjustPitchControlVariables::sendToDDS Server ERROR Received status = [%d]\n",st);
    }
    else
    {
        statuslbl =  MACH_STATUS_TEXT[1];
    }
    ptr->DrawingArea.Viewport.SetResource("statuslbl/String",statuslbl.c_str());
    DEBUGF_VDT("FINISHED AdjustPitchControlVariables::sendToDDS Test\n");

}
void AdjustPitchControlVariables::timer(int d,  void (*f)( vector<pair<string,double>> ,GlgSCADAViewer * ), vector<pair<string,double>> pitchVariables,GlgSCADAViewer *ptr)
{
     std::thread([d,f,pitchVariables,ptr](){
        std::this_thread::sleep_for(std::chrono::seconds(d));
        f(pitchVariables,ptr);
    }).detach();
}

void AdjustPitchControlVariables::receiveFromDDS(double &p1,double &p2,double &p3,double &p4,CDataFeed * pDataFeed)
{
     // p1 = pitchVariables[0].second;
     // p2 = pitchVariables[1].second;
     // p3 = pitchVariables[2].second;
     // p4 = pitchVariables[3].second;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditThrottleProfiles::EditThrottleProfiles()
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName =  EDIT_THROTTLE_PROFILES_LABEL_STRING;
    mainMenuName = UTILITY_LABEL_STRING;
    btnfinishInstate.first = BTN_FINISH_INSTATE2;
    btnfinishInstate.second = -1;
    btncancelInstate.first = BTN_CANCEL_INSTATE2;
    btncancelInstate.second = -1;
    status.first = STATUS_THROTTLE_EDITOR_LABEL;
    status.second = "Wait Processing Transaction";

    for(int i = 0;i < NUMBER_OF_THROUTTLE_PROFILES; i++)
    {
         pitch.push_back(pair<string,double>(PITCH_VALUES[i],0));
         rpm.push_back(pair<string,double>(RPM_VALUES[i],0));
    }
    option.first = EDITOR_THR_PROFILES_OPTION;
    option.second = 0;

}
EditThrottleProfiles::~EditThrottleProfiles()
{
   pitch.clear();
   rpm.clear();
}
void EditThrottleProfiles::ProcessInput(string action,string origin, GlgDrawingArea * drawingArea)
{
    if(action == "Select" && drawingArea->parent->MainMenuIndex == this->mainMenuIndex && drawingArea->parent->SubMenuIndex == this->subMenuIndex)
    {
      drawingArea->parent->utility->DisplayUtilityPages(drawingArea->parent->MainMenuIndex, drawingArea->parent->SubMenuIndex);
    }
}
void EditThrottleProfiles::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{
    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
    {
        //throttleProfileStr currentProfile;
        double visibility = -1;
        ptrDrawingArea->Viewport.GetResource(btnfinishInstate.first.c_str(),&btnfinishInstate.second);
        ptrDrawingArea->Viewport.GetResource(btncancelInstate.first.c_str(),&btncancelInstate.second);
        ptrDrawingArea->Viewport.GetResource(BTN_FINISH_VISIBILITY1.c_str(),&visibility);
        if(btnfinishInstate.second == 1 && visibility == 1.0)
        {
           // ptrDrawingArea->Viewport.SetResource(STATUS_VISIBILITY.c_str(),1.0);
            //ptrDrawingArea->Viewport.SetResource(BTN_FINISH_VISIBILITY1.c_str(),-0.3);
            ptrDrawingArea->Viewport.GetResource(option.first.c_str(),&option.second);
            for(int i = 0;i < NUMBER_OF_THROUTTLE_PROFILES; i++)
            {
                ptrDrawingArea->Viewport.GetResource(pitch[i].first.c_str(),&pitch[i].second);
                ptrDrawingArea->Viewport.GetResource(rpm[i].first.c_str(),&rpm[i].second);
            }

            timer(0,  sendToDDS,option,pitch, rpm,ptr);

        }
        else if(btncancelInstate.second == 1)
        {
            DEBUGF_VDT("STARTED EditThrottleProfiles  profileType = [%d] Button pressed CANCEL on Page WriteThrottleProfile\n");
            ptr->SelectMainMenuItem((GlgLong)ptr->MainMenuIndex,0,true);
            DEBUGF_VDT("FINISHED EditThrottleProfiles  profileType = [%d] Button pressed CANCEL on Page WriteThrottleProfile\n");
        }
        for(int i = 0;i < NUMBER_OF_THROUTTLE_PROFILES; i++)
        {
            ptrDrawingArea->Viewport.SetResource(pitch[i].first.c_str(),0.0);
            ptrDrawingArea->Viewport.SetResource(rpm[i].first.c_str(), 0.0);
        }
    }
}
void EditThrottleProfiles::sendToDDS(pair<string,double> option, vector<pair<string,double>> pitch, vector<pair<string,double>> rpm,GlgSCADAViewer *ptr)
{
     string statuslbl = STATUS_THROTTLE_EDITOR_TEXT[0];
     ptr->DrawingArea.Viewport.SetResource(STATUS_THROTTLE_EDITOR_LABEL.c_str(),statuslbl.c_str());
     ptr->DrawingArea.Viewport.SetResource(STATUS_VISIBILITY.c_str(),1.0);
     ptr->DrawingArea.Viewport.SetResource(BTN_FINISH_VISIBILITY1.c_str(),-0.3);
     throttleProfileStr currentProfile;
     currentProfile.profileType = option.second;
     for(int i = 0;i < NUMBER_OF_THROUTTLE_PROFILES; i++)
     {
                currentProfile.profile[i].ndx = int(i - 10);
                currentProfile.profile[i].pitch = (double)pitch[i].second;
                currentProfile.profile[i].rpm = (double)rpm[i].second;
     }
     DEBUGF_VDT("START EditThrottleProfiles  profileType = [%d] Button pressed FINISH on Page WriteThrottleProfile\n",currentProfile.profileType);

     ptr->pDataFeed->WriteThrottleProfile(currentProfile.profileType ,&currentProfile);
     statuslbl = STATUS_THROTTLE_EDITOR_TEXT[1];
     ptr->DrawingArea.Viewport.SetResource(STATUS_THROTTLE_EDITOR_LABEL.c_str(),statuslbl.c_str());
     DEBUGF_VDT("FINISH EditThrottleProfiles  profileType = [%d] Button pressed FINISH on Page WriteThrottleProfile\n",currentProfile.profileType);
}
void EditThrottleProfiles::timer(int d,  void (*f)( pair<string,double> ,vector<pair<string,double>> , vector<pair<string,double>> ,GlgSCADAViewer *), pair<string,double> option, vector<pair<string,double>> pitch, vector<pair<string,double>> rpm,GlgSCADAViewer *ptr)
{
     std::thread([d,f,option,pitch,rpm,ptr](){
        std::this_thread::sleep_for(std::chrono::seconds(d));
        f(option,pitch,rpm,ptr);
    }).detach();
}
void EditThrottleProfiles::printData()
{
    cout << " MainManu = " << mainMenuName <<" MainMenuIndex = "<< mainMenuIndex << " SubMenuIndex = "<<subMenuIndex << endl;
    cout << "Finish = "<<btnfinishInstate.first << " "<<btnfinishInstate.second << endl;
    cout << "Option = "<<option.first << " = "<<option.second<< endl;
    for(int i = 0;i < NUMBER_OF_THROUTTLE_PROFILES; i++)
    {
         cout << pitch[i].first <<" = "<< pitch[i].second  << rpm[i].first << " = " << rpm[i].second << endl;

    }
}
void EditThrottleProfiles::printsendData( throttleProfileStr currentProfile,int option)
{
    if(option == 0)
    {
       cout <<" Start Sending Profile"<< endl;
    }
    else if(option == 1)
    {
          cout <<" Start Recieving Profile"<< endl;
    }
    else
    {
        cout << " Start Requesting Profile"<< endl;
    }
    cout << " profiletype = " << currentProfile.profileType <<endl;

    for(int i = 0;i < MAXNUMTHROTTLEENTRIES; i++)
    {
         cout << " ndx = " << currentProfile.profile[i].ndx << " pitch = " << currentProfile.profile[i].pitch << " rpm = " << currentProfile.profile[i].rpm << endl;
    }
    if(option == 0)
    {
       cout <<" Finish Sending Profile"<< endl;
    }
    else if(option == 1)
    {
          cout <<" Finish Recieving Profile"<< endl;
    }
    else
    {
         cout << " Finish Requesting Profile"<< endl;
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HardwareDiagnostics::HardwareDiagnostics()
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName =  HARDWARE_DIAGNOSTICS_LABEL_STRING;
    mainMenuName = UTILITY_LABEL_STRING;
    btnfinishInstate.first = BTN_FINISH_INSTATE3;
    btnfinishInstate.second = -1;
    btnstopInstate.first = BTN_STOP_INSTATE3;
    btnstopInstate.second = -1;
    btncancelInstate.first = BTN_CANCEL_INSTATE3;
    btncancelInstate.second = -1;
    option.first = HARDWARE_DIAGNOSTICS_OPTION;
    option.second = 0;
    status.first = STATUS_HADWARE_LABEL;
    status.second = STATUS_HADWARE_LABEL_TEXT[0];
    btnFinishVisibility.first = HARDWARE_BTN_FINISH_VISIBILITY;
    btnFinishVisibility.second = 0.0;
    btnStopVisibility.first = HARDWARE_BTN_STOP_VISIBILITY;
    btnStopVisibility.second =  0.0;
    statuslabelvisibility.first = STATUS_LABEL_VISIBILITY;
    statuslabelvisibility.second = 0;

    pair<string,string> temp;
    for(int i =0;i<NUMBER_OF_OPTION_TYPES;i++)
    {
        temp.first = HARDWARE_DIAGNOSTIC_OPTIONS_TYPES[i];
        temp.second = "";
        optionnames.push_back(temp);
    }
}

HardwareDiagnostics::~HardwareDiagnostics()
{
   optionnames.clear();
}
 std::mutex mh[3];
void HardwareDiagnostics::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{
    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
    {
        cout << "Processing "<< mainMenuName << " " << subMenuName << " MainManu = " << mainMenuName <<" MainMenuIndex = "<< mainMenuIndex << " SubMenuIndex = "<<subMenuIndex << endl;
        ptrDrawingArea->Viewport.GetResource(btnfinishInstate.first.c_str(),&btnfinishInstate.second);
        ptrDrawingArea->Viewport.GetResource(btnstopInstate.first.c_str(),&btnstopInstate.second);
        ptrDrawingArea->Viewport.GetResource(btncancelInstate.first.c_str(),&btncancelInstate.second);
        ptrDrawingArea->Viewport.GetResource(option.first.c_str(),&option.second);

        if(btnfinishInstate.second == 1)
        {
            const char * currenttest;
            if((int)option.second > -1 && (int)option.second <NUMBER_OF_OPTION_TYPES )
            {
                ptrDrawingArea->Viewport.GetResource(optionnames[(int)option.second].first.c_str(),&currenttest);
                optionnames[(int)option.second].second = string(currenttest);
            }
            statuslabelvisibility.second = 0;

            btnFinishVisibility.second = 0.0;

            status.second = STATUS_HADWARE_LABEL_TEXT[0];
            statuslabelvisibility.second = 1.0;
            ptr->DrawingArea.Viewport.SetResource(status.first.c_str(),status.second.c_str());
            ptr->DrawingArea.Viewport.SetResource( statuslabelvisibility.first.c_str(),statuslabelvisibility.second);
            ptr->DrawingArea.Viewport.SetResource(btnFinishVisibility.first.c_str(),btnFinishVisibility.second);

            ptr->DrawingArea.Viewport.SetResource( statuslabelvisibility.first.c_str(), statuslabelvisibility.second);

            if(option.second == 1 || option.second == 2)
            {
                btnStopVisibility.second = 1.0;
                ptr->DrawingArea.Viewport.SetResource(btnStopVisibility.first.c_str(),btnStopVisibility.second);
            }
            //DEBUGF_VDT("START HardwareDiagnostics::sendToDDS Button START pressed Test\n");

            mh[0].lock();
            int st = timer(0,&sendToDDS,option.second-1,false,btnfinishInstate,ptr);
            mh[0].unlock();
           // DEBUGF_VDT("FINISH HardwareDiagnostics::sendToDDS Button START pressed Test\n");

        }
        else if(btnstopInstate.second == 1)
        {
             //DEBUGF_VDT("START HardwareDiagnostics::sendToDDS Button Finish pressed Test\n");
             btnStopVisibility.second = -0.3;
             ptr->DrawingArea.Viewport.SetResource(btnStopVisibility.first.c_str(),btnStopVisibility.second);
             if(option.second == 1 || option.second == 2)
             {
                 mh[1].lock();
                int st = timer(0,&sendToDDS,option.second-1,true,btnstopInstate,ptr);
                 mh[1].unlock();
             }
             ptr->DrawingArea.Viewport.SetResource(STATUS_LABEL_VISIBILITY.c_str(),0.0);
             ptr->DrawingArea.Viewport.SetResource(HARDWARE_DIAGNOSTICS_OPTION.c_str(),0.0);
             ptr->DrawingArea.Viewport.SetResource(HARDWARE_BTN_FINISH_VISIBILITY.c_str(),0.0);
             ptr->DrawingArea.Viewport.SetResource(HARDWARE_BTN_STOP_VISIBILITY.c_str(),0.0);
             //statuslabelvisibility.second = 0;

             //DEBUGF_VDT("FINISH HardwareDiagnostics::sendToDDS Button Finish pressed Test\n");
        }
        else if(btncancelInstate.second == 1)
        {
            //DEBUGF_VDT("START HardwareDiagnostics::sendToDDS Button Cancel pressed Test\n");

           // if(option.second != 2)
            //{
                //st = ptr->pDataFeed->CreateHardwareDiagnostics(option.second,true);
           // }
              if(option.second == 1 || option.second == 2)
             {
                mh[2].lock();
                int st = timer(0,&sendToDDS,option.second-1,false,btnstopInstate,ptr);
                mh[2].unlock();
             }
             ptr->DrawingArea.Viewport.SetResource(STATUS_LABEL_VISIBILITY.c_str(),0.0);
             ptr->DrawingArea.Viewport.SetResource(HARDWARE_DIAGNOSTICS_OPTION.c_str(),0.0);
             ptr->DrawingArea.Viewport.SetResource(HARDWARE_BTN_FINISH_VISIBILITY.c_str(),0.0);
             ptr->DrawingArea.Viewport.SetResource(HARDWARE_BTN_STOP_VISIBILITY.c_str(),0.0);
            //statuslabelvisibility.second = 0;

            //DEBUGF_VDT("FINISH HardwareDiagnostics::sendToDDS Button Cancel pressed Test\n");
        }
    }
}
void HardwareDiagnostics::ProcessInput(string action, string origin,GlgDrawingArea * drawingArea)
{
    if(drawingArea->parent->MainMenuIndex == this->mainMenuIndex && drawingArea->parent->SubMenuIndex == this->subMenuIndex)
    {

        statuslabelvisibility.second = 0;
        drawingArea->Viewport.SetResource( statuslabelvisibility.first.c_str(), statuslabelvisibility.second);
        drawingArea->Viewport.GetResource(option.first.c_str(),&option.second);
        if(option.second == 0.0)
             btnFinishVisibility.second = 0.0;
        else
             btnFinishVisibility.second = 1.0;


        drawingArea->Viewport.SetResource( btnFinishVisibility.first.c_str(), btnFinishVisibility.second);

    }
}

int HardwareDiagnostics::sendToDDS(double opt,bool condition,pair<string,double> btnoption,GlgSCADAViewer *ptr)
{
    string op ="";
    string statuslbl;
    if(btnoption.first == "btnFinish/InState")
    {
        op = "START";
    }
    else if(btnoption.first == "btnStop/InState")
    {
        op = "STOP";
    }
    else if(btnoption.first == "btnCancel/InState")
    {
        op = "CANCEL";
    }

    DEBUGF_VDT("START HardwareDiagnostics::sendToDDS Button Name = [%s]  pressed  Test option = [%f] stoptest = [%d] \n",op.c_str(),opt,(int)condition);
    int st = -1;
    st = ptr->pDataFeed->CreateHardwareDiagnostics(opt,condition);


    if(st == -1)
     {
          statuslbl = STATUS_HADWARE_LABEL_TEXT[2];
          //string o = string(optionnames[(int)option.second].second);
          ERRORF_VDT("Server Responce on HardwareDiagnostics::sendToDDS Button Name = [%s]  pressed Test option = [%f]  stoptest = [%d] Server ERROR Received status = [%d]\n",op.c_str(),opt,(int)condition,st);
     }
     else
     {
         statuslbl = STATUS_HADWARE_LABEL_TEXT[1];
         //string o = string(optionnames[(int)option.second].second);
         DEBUGF_VDT("Server Responce on HardwareDiagnostics::sendToDDS Button Name = [%s]  pressed Test option = [%f]  stoptest = [%d] Server SUCCESS Received status = [%d]\n",op.c_str(),opt,(int)condition,st);
     }

     if(op != "START")
     {

     }
     else
     {
         ptr->DrawingArea.Viewport.SetResource(STATUS_HADWARE_LABEL.c_str(),statuslbl.c_str());
     }
     DEBUGF_VDT("FINISH HardwareDiagnostics::sendToDDS Button Name = [%s]  pressed  Test option = [%f] stoptest = [%d] \n",op.c_str(),opt,(int)condition);
     return st;

}
int HardwareDiagnostics::timer(int d,  int (*f)(double,bool,pair<string,double> ,GlgSCADAViewer *  ),double option,bool condition,pair<string,double> btnoption,GlgSCADAViewer *ptr)
{
    try
    {
            std::thread([d,f,option,condition,btnoption,ptr](){std::this_thread::sleep_for(std::chrono::seconds(d));
                   return f(option,condition,btnoption,ptr);
            }).detach();

    }
    catch(const std::system_error& e)
    {
        cout <<"catched system error "<< e.what()<< endl;
    }

}
bool HardwareDiagnostics::receiveFromDDS(double &opt,CDataFeed * pDataFeed)
{
    opt = option.second;
    if((int)opt > -1 && (int)opt < NUMBER_OF_OPTION_TYPES)
    {
      statuslabelvisibility.second = 1;
      cout << "Hardware Diagnostic test FINISHED SUCCESSFULL =  "<< opt << "  NAME = " << optionnames[(int)opt].second << endl;
      return true;
    }
    else
    {
        cout << "Hardware Diagnostic test FINISHED FAILURE =  " << option.second << " NAME = " << optionnames[(int)option.second].second << endl;
        return false;
    }
}
void HardwareDiagnostics::printData()
{
    cout << " MainManu = " << mainMenuName <<" MainMenuIndex = "<< mainMenuIndex << " SubMenuIndex = "<<subMenuIndex << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChangeSystemDate::ChangeSystemDate()
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName =  CHANGE_SYSTEM_DATA_LABEL_STRING;
    mainMenuName = UTILITY_LABEL_STRING;
    btnfinishInstate.first = BTN_FINISH_INSTATE4;
    btnfinishInstate.second = -1;
    btncancelInstate.first = BTN_CANCEL_INSTATE4;
    btncancelInstate.second = -1;
    //datetxt.first = DATE_TEXT;
    //datetxt.second = "";
    pair<string,string> temp;
    for(int i=0;i<DATE_COUNT;i++)
    {
        temp.first = DATE_TEXT_ARRAY[i];
        temp.second = "";
        datearray.push_back(temp);
    }
   // timetxt.first = TIME_TEXT;
   // timetxt.second = "";
    for(int i=0;i<TIME_COUNT;i++)
    {
        temp.first = TIME_TEXT_ARRAY[i];
        temp.second = "";
        timearray.push_back(temp);
    }

    status.first = CHANGE_SYSTEM_DATE_STATUS_LABEL_VISIBILITY;
    status.second = 0.0;
}

ChangeSystemDate::~ChangeSystemDate()
{

}

void ChangeSystemDate::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{
    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
    {
        double finishVisibility =-1;
        ptrDrawingArea->Viewport.GetResource("btnFinish/Visibility",&finishVisibility);
        ptrDrawingArea->Viewport.GetResource(btncancelInstate.first.c_str(),&btncancelInstate.second);
        if(finishVisibility == 1.0  )
        {
                //cout << "Processing "<< mainMenuName << " " << subMenuName << " MainManu = " << mainMenuName <<" MainMenuIndex = "<< mainMenuIndex << " SubMenuIndex = "<<subMenuIndex << endl;
                ptrDrawingArea->Viewport.GetResource(btnfinishInstate.first.c_str(),&btnfinishInstate.second);

                bool validdate = false;
                bool validtime = false;
                if(btnfinishInstate.second == 1)
                {
                   const char * d,*t,*da[datearray.size()],*ta[timearray.size()];
                   string sdate = "",stime ="";
                   //char date[11];
                  // char time[9];
                   //char ssdate[datearray.size()];
                 for(int i = 0;i<datearray.size();i++)
                    {
                        ptrDrawingArea->Viewport.GetResource(datearray[i].first.c_str(),&da[i]);
                        //cout << datearray[i].first.c_str() << " da"<< da[i]<<endl;
                        if(i==1 || i == 3)
                        {
                           sdate = sdate + "/";

                        }
                        else
                        {
                           sdate = sdate + da[i];
                        }
                    }

                for(int i = 0;i<timearray.size();i++)
                    {
                        ptrDrawingArea->Viewport.GetResource(timearray[i].first.c_str(),&ta[i]);
                        if(i==1 || i == 3 )
                        {
                            stime = stime + ":";
                        }
                        else
                        {
                            stime = stime + ta[i];
                        }
                     }


                /*int a=0;
                for(a=0;a < 10;a++)
                {
                    date[a] = sdate[a];

                }
                date[a]='\0';

                for(a=0;a < 8;a++)
                {

                    time[a] = stime[a];
                }
                time[a]='\0';*/

                validdate  = Validate(sdate.c_str(),'/');
                validtime  = Validate(stime.c_str(),':');

                if(validdate && validtime)
                {
                        ptrDrawingArea->Viewport.SetResource(status.first.c_str(),0.0);
                        DEBUGF_VDT("START sending to the server Button FINISH on SetTime page  pressed: DATA = [%s], TIME = [%s]  validdata = [%d], validtime = [%d]\n",sdate.c_str(), stime.c_str(),(int)validdate, (int)validtime);
                        ptrDrawingArea->Viewport.SetResource("statuslbl/String","Date/Time Update in process.");
                        //ptrDrawingArea->Viewport.SetResource(status.first.c_str(),1.0);
                        ptrDrawingArea->Viewport.SetResource("btnFinish/Visibility",-0.3);

                        timer(TIME_DELAY1,&sendToDDS,sdate,stime,ptr);

                        /*for(int i = 0;i<datearray.size();i++)
                        {
                                ptrDrawingArea->Viewport.SetResource(datearray[i].first.c_str(),(char*)"");
                        }
                       for(int i = 0;i<timearray.size();i++)
                        {
                                ptrDrawingArea->Viewport.SetResource(timearray[i].first.c_str(),(char *)"");
                        }*/

                 }
                else
                {
                    DEBUGF_VDT("Button FINISH on SetTime page  pressed: validdate = [%d], validtime = [%d], validation error = [%d] DATA = [%s], TIME = [%s]\n",(int)validdate, (int)validtime,sdate.c_str(),stime.c_str());
                    ptrDrawingArea->Viewport.SetResource("statuslbl/String","Invalid Input");
                    ptrDrawingArea->Viewport.SetResource(status.first.c_str(),1.0);
                }

            }


             DEBUGF_VDT("FINISH Processing Button FINISH on SetTime page  pressed.\n");
        }
        if(btncancelInstate.second == 1)
        {
            DEBUGF_VDT("START processing Button CANCEL on SetTime page  pressed.\n");
            ptr->SelectMainMenuItem((GlgLong)ptr->MainMenuIndex,0,true);
            DEBUGF_VDT("FINISH processing Button CANCEL on SetTime page  pressed.\n");
        }
    }
}
void ChangeSystemDate::ProcessInput(string action, string origin,GlgDrawingArea * drawingArea)
{
    if(drawingArea->parent->MainMenuIndex == this->mainMenuIndex && drawingArea->parent->SubMenuIndex == this->subMenuIndex)
    {
      if(strcmp(action.c_str(),"ValueChanged") == 0 )
       {

          const char * d,*t,*da[datearray.size()],*ta[timearray.size()];
           int l =-1,oplen=-1;
           bool valid = true;
           string val;

          for(int i=0;i<DATE_COUNT;i++)
          {
             if(strcmp(origin.c_str(),DATE_ARRAY_NAMES[i].c_str()) == 0)
             {
                switch(i)
                {
                      case 0:
                      case 2:
                      case 4:
                       drawingArea->Viewport.GetResource(datearray[i].first.c_str(),&d);

                       l = strlen(d);
                       if(i==0 || i == 2)
                           oplen =2;
                       else if(i==4)
                           oplen =4;
                       if(l >= oplen)
                       {
                           val = string(d);
                           int j=0;
                           for(j=0;j<oplen;j++)
                           {

                            if(isdigit(val[j]))
                            {

                            }
                            else
                                valid = false;
                           }
                           val[j] = '\0';
                           if(valid)
                           {
                             drawingArea->Viewport.SetResource(datearray[i].first.c_str(),val.c_str());
                             if(strlen(val.c_str()) == oplen)
                             {
                                if(i + 2 < DATE_COUNT)
                                    GlgSetFocus(drawingArea->Viewport, (char*)DATE_ARRAY_NAMES[i + 2].c_str() );
                                else
                                    GlgSetFocus(drawingArea->Viewport, (char*)TIME_ARRAY_NAMES[0].c_str() );
                             }
                           }
                           else
                           {
                              drawingArea->Viewport.SetResource(datearray[i].first.c_str(),(char*)"");
                              GlgSetFocus(drawingArea->Viewport, (char*)DATE_ARRAY_NAMES[i].c_str() );
                           }
                       }

                       break;
                      case 1:
                      case 3:
                        //drawingArea->Viewport.SetResource(datearray[i].first.c_str(),(char*)"/");
                        GlgSetFocus(drawingArea->Viewport, (char*)DATE_ARRAY_NAMES[i + 1].c_str() );
                        break;


                }
             }
          }
          for(int i=0;i<TIME_COUNT;i++)
          {
             if(strcmp(origin.c_str(),TIME_ARRAY_NAMES[i].c_str()) == 0)
             {
                switch(i)
                {
                      case 0:
                      case 2:
                      case 4:
                     // case 6:
                       drawingArea->Viewport.GetResource(timearray[i].first.c_str(),&d);

                       l = strlen(d);
                       oplen =2;

                       if(l >= oplen)
                       {
                           val = string(d);
                           int j=0;
                           for(j=0;j<oplen;j++)
                           {
                            if(i != TIME_COUNT - 1)
                            {
                                if(isdigit(val[j]))
                                {

                                }
                                else
                                 valid = false;
                            }

                           }
                           val[j] = '\0';
                           if(valid)
                           {
                               drawingArea->Viewport.SetResource(timearray[i].first.c_str(),val.c_str());
                               if(strlen(val.c_str()) == oplen )
                                  GlgSetFocus(drawingArea->Viewport, (char*)TIME_ARRAY_NAMES[i + 2].c_str() );


                           }
                           else
                           {
                              drawingArea->Viewport.SetResource(timearray[i].first.c_str(),(char*)"");
                              GlgSetFocus(drawingArea->Viewport, (char*)TIME_ARRAY_NAMES[i].c_str() );
                           }
                       }

                       break;
                      case 1:
                      case 3:

                        GlgSetFocus(drawingArea->Viewport, (char*)DATE_ARRAY_NAMES[i + 1].c_str() );
                        break;
                      default:
                          GlgSetFocus(drawingArea->Viewport, (char*)"btnFinish" );
                          break;
                }

             }
          }

          bool finishvalid = true;

          const char *checkdata;
         if(finishvalid)
          {
            for(int a =0;a<DATE_COUNT;a++)
            {
               drawingArea->Viewport.GetResource(datearray[a].first.c_str(),&checkdata);
               if(strlen(checkdata) < 2 && (a == 0 || a == 2 ))
                   finishvalid = false;

               else if(strlen(checkdata) < 4 && a == 4)
                   finishvalid = false;
            }
          }
          if(finishvalid)
          {
              for(int a =0;a<TIME_COUNT;a++)
              {
                   drawingArea->Viewport.GetResource(timearray[a].first.c_str(),&checkdata);
                   if(strlen(checkdata) < 2 && (a == 0 || a == 2 || a == 4 ))
                       finishvalid = false;
                   //else if(strcmp(checkdata,":") !=0 && (a == 1 || a == 3 || a == 5))
                       //finishvalid = false;
              }
          }
          if(finishvalid)
          {
              drawingArea->Viewport.SetResource("btnFinish/Visibility",1.0);
              GlgSetFocus(drawingArea->Viewport, (char*)"btnFinish" );
          }
          else
          {
              drawingArea->Viewport.SetResource("btnFinish/Visibility",-0.3);
          }
       }


    }
}
void ChangeSystemDate::sendToDDS(string date,string time,GlgSCADAViewer *ptr)
{
    int success = ptr->pDataFeed->SetTime(date,time);

    vector<int> ndate;
    vector<int> ntime;
    ndate = ptr->utility->splitDate(date,'/');
    ntime = ptr->utility->splitDate(time,':');
    curdate = ndate;
    curtime = ntime;

    if(success == -1)
    {
        //ptr->DrawingArea.Viewport.SetResource("statuslbl/String","Server Error");
        ERRORF_VDT("Button FINISH responce from server received : DATE = [%s], TIME = [%s], SERVER ERROR status recieved = [%d]\n",date.c_str(), time.c_str(),success);
    }
    else
    {
         //ptr->DrawingArea.Viewport.SetResource("statuslbl/String","Update Completed");
         DEBUGF_VDT("Button FINISH responce from server received : DATE = [%s], TIME = [%s], SERVER SUCCESS status recieved = [%d]\n",date.c_str(), time.c_str(),success); 
    }
    ptr->DrawingArea.Viewport.SetResource("statuslbl/Visibility",0.0);

}
bool ChangeSystemDate::receiveFromDDS(char ** date,char ** time)
{
     //*date = (char *)datetxt.second.c_str();
     //*time = (char *)timetxt.second.c_str();
}
void ChangeSystemDate::timer(int d,  void (*f)(string ,string ,GlgSCADAViewer *  ),string date,string time,GlgSCADAViewer *ptr)
{

    std::thread([d,f,date,time,ptr](){
        std::this_thread::sleep_for(std::chrono::seconds(d));
        f(date,time,ptr);
    }).detach();
}

void ChangeSystemDate::printData()
{
    cout << " MainManu = " << mainMenuName <<" MainMenuIndex = "<< mainMenuIndex << " SubMenuIndex = "<<subMenuIndex << endl;
}
bool ChangeSystemDate::Validate(const string &s,char delim)
 {
        std::vector<double> elems;
        int validdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

         int leapyear = 2012;
         bool result = true;
         std::string item;
         std::stringstream ss(s);

         while (std::getline(ss, item, delim))
         {
             if(!item.empty())
             {
                 double val = stod(item);
                 elems.push_back(val);
             }
         }
         switch(delim)
         {
             case '/':
             if(elems.size() == 0 || elems[0] <= 0 || elems[0] > 12 ||  elems[1] <= 0 || elems[1] > 31 || elems[2] < 2015 || elems[2] > 4000)
                return false;

             if(elems[0] != 2)
             {
                if(elems[1] > validdays[(int)elems[0] - 1])
                {
                      return false;
                }
             }
             else
             {
                bool leapY =  (((int)elems[2] - leapyear) % 4 ) == 0;
                if(leapY )
                {
                    if(  elems[1] > (validdays[(int)elems[0] - 1]) + 1 )
                      return false;
                }
                else
                {
                    if(  elems[1] > (validdays[(int)elems[0] - 1]))
                      return false;
                }
             }
             break;
            case ':':
             if(elems.size() == 0 || elems[0] < 0 || elems[0] > 23 ||  elems[1] < 0 || elems[1] > 59 || elems[2] < 0 || elems[2] > 59)
                return false;

                break;
         }
         return true;
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommentEntryScreen::CommentEntryScreen()
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    mainMenuIndexPrevious = -1;
    subMenuIndexPrevious = -1;
    subMenuName =  COMMENT_SYSTEM_SCREEN_LABEL_STRING;
    mainMenuName = DATA_LOGGING_STRING;
    btnfinishInstate.first = BTN_FINISH_INSTATE5;
    btnfinishInstate.second = -1;
    btncancelInstate.first = BTN_CANCEL_INSTATE5;
    btncancelInstate.second = -1;
    initialsTxt.first = INITIALS_TEXT;
    initialsTxt.second = "";
    commentTxt.first = COMMENT_TEXT;
    commentTxt.second = "";
    statuslbl.first = STATUS_COMMENT_LABEL_STRING;
    statuslbl.second = STATUS_COMMENT_LABEL_TEXT[0];
    statusVisibility.first = STATUS_LABEL_COMMENT_VISIBILITY;
    statusVisibility.second = 0.0;
    btnFinishVisibility.first = BTN_FINISH_COMMENT_VISIBILITY;
    btnFinishVisibility.second = 1.0;



}

CommentEntryScreen::~CommentEntryScreen()
{

}

void CommentEntryScreen::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{
    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)// || (ptr->utility->commentbuttonclicked ))
    {

        //cout << "Processing "<< mainMenuName << " " << subMenuName << " MainManu = " << mainMenuName <<" MainMenuIndex = "<< mainMenuIndex << " SubMenuIndex = "<<subMenuIndex << endl;
        DEBUGF_VDT("mainMenuName = [%s] subMenuName = [%s] MainManuIndex = [%d] SubMenuIndex = [%d]\n",mainMenuName.c_str(),subMenuName.c_str(),mainMenuIndex,subMenuIndex);
        ptrDrawingArea->Viewport.GetResource(btnfinishInstate.first.c_str(),&btnfinishInstate.second);
        ptrDrawingArea->Viewport.GetResource(btncancelInstate.first.c_str(),&btncancelInstate.second);

        ptrDrawingArea->Viewport.GetResource( btnFinishVisibility.first.c_str(),&btnFinishVisibility.second);
        if(btnfinishInstate.second == 1 && btnFinishVisibility.second == 1)
        {
            const char * i,*c;
            ptrDrawingArea->Viewport.GetResource(initialsTxt.first.c_str(),&i);
            initialsTxt.second = string(i);
            ptrDrawingArea->Viewport.GetResource(commentTxt.first.c_str(),&c);
            commentTxt.second = string(c);

            timer(TIME_DELAY_COMMENT,&sendToDDS,initialsTxt.second,commentTxt.second,ptr);

        }
        else if(btncancelInstate.second == 1)
        {
            DEBUGF_VDT("Start CommentEntryScreen  Page Button Cancel pressed\n");
            ptr->SelectMainMenuItem((GlgLong)ptr->MainMenuIndex,0,true);
            DEBUGF_VDT("Finish CommentEntryScreen Page Button Cancel pressed\n");
        }

        ptrDrawingArea->Viewport.SetResource(initialsTxt.first.c_str(),"");
        ptrDrawingArea->Viewport.SetResource(commentTxt.first.c_str(),"");
        ptrDrawingArea->Viewport.SetResource("btnFinish/Visibility",-0.3);
        GlgSetFocus(ptrDrawingArea->Viewport, (char*)"initialsTxt" );
    }
}


void CommentEntryScreen::sendToDDS(string initials,string comment,GlgSCADAViewer *ptr)
{
    DEBUGF_VDT("FINISH CommentEntryScreen  Page Button Finish pressed\n");
    string statuslbl  = STATUS_COMMENT_LABEL_TEXT[0];
    //statusVisibility.second = 1.0;
    //btnFinishVisibility.second = -0.3;
    ptr->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
    ptr->DrawingArea.Viewport.SetResource( "statuslbl/Visibility",1.0);
    ptr->DrawingArea.Viewport.SetResource( "btnFinish/Visibility", -0.3);
    DEBUGF_VDT("Start sending to the Server Initials =[%s] Comment = [%s]\n",initials.c_str(), comment.c_str());
    int commentType = 0;
    int istatus =  ptr->pDataFeed->WriteComment(commentType, (char*)initials.c_str(), (char*)comment.c_str());
    if(istatus == -1)
    {
         statuslbl = STATUS_COMMENT_LABEL_TEXT[2];
         ERRORF_VDT("CommentEntryScreen::sendToDDS: Responce from Server commentType =[%d]  operatorName = [%s] commentText = [%s]  Server ERROR Received status = %d\n",commentType,initials.c_str(),comment.c_str(), istatus);
    }
    else
    {
         statuslbl = STATUS_COMMENT_LABEL_TEXT[1];
         DEBUGF_VDT("CommentEntryScreen::sendToDDS: Responce from Server commentType =[%d]  operatorName = [%s] commentText = [%s]  Server SUCCESS Received status = %d\n",commentType,initials.c_str(),comment.c_str(), istatus);
    }
    ptr->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());

}
void CommentEntryScreen::timer(int d,  void (*f)(string ,string ,GlgSCADAViewer *  ),string initials,string comment,GlgSCADAViewer *ptr)
{
    std::thread([d,f,initials,comment,ptr](){
        std::this_thread::sleep_for(std::chrono::seconds(d));
        f(initials,comment,ptr);
    }).detach();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AlarmVariableModification::Init( int nNames,int nPoints)
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName =  "";
    mainMenuName = UTILITY_LABEL_STRING;

    type = NOTDEFINED;
    names = nNames;
    points = nPoints;
    btnfinishInstate.first = BTN_FINISH_INSTATE6;
    btnfinishInstate.second = -1;
    btncancelInstate.first = BTN_CANCEL_INSTATE6;
    btncancelInstate.second = -1;
    parameterNumber.first = PAPAMETER_NUMBER;
    parameterNumber.second = "";
    parameterName.first = ALARM_VARIABLE_MODIFICATION_PARAMETER_NAME;
    parameterName.second = "";
    operatorName.first = OPERATOR_NAME;
    operatorName.second = "";
    comment.first = ALARM_VARIABLE_COMMENT;
    comment.second = "";

    pair<string,double> p;
    vector<pair<string,double>> temp;
    for(int i = 0; i < names;i++)
    {
        for(int j = 0;j < points; j++ )
        {
            p.first = SETPOINTS[i][j];
            p.second = 0;
            temp.push_back(p);
        }
        setpoints.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<6;i++)
    {
        statuslbl[i].first = ALARM_VAR_STATUS_LABEL[i];
        statuslbl[i].second = ALARM_VAR_STATUS_LABEL_TEXT[i][0];
        statusVisibility[i].first = ALARM_VAR_STATUS_LABEL_VISIBILITY[i];
        statusVisibility[i].second = 0.0;
    }

    btnFinishVisibility.first = BTN_FINISH6_VISIBILITY;
    btnFinishVisibility.second = 1.0;
}

AlarmVariableModification::~AlarmVariableModification()
{
    for(int i = 0; i < names;i++)
    {
        setpoints.clear();
    }
}
std::mutex mAlarms;
void AlarmVariableModification::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{
    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
    {

        DEBUGF_VDT("START AlarmVariableModification Page mainMenuName = [%s] subMenuName = [%s] MainMenuIndex = [%d] SubMenuIndex = [%d] Button Finish pressed\n",mainMenuName.c_str(),subMenuName.c_str(),mainMenuIndex,subMenuIndex);
        ptrDrawingArea->Viewport.GetResource(btnfinishInstate.first.c_str(),&btnfinishInstate.second);
        ptrDrawingArea->Viewport.GetResource(btncancelInstate.first.c_str(),&btncancelInstate.second);
        ptrDrawingArea->Viewport.GetResource(btnFinishVisibility.first.c_str(),&btnFinishVisibility.second);
        if(btnfinishInstate.second == 1 && btnFinishVisibility.second ==  1)
        {
            const char * pNumber,*pName,*oName,*pComment;
            ptr->DrawingArea.Viewport.GetResource( parameterNumber.first.c_str(),&pNumber);
            ptr->DrawingArea.Viewport.GetResource( parameterName.first.c_str(),&pName);
            ptr->DrawingArea.Viewport.GetResource( operatorName.first.c_str(),&oName);
            ptr->DrawingArea.Viewport.GetResource( comment.first.c_str(),&pComment);
            parameterNumber.second = string(pNumber);
            parameterName.second = string(pName);
            operatorName.second = string(oName);
            comment.second = string(pComment);
            pair<pair<string,double>,pair<string,double>> rangetemp;
            for(int i=0;i< names;i++)
            {
                    for(int j=0;j<points;j++)
                    {
                         ptr->DrawingArea.Viewport.GetResource( setpoints[i][j].first.c_str(),&setpoints[i][j].second);
                    }
            }
            if(type == DIGITAL_TYPE)
            {
                rangetemp.first.first = "";
                rangetemp.first.second = 0;
                rangetemp.second.first ="";
                rangetemp.second.second=0;
            }
            else if(type == ANALOG_TYPE)
            {
                AnalogAlarmVariableModification * ins = dynamic_cast<AnalogAlarmVariableModification *>(this);
                ptrDrawingArea->Viewport.GetResource(ins->range.first.first.c_str(),&ins->range.first.second);
                ptrDrawingArea->Viewport.GetResource(ins->range.second.first.c_str(),&ins->range.second.second);
                rangetemp = ins->range;

            }
            mAlarms.lock();
            ALARMS_FINISHED=-1;
            mAlarms.unlock();
            timer(0,  sendToDDS,type,rangetemp,parameterNumber,parameterName,operatorName,comment,setpoints,ptr);
            timer(20,   DelayAlamsCall,type,rangetemp,parameterNumber,parameterName,operatorName,comment,setpoints,ptr);


        }
        else if(btncancelInstate.second == 1)
        {
            DEBUGF_VDT("Start AlarmVariableModification %s Page Button Cancel pressed\n",(STATUS_PAGE_TYPE_NAME[(int)type]).c_str());
            ptr->SelectMainMenuItem((GlgLong)ptr->MainMenuIndex,0,true);
            DEBUGF_VDT("Finish AlarmVariableModification % Page Button Cancel pressed\n",(STATUS_PAGE_TYPE_NAME[(int)type]).c_str());
        }
    }
}
 void  AlarmVariableModification::DelayAlamsCall(STATUS_PAGE_TYPE type, pair<pair<string,double>,pair<string,double>>,pair<string,string> parameterNumber,pair<string,string> parameterName,pair<string,string> operatorName,pair<string,string> comment,vector<vector<pair<string,double>>> setpoints, GlgSCADAViewer *scadaViewer)
 {

     if(ALARMS_FINISHED != 0)
     {
         mAlarms.lock();
         ALARMS_FINISHED =1;
         mAlarms.unlock();
        scadaViewer->DrawingArea.Viewport.SetResource( "btnFinish/Visibility",-0.3);
        string statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][0];
        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/Visibility", 0.0);
        scadaViewer->DrawingArea.Viewport.SetResource( comment.first.c_str(),"Time Out Server Error");
     }

 }
void AlarmVariableModification::sendToDDS(STATUS_PAGE_TYPE type, pair<pair<string,double>,pair<string,double>> range,pair<string,string> parameterNumber,pair<string,string> parameterName,pair<string,string> operatorName,pair<string,string> comment,vector<vector<pair<string,double>>> setpoints, GlgSCADAViewer *scadaViewer)
{
    scadaViewer->DrawingArea.Viewport.SetResource( "btnFinish/Visibility",-0.3);
    string statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][0];
    scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
    scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/Visibility", 1.0);

    ANALOGALARMVARLOGMODSTR  avalue;
    DIGITALALARMVARLOGMODSTR dvalue;
    int numberOfNames = -1;
    int numberOfPoints =-1;
    DEBUGF_VDT("AlarmVariableModification::sendToDDS  Page type = [%d] Pointid = [%s] Button Finish pressed\n",(int)type,parameterNumber.second.c_str());
    int st=-1,st1=-1,tdelay = -1;
    if(isValid((char *)parameterNumber.second.c_str()))
    {
        if(type == ANALOG_TYPE)
        {
            numberOfNames = NUMBER_OF_ANALOG_SETPOINT_NAMES;
            numberOfPoints = NUMBER_OF_ANALOG_SETPOINTS_IN_EACH_NAME;
            memcpy(avalue.pointID,parameterNumber.second.c_str(),MAXPOINTIDLEN);
            memcpy(avalue.longName,parameterName.second.c_str(),MAXLONGNAMELEN);
            memcpy(avalue.comment,comment.second.c_str(),MAXCOMMENTLEN);
            memcpy(avalue.operatorName,operatorName.second.c_str(),MAXOPERATORNAMELEN);

            avalue.rangeLow = range.first.second;
            avalue.rangeHigh = range.second.second;

            ALARMSETPOINTS  spoints;
            spoints.setPointHighHigh = setpoints[1][0].second;
            spoints.setPointHigh = setpoints[1][1].second;
            spoints.setPointLow = setpoints[1][2].second;
            spoints.setPointLowLow = setpoints[1][3].second;

            avalue.setPtHighHigh = setpoints[1][0].second;
            avalue.setPtHigh = setpoints[1][1].second;
            avalue.setPtLow = setpoints[1][2].second;
            avalue.setPtLowLow = setpoints[1][3].second;
            st =-1;

            st = scadaViewer->pDataFeed->WriteAlarmSetpoints((char *)parameterNumber.second.c_str(),&spoints);


            if(st == -1)
            {
                statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[1][2];
                scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl1/String", statuslbl.c_str());
                ERRORF_VDT("ERROR SETPOINTS receiveFromDDS pointid  = [%s]  Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),st);
            }
            else
            {
                statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[1][1];
                scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl1/String", statuslbl.c_str());

                setpoints[1][0].second = spoints.setPointHighHigh;
                setpoints[1][1].second = spoints.setPointHigh;
                setpoints[1][2].second = spoints.setPointLow;
                setpoints[1][3].second = spoints.setPointLowLow;

                DEBUGF_VDT("STARTED SETPOINTS sendToDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st);
                for(int j=0;j < NUMBER_OF_ANALOG_SETPOINTS_IN_EACH_NAME;j++)
                {
                    DEBUGF_VDT(" setpoints[%d] = [%f]  ",  j,setpoints[1][j].second);
                }
                DEBUGF_VDT("FINISHED SETPOINTS sendToDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st);
            }
            scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl1/Visibility", 1.0);

            ALARMRESET pasp;
            pasp.resetHighHigh = setpoints[2][0].second;
            pasp.resetHigh = setpoints[2][1].second;
            pasp.resetLow = setpoints[2][2].second;
            pasp.resetLowLow = setpoints[2][3].second;

            avalue.resetPtHighHigh = setpoints[2][0].second;
            avalue.resetPtHigh = setpoints[2][1].second;
            avalue.resetPtLow = setpoints[2][1].second;
            avalue.resetPtLowLow = setpoints[2][1].second;

            st1 = scadaViewer->pDataFeed->WriteAlarmReset((char *)parameterNumber.second.c_str(),&pasp);
            if(st1 == -1)
            {
                statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[2][2];
                scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl2/String", statuslbl.c_str());
                ERRORF_VDT("ERROR RESET sendToDDS pointid  = [%s]  Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),st1);
            }
            else
            {
                statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[2][1];
                scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl2/String", statuslbl.c_str());

                setpoints[2][0].second = pasp.resetHighHigh;
                setpoints[2][1].second = pasp.resetHigh;
                setpoints[2][2].second = pasp.resetLow;
                setpoints[2][3].second = pasp.resetLowLow;
                DEBUGF_VDT("STARTED RESET sendToDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st1);
                for(int j =0; j < NUMBER_OF_ANALOG_SETPOINTS_IN_EACH_NAME; j++)
                {
                    DEBUGF_VDT(" setpoints[%d] = [%f]  ", j, setpoints[2][j].second);
                }
                DEBUGF_VDT("FINISHED  RESET sendToDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st1);

            }
            scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl2/Visibility",1.0);
            avalue.timeDelayHighHigh = setpoints[0][0].second ;
            avalue.timeDelayHigh = setpoints[0][1].second ;
            avalue.timeDelayLow = setpoints[0][2].second ;
            avalue.timeDelayLowLow = setpoints[0][3].second ;
        }
        else if(type == DIGITAL_TYPE)
        {
            numberOfNames = NUMBER_OF_DIGITAL_SETPOINT_NAMES;
            numberOfPoints = NUMBER_OF_DIGITAL_SETPOINTS_IN_EACH_NAME;
            memcpy(dvalue.pointID,parameterNumber.second.c_str(),MAXPOINTIDLEN);
            memcpy(dvalue.longName,parameterName.second.c_str(),MAXLONGNAMELEN);
            memcpy(dvalue.comment,comment.second.c_str(),MAXCOMMENTLEN);
            memcpy(dvalue.operatorName,operatorName.second.c_str(),MAXOPERATORNAMELEN);
            dvalue.time_delay = setpoints[0][0].second;
        }

        tdelay = 1;
        tdelay = scadaViewer->pDataFeed->WriteAlarmTimeDelay((char *)parameterNumber.second.c_str(),setpoints[0][0].second);
        if(tdelay == -1)
        {
            statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[0][2];
            scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl0/String", statuslbl.c_str());
            ERRORF_VDT("ERROR Time sendToDDS pointid  = [%s]  time = [%f] Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),setpoints[0][0].second,tdelay);
        }
        else
        {
            DEBUGF_VDT("STARTED TIME DELAY sendToDDS pointid  = [%s]  Server SUCCESS Received status\n", parameterNumber.second.c_str());
            statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[0][1];
            scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl0/String", statuslbl.c_str());

            for(int j =0; j < numberOfPoints; j++)
            {
                setpoints[0][j].second = tdelay;
                DEBUGF_VDT(" setpoints[%d] = [%f]  ", j, setpoints[0][j].second);
            }

            DEBUGF_VDT("FINISHED TIME DELAY sendToDDS pointid  = [%s]  Server SUCCESS Received status\n", parameterNumber.second.c_str());
        }


        if(type == ANALOG_TYPE)
        {
             scadaViewer->DrawingArea.Viewport.SetResource(  "statuslbl0/Visibility", 1.0);
            if(st != -1 && st1 != -1 && tdelay != -1)
            {
                int astatus = scadaViewer->pDataFeed->WriteAnalogAlarmVariableModEntry(&avalue);

                if(ALARMS_FINISHED != 1)
                {
                    mAlarms.lock();
                    ALARMS_FINISHED = 0;
                    mAlarms.unlock();
                    if(astatus == -1)
                    {
                        string error= "ERROR TO WRITE ANALOG LOG ENTRY";
                        scadaViewer->DrawingArea.Viewport.SetResource( comment.first.c_str(),error.c_str());
                        statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][2];
                        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
                        ERRORF_VDT("ERROR WriteAnalogAlarmVariableModEntry pointid  = [%s]  name = [%s] rlow = [%f] rhigh =[%f] opname = [%s] comment =[%s] Server ERROR Received astatus = [%d]\n", avalue.pointID,avalue.longName,avalue.rangeLow,avalue.rangeHigh,avalue.operatorName,avalue.comment,astatus);

                    }
                    else
                    {
                        statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][1];
                        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
                        DEBUGF_VDT("SUCCESS WriteAnalogAlarmVariableModEntry pointid  = [%s]  name = [%s] rlow = [%f] rhigh =[%f] opname = [%s] comment =[%s] Server ERROR Received astatus = [%d]\n", avalue.pointID,avalue.longName,avalue.rangeLow,avalue.rangeHigh,avalue.operatorName,avalue.comment,astatus);
                    }
                    DEBUGF_VDT("START DATA Written WriteAnalogAlarmVariableModEntry \n");
                    for(int i =0;i <  numberOfNames;i++)
                    {
                        for(int j=0;j < numberOfPoints;j++)
                        {
                            DEBUGF_VDT("[%f]  ",setpoints[i][j].second);
                        }
                        DEBUGF_VDT("\n");
                    }
                }
                DEBUGF_VDT("FINISH DATA Written WriteAnalogAlarmVariableModEntry \n");
            }
            else
            {
                string error= "ERROR TO WRITE ";
                if(st == -1)
                    error = error + "SETPOINTS;";
                if(st1 == -1)
                    error = error + "RESETS;";
                if(tdelay == 1)
                    error = error + "TIME";
                scadaViewer->DrawingArea.Viewport.SetResource( comment.first.c_str(),error.c_str());
                scadaViewer->DrawingArea.Viewport.SetResource( "btnFinish/Visibility",1.0);
                statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][2];
                scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
            }
         }
        else if(type == DIGITAL_TYPE)
        {
            if(tdelay != -1)
            {
                int dstatus = scadaViewer->pDataFeed->WriteDigitalAlarmVariableModEntry(&dvalue);

                if(ALARMS_FINISHED != 1)
                {
                    mAlarms.lock();
                    ALARMS_FINISHED = 0;
                    mAlarms.unlock();

                    if(dstatus == -1)
                    {
                        string error= "ERROR TO WRITE DIGITAL LOG ENTRY";
                        scadaViewer->DrawingArea.Viewport.SetResource( comment.first.c_str(),error.c_str());
                        statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][2];
                        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
                        ERRORF_VDT("ERROR WriteDigitalAlarmVariableModEntry pointid  = [%s]  name = [%s] opname = [%s] comment =[%s] timedelay = [%d] Server ERROR Received astatus = [%d]\n", dvalue.pointID,dvalue.longName,dvalue.operatorName,dvalue.comment,dvalue.time_delay,dstatus);

                    }
                    else
                    {
                        statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][1];
                        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
                        ERRORF_VDT("SUCCESS WriteDigitalAlarmVariableModEntry pointid  = [%s]  name = [%s] opname = [%s] comment =[%s] timedelay = [%d] Server ERROR Received astatus = [%d]\n", dvalue.pointID,dvalue.longName,dvalue.operatorName,dvalue.comment,dvalue.time_delay,dstatus);
                    }
                }
            }
            else
            {

                string error= "ERROR TO WRITE TIME";
                scadaViewer->DrawingArea.Viewport.SetResource( comment.first.c_str(),error.c_str());

                scadaViewer->DrawingArea.Viewport.SetResource( "btnFinish/Visibility",1.0);
                statuslbl = ALARM_VAR_STATUS_LABEL_TEXT[3][2];
                scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());

            }
        }
    }
    else
    {
        statuslbl = "Data Point is Invalid";
        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/String", statuslbl.c_str());
        scadaViewer->DrawingArea.Viewport.SetResource( "statuslbl/Visibility", 1.0);
        parameterName.second = "";
        scadaViewer->DrawingArea.Viewport.SetResource( parameterName.first.c_str(), parameterName.second.c_str());
        DEBUGF_VDT("ERROR sendToDDS  Invalid POINT ID  = [%s] status\n", parameterNumber.second.c_str());
    }
    DEBUGF_VDT("FINISH AlarmVariableModification %d Page Pointid = [%s] Button Finish pressed\n",(int)type,parameterNumber.second.c_str());
}
void AlarmVariableModification::timer(int d,  void (*f)(STATUS_PAGE_TYPE, pair<pair<string,double>,pair<string,double>> ,pair<string,string> ,pair<string,string> ,pair<string,string> ,pair<string,string> ,vector<vector<pair<string,double>>> , GlgSCADAViewer * ),STATUS_PAGE_TYPE type, pair<pair<string,double>,pair<string,double>> range,pair<string,string> parameterNumber,pair<string,string> parameterName,pair<string,string> operatorName,pair<string,string> comment,vector<vector<pair<string,double>>> setpoints, GlgSCADAViewer *ptr)
{
     std::thread  ([d,f,type,range,parameterNumber,parameterName, operatorName,comment,setpoints,ptr](){
        std::this_thread::sleep_for(std::chrono::seconds(d));
        f(type,range,parameterNumber,parameterName, operatorName,comment,setpoints,ptr);
    }).detach();


}
void AlarmVariableModification::ProcessInput(string action,string origin, GlgDrawingArea * drawingArea)
{
    if(drawingArea->parent->MainMenuIndex == this->mainMenuIndex && drawingArea->parent->SubMenuIndex == this->subMenuIndex)
    {
        if(strcmp(origin.c_str(),"ParameterName") == 0)
        {
            drawingArea->Viewport.SetResource(parameterName.first.c_str(),parameterName.second.c_str());
        }
    }
}

void AlarmVariableModification::receiveFromDDS(GlgSCADAViewer *scadaViewer)
{
     DEBUGF_VDT("START AlarmVariableModification %d Page Pointid = [%s] Button Finish pressed\n",(int)type,parameterNumber.second.c_str());

      for(int i=0;i<6;i++)
      {
          if((type == DIGITAL_TYPE && i == 3) || type == ANALOG_TYPE)
          {
            statuslbl[i].first = ALARM_VAR_STATUS_LABEL[i];
            statuslbl[i].second = ALARM_VAR_STATUS_LABEL_TEXT[i][0];
            statusVisibility[i].first = ALARM_VAR_STATUS_LABEL_VISIBILITY[i];
            statusVisibility[i].second = 0.0;
            scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[i].first.c_str(), statuslbl[i].second.c_str());
            scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[i].first.c_str(), statusVisibility[i].second);
         }
      }

     parameterName.second = "";
     scadaViewer->DrawingArea.Viewport.SetResource( parameterName.first.c_str(), parameterName.second.c_str());

     char  longname[150];

     for(int x=0;x<150;x++)
     {
         longname[x] = '\0';
     }

     int st =-1;
     bool isvalidid = scadaViewer->pDataFeed->ValidateDataPoint((char *)parameterNumber.second.c_str());
     if(isvalidid)
     {

            st = scadaViewer->pDataFeed->ReadLongName((char *)parameterNumber.second.c_str(),longname,150);

            if(st == -1)
            {
                statuslbl[3].second = ALARM_VAR_STATUS_LABEL_TEXT[3][2];
                statusVisibility[3].second =1.0;
                scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[3].first.c_str(), statuslbl[3].second.c_str());
                scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[3].first.c_str(), statusVisibility[3].second);
                parameterName.second = "";
                ERRORF_VDT("Fail to get Name pointid  = [%s]  Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),st);
                scadaViewer->DrawingArea.Viewport.SetResource( parameterName.first.c_str(), parameterName.second.c_str());
            }
            else
            {
                parameterName.second = string(longname);
                scadaViewer->DrawingArea.Viewport.SetResource( parameterName.first.c_str(), parameterName.second.c_str());
                DEBUGF_VDT("Got Name pointid  = [%s]  Server SUCCSES Received status = [%d]\n", parameterNumber.second.c_str(),st);
            }

            if(type == ANALOG_TYPE)
            {
                AnalogAlarmVariableModification * ins = static_cast<AnalogAlarmVariableModification *>(this);
                scadaViewer->DrawingArea.Viewport.SetResource( ins->range.first.first.c_str(), -1.0);
                scadaViewer->DrawingArea.Viewport.SetResource( ins->range.second.first.c_str(),-1.0);
                for(int i=0;i<names;i++)
                {
                    for(int j=0;j<points;j++)
                    {
                        scadaViewer->DrawingArea.Viewport.SetResource(setpoints[i][j].first.c_str(), -1);
                     }
                }
                ins->range.first.second = -1;
                ins->range.first.second =  scadaViewer->pDataFeed->ReadEngineeringLow((char *)parameterNumber.second.c_str());
                if(ins->range.first.second == -1)
                {
                    statuslbl[4].second = "Fail to get Range Low Server Error";
                    statusVisibility[4].second =1.0;
                    scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[4].first.c_str(), statuslbl[4].second.c_str());
                    scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[4].first.c_str(), statusVisibility[4].second);
                    ERRORF_VDT("Fail to get Range Low pointid  = [%s]  Server ERROR Received status = [%f]\n", parameterNumber.second.c_str(),ins->range.first.second);
                }
                else
                {

                    scadaViewer->DrawingArea.Viewport.SetResource( ins->range.first.first.c_str(), ins->range.first.second);
                    DEBUGF_VDT("Got Range Low pointid  = [%s]  Low = [%f] Server SUCCSES Received status \n", parameterNumber.second.c_str(),ins->range.first.second,ins->range.first.second);
                }
                ins->range.second.second = -1;
                ins->range.second.second = scadaViewer->pDataFeed->ReadEngineeringHigh((char *)parameterNumber.second.c_str());
                if(ins->range.second.second == -1)
                {
                    statuslbl[5].second = "Fail to get Range High Server Error";
                    statusVisibility[5].second =1.0;
                    scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[5].first.c_str(), statuslbl[5].second.c_str());
                    scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[5].first.c_str(), statusVisibility[5].second);
                    ERRORF_VDT("Fail to get Range High pointid  = [%s]  Server ERROR Received status = [%f]\n", parameterNumber.second.c_str(),ins->range.second.second);
                }
                else
                {
                    scadaViewer->DrawingArea.Viewport.SetResource( ins->range.second.first.c_str(), ins->range.second.second);
                    DEBUGF_VDT("Got Range High pointid  = [%s]  High = [%f] Server SUCCSES Received status = [%f]\n", parameterNumber.second.c_str(),ins->range.second.second,ins->range.second.second);
                }
                ALARMSETPOINTS spoints;
                int st1 = -1;
                st1 = scadaViewer->pDataFeed->ReadAlarmSetpoints((char *)parameterNumber.second.c_str(),&spoints);
                if(st1 == -1)
                {
                    statuslbl[1].second = "Setpoints Server Error";
                    statusVisibility[1].second =1.0;
                    scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[1].first.c_str(), statuslbl[1].second.c_str());
                    scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[1].first.c_str(), statusVisibility[1].second);
                    ERRORF_VDT("ERROR SETPOINTS receiveFromDDS pointid  = [%s]  Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),st1);
                }
                else
                {
                    setpoints[1][0].second = spoints.setPointHighHigh;
                    setpoints[1][1].second = spoints.setPointHigh;
                    setpoints[1][2].second = spoints.setPointLow;
                    setpoints[1][3].second = spoints.setPointLowLow;

                    DEBUGF_VDT("STARTED SETPOINTS receiveFromDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st1);
                    for(int j=0;j<points;j++)
                    {
                         DEBUGF_VDT(" setpoints[%d] = [%f]  ",  j,setpoints[1][j].second);
                        scadaViewer->DrawingArea.Viewport.SetResource(setpoints[1][j].first.c_str(), setpoints[1][j].second);
                    }
                    DEBUGF_VDT("FINISHED SETPOINTS receiveFromDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st1);
                }
                ALARMRESET pasp;
                int st2=-1;
                st2 = scadaViewer->pDataFeed->ReadAlarmReset((char *)parameterNumber.second.c_str(),&pasp);
                if(st2 == -1)
                {
                    statuslbl[2].second = "Reset Server Error";
                    statusVisibility[2].second =1.0;
                    scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[2].first.c_str(), statuslbl[2].second.c_str());
                    scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[2].first.c_str(), statusVisibility[2].second);
                    ERRORF_VDT("ERROR RESET receiveFromDDS pointid  = [%s]  Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),st2);
                }
                else
                {
                    setpoints[2][0].second = pasp.resetHighHigh;
                    setpoints[2][1].second = pasp.resetHigh;
                    setpoints[2][2].second = pasp.resetLow;
                    setpoints[2][3].second = pasp.resetLowLow;
                    DEBUGF_VDT("STARTED RESET receiveFromDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st2);
                    for(int j =0; j < points; j++)
                    {
                        DEBUGF_VDT(" setpoints[%d] = [%f]  ", j, setpoints[2][j].second);
                        scadaViewer->DrawingArea.Viewport.SetResource(setpoints[2][j].first.c_str(), setpoints[2][j].second);
                    }
                    DEBUGF_VDT("FINISHED  RESET receiveFromDDS pointid  = [%s]  Server SUCCESS Received status = [%d]\n", parameterNumber.second.c_str(),st2);
                }
            }
            int tdelay = -1;
            tdelay = scadaViewer->pDataFeed->ReadAlarmTimeDelay((char *)parameterNumber.second.c_str());
            if(tdelay == -1)
            {
                if(type == ANALOG_TYPE)
                {
                    statuslbl[0].second = "Time Delay Server Error";
                    statusVisibility[0].second =1.0;
                    scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[0].first.c_str(), statuslbl[0].second.c_str());
                    scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[0].first.c_str(), statusVisibility[0].second);
                }
                else if(type == DIGITAL_TYPE)
                {
                    statuslbl[3].second = "Time Delay Server Error";
                    statusVisibility[3].second =1.0;
                    scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[3].first.c_str(), statuslbl[3].second.c_str());
                    scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[3].first.c_str(), statusVisibility[3].second);
                }
                ERRORF_VDT("ERROR Timr Delay receiveFromDDS pointid  = [%s]  Server ERROR Received status = [%d]\n", parameterNumber.second.c_str(),tdelay);
            }
            else
            {
                DEBUGF_VDT("STARTED TIME DELAY receiveFromDDS pointid  = [%s]  Server SUCCESS Received status\n", parameterNumber.second.c_str());

                for(int j =0; j < points; j++)
                {
                    setpoints[0][j].second = tdelay;
                    DEBUGF_VDT(" setpoints[%d] = [%f]  ", j, setpoints[0][j].second);
                    scadaViewer->DrawingArea.Viewport.SetResource(setpoints[0][j].first.c_str(), setpoints[0][j].second);
                }

                DEBUGF_VDT("FINISHED TIME DELAY receiveFromDDS pointid  = [%s]  Server SUCCESS Received status\n", parameterNumber.second.c_str());
            }
     }
     else
     {
         statuslbl[3].second = "Data Point is Invalid";
         statusVisibility[3].second =1.0;
         scadaViewer->DrawingArea.Viewport.SetResource( statuslbl[3].first.c_str(), statuslbl[3].second.c_str());
         scadaViewer->DrawingArea.Viewport.SetResource( statusVisibility[3].first.c_str(), statusVisibility[3].second);
         parameterName.second = "";
         scadaViewer->DrawingArea.Viewport.SetResource( parameterName.first.c_str(), parameterName.second.c_str());
         DEBUGF_VDT("ERROR receiveFromDDS  Invalid POINT ID  = [%s] status\n", parameterNumber.second.c_str());
     }
     DEBUGF_VDT("FINISH AlarmVariableModification %d Page Pointid = [%s] Button Finish pressed\n",(int)type,parameterNumber.second.c_str());

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DigitalAlarmVariableModification::DigitalAlarmVariableModification(int nNames,int nPoints)
{

    Init(nNames,nPoints);
    subMenuName =  DIGITAL_ALARM_VARIABLE_MODIFICATION_LABEL_STRING;
    type = DIGITAL_TYPE;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnalogAlarmVariableModification::AnalogAlarmVariableModification(int nNames,int nPoints)
{
    Init(nNames,nPoints);
    subMenuName =  ANALOG_ALARM_VARIABLE_MODIFICATION_LABEL_STRING;
    type =ANALOG_TYPE;
    range.first.first = RANGE[0];
    range.first.second = -1;
    range.second.first = RANGE[1];
    range.second.second = -1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tank::Tank(){}
Tank::Tank(string name)
{
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName = name;
    mainMenuName = TANKS_LABEL_STRING;
    values.push_back(pair<string,double>("Engr_Low",-1));
    values.push_back(pair<string,double>("Alm_Ll_Setpoint",-1));
    values.push_back(pair<string,double>("Alm_Lo_Setpoint",-1));
    values.push_back(pair<string,double>("Alm_Hi_Setpoint",-1));
    values.push_back(pair<string,double>("Alm_Hh_Setpoint",-1));
    values.push_back(pair<string,double>("Capacity",-1));
}
Tank::~Tank(){};
void Tank::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr){}
void Tank::printData(){}
void Tank::ProcessTags(GlgSCADAViewer *ptr,GlgTagRecord *tag_record,double value,bool option,int start,int end,int tankpagenumber)
{

    map<string,double>::iterator i;
    string source(tag_record->tag_source);

    string str = source;
    if(start < end - 1)
    {
        //tanksdata[source] = value;
        bool found = false;
        for(int a=0;a<values.size();a++)
        {
               if(str.find(values[a].first)  != string::npos)
               {
                    tanksdata[source] = value;
                    found = true;
               }
        }
        if(!found)
             ptr->SetTag( tag_record->tag_source, value, false );
    }
    else if(start == end - 1)
    {
        int found = false;
        for(int a=0;a<values.size();a++)
        {
               if(str.find(values[a].first)  != string::npos)
               {
                    tanksdata[source] = value;
                    found = true;
               }
        }
        if(!found)
             ptr->SetTag(tag_record->tag_source, value, false );
       //tanksdata[source] = value;
       for( i = tanksdata.begin();i != tanksdata.end(); i++ )
       {
           //cout << i->first << " = "<< i->second << endl;
       }
        cout <<"Recieved Values end"<<endl;
        vector<map<string,double>> maps;
        int j = 0;
        map<string,double>  temp;
        //cout <<"Recieved Values begin"<<endl;
        int count =0;
        for( i = tanksdata.begin();i != tanksdata.end(); i++ )
         {
             //cout << i->first << " "<<i->second << endl;
             temp[i->first] = i->second;
             if( j < 5 )
                     j++;
                 else
                 {
                     j=0;
                     count++;
                     maps.push_back(temp);
                     temp.clear();
                 }
        }


       map<string,double>::iterator it;
       cout <<"CURRENT MAPS begin = "<<maps.size() << endl;
       for(int y =0 ;y< maps.size();y++)
       {
           cout << "MAP Number = "<< y << endl;
           for(it=maps[y].begin();it != maps[y].end();it++)
           {
               cout << it->first << " = "<< it->second << endl;
           }
           cout <<"#################"<<endl;
       }
       cout <<"CURRENT MAPS end"<<endl;

       for(int y =0 ;y< maps.size();y++)
       {
           FindTankRealData(maps[y]);
       }
       cout << "Modified Values begin "<<endl;
       for(int y =0 ;y< maps.size();y++)
       {
           for(it=maps[y].begin();it != maps[y].end();it++)
           {
               cout << it->first << " = "<< it->second << endl;
               ptr->SetTag( it->first.c_str(),it->second, false );
           }
       }
       cout << "Modified Values end "<<endl;
       tanksdata.clear();
       maps.clear();
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tank::FindTankRealData(map<string,double> & m)
{
    map<string,double>::iterator i;
    for(i=m.begin();i != m.end();i++)
    {
        string str = i->first;
        for(int a=0;a<values.size();a++)
        {
            if(str.find(values[a].first)  != string::npos)
                values[a].second = i->second;
        }
    }

    if(values[2].second <= values[0].second || values[2].second >= values[5].second)
    {
        values[2].second = values[0].second ;
    }
    if(values[1].second >= values[2].second || values[1].second <= values[0].second)
    {
        values[1].second = values[2].second;
    }
    if(values[3].second <= values[0].second || values[3].second >= values[5].second)
    {
        values[3].second = values[5].second;
    }
    if(values[4].second <= values[3].second || values[4].second >= values[5].second)
    {
        values[4].second = values[3].second;
    }

    for(i=m.begin();i != m.end();i++)
    {
        string str = i->first;
        for(int a=0;a<values.size();a++)
        {
            if(str.find(values[a].first)  != string::npos)
               i->second =  values[a].second ;
        }
    }
}
Diagnostics::Diagnostics()
{
    selection = 0;
    mainMenuIndex = -1;
    subMenuIndex = -1;
    subMenuName =   ADMINISTRATOR_LABEL_STRING;
    mainMenuName = UTILITY_LABEL_STRING;
    pair<string,double> temp;
    pair<string,double> temp1;
    pair<string,string> item;
    pair<pair<string,double>, string> btnpair;
    vector<pair<string,string>> tempmemory1;
    vector<pair<string,string>> tempmemory2;

    for(int i=0;i<NUMBER_OF_PROGRAMS;i++)
    {

        temp.first = BUTTONS[i];
        temp.second = -1;
        btnpair.first = temp;
        btnpair.second = PROGRAMS[i];
        buttons.push_back(btnpair);
    }
    //////////////////////////////////////////////
    for(int i=0;i<NUMBER_OF_STATUS_DISPLAYS;i++)
    {
        temp.first = STATUS_DISPLAYS[i];
        temp.second = -1;
        statusdisplays.push_back(temp);
    }
    ////////////////////////////////////////////////////
    for(int i=0;i<NUMBER_OF_CHANNELS;i++)
    {
        temp.first = CHANNELS[0] + to_string(i + 1) + "/Value";
        temp.second =-1;
        temp1.first = CHANNELS[1] + to_string(i + 1) + "/TextString";
        temp1.second = false;
        channels.push_back(pair<  pair<string,double>, pair<string,bool>  >(temp,temp1));
    }
    for(int i=0;i<MEM_LIST_LENGTH;i++)
    {
        item.first = MEMORY_ITEM_NAME[0] + to_string(i + 1) + "/TextString";
        item.second = "";

        tempmemory1.push_back(item);
        item.first = MEMORY_ITEM_NAME[1] + to_string(i + 1) + "/TextString";
        item.second = "";
        tempmemory2.push_back(item);
    }
    memory.first = tempmemory1;
    memory.second = tempmemory2;
    tempmemory1.clear();
    tempmemory2.clear();

    for(int j = 0; j < NUMBER_OF_OPTIONS1;j++)
    {
        pair<string,double> temp;
        temp.first = PRIMARY_SECONDARY_CHECK_BOX[j];
        temp.second = 0;
        opt.push_back(temp);
    }

}
Diagnostics::~Diagnostics()
{

    buttons.clear();
    statusdisplays.clear();
    channels.clear();
    memory.first.clear();
    memory.second.clear();

}
void Diagnostics::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
{

    if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
    {
        for(int i = 0;i< buttons.size();i++)
        {
            ptrDrawingArea->Viewport.GetResource(buttons[i].first.first.c_str(),&buttons[i].first.second);
            if(buttons[i].first.second == 1)
            {
               system(buttons[i].second.c_str());
                //system("gnome-terminal");
            }
        }
    }
}
void Diagnostics::ProcessInput(string action,string origin, GlgDrawingArea * drawingArea)
{

    if(drawingArea->parent->MainMenuIndex == this->mainMenuIndex && drawingArea->parent->SubMenuIndex == this->subMenuIndex)
    {
        string SvrDiagStr;
        int DiagStrID = 0,status = -1,statusD[5];
        int j =0;

           if(opt[0].second == 1)
           {
               j=1;
               opt[0].second =0;
               opt[1].second =1;
               drawingArea->Viewport.SetResource(opt[0].first.c_str(),opt[0].second);
               drawingArea->Viewport.SetResource(opt[1].first.c_str(),opt[1].second);
           }
           else  if(opt[1].second == 1)
           {
               j=0;
               opt[0].second =1;
               opt[1].second =0;
               drawingArea->Viewport.SetResource(opt[0].first.c_str(),opt[0].second);
               drawingArea->Viewport.SetResource(opt[1].first.c_str(),opt[1].second);
           }


             if(opt[0].second == 1)
                 j=0;
             else if(opt[1].second == 1)
                 j=1;
             MPCMS_ServerType ServerID;
                 if(j == 0)
                 {
                      ServerID = MST_PRIMARY;
                      drawingArea->Viewport.SetResource(opt[1].first.c_str(),0.0);
                 }
                 else if(j==1)
                 {
                     ServerID = MST_SECONDARY;
                     drawingArea->Viewport.SetResource(opt[0].first.c_str(),0.0);
                 }
                 for(int a=0; a <  statusdisplays.size();a++)
                 {
                    statusD[a] =-1;
                 }
                 bool pr = false;
                 statusD[0] = drawingArea->parent->pDataFeed->ReadSvrIsPrimary(ServerID,&pr);
                    if(statusD[0] != -1)
                    {
                        if(pr)
                        {
                            statusdisplays[0].second  = 1;
                             drawingArea->Viewport.SetResource(statusdisplays[0].first.c_str(),"TRUE");
                        }
                        else
                        {
                            statusdisplays[0].second  = 0;
                            drawingArea->Viewport.SetResource(statusdisplays[0].first.c_str(),"FALSE");
                        }
                    }

                  bool ac =false;
                  statusD[1] = drawingArea->parent->pDataFeed->ReadSvrIsActive(ServerID,&ac);
                  if(statusD[1] != -1)
                  {
                      if(ac)
                      {
                          statusdisplays[1].second  = 1;
                          drawingArea->Viewport.SetResource(statusdisplays[1].first.c_str(),"TRUE");
                      }
                      else
                      {
                          statusdisplays[1].second  = 0;
                         drawingArea->Viewport.SetResource(statusdisplays[1].first.c_str(),"FALSE");
                      }
                  }

                  bool hb =false;
                  statusD[2] = drawingArea->parent->pDataFeed->ReadSvrReceiveHeartbeat(ServerID,&hb);
                  if(statusD[2] != -1)
                  {
                        if(hb)
                        {
                            statusdisplays[2].second  = 1;
                             drawingArea->Viewport.SetResource(statusdisplays[2].first.c_str(),"TRUE");
                        }
                        else
                        {
                            statusdisplays[2].second  = 2;
                           drawingArea->Viewport.SetResource(statusdisplays[2].first.c_str(),"FALSE");
                        }
                    }

                  long pcTemp =-1;
                     statusD[3] = drawingArea->parent->pDataFeed->ReadSvrTemp(ServerID,&pcTemp);
                     if(statusD[3] != -1)
                     {

                             statusdisplays[3].second  = pcTemp;
                             drawingArea->Viewport.SetResource(statusdisplays[3].first.c_str(), statusdisplays[3].second);
                      }


                  long cycleTime =-1;
                     statusD[4] = drawingArea->parent->pDataFeed->ReadSvrCycleTime(ServerID,&cycleTime);
                     if(statusD[4] != -1)
                     {

                             statusdisplays[4].second  = cycleTime;
                             drawingArea->Viewport.SetResource(statusdisplays[4].first.c_str(), statusdisplays[4].second);
                     }


                 for(int i=0;i<memory.first.size();i++)
                 {
                    status = receiveFromDDS(ServerID, SvrDiagStr, i, drawingArea->parent->pDataFeed);
                    if(status == -1)
                    {
                             string serverid ="";
                             if(ServerID == 0)
                                 serverid  = "Primary";
                             else if(ServerID == 1)
                                  serverid  = "Secondary";

                             memory.first[i].second = "DataFeed::ReadSvrDiagnosticStr: ServerID " + serverid + " ERROR";
                    }
                    else
                    {
                        if(strlen(SvrDiagStr.c_str()) != 0)
                        {
                                memory.first[i].second = SvrDiagStr;
                        }
                        else
                        {
                             memory.first[i].second = string("");
                        }
                    }
                    drawingArea->Viewport.SetResource(memory.first[i].first.c_str(), memory.first[i].second.c_str());
                 }
                 for(int i = 0;i < channels.size();i++)
                 {
                     status = -1;
                     channels[i].first.second = -1;
                     status = drawingArea->parent->pDataFeed->ReadSvrSerialErrCount(ServerID, &channels[i].first.second, i);
                     drawingArea->Viewport.SetResource(channels[i].first.first.c_str(), (double)channels[i].first.second);

                     status = false;
                     channels[i].second.second = -1;
                     status = drawingArea->parent->pDataFeed->ReadSvrSerialTimeout(ServerID, &channels[i].second.second, i);
                     if(channels[i].second.second)
                     {
                        drawingArea->Viewport.SetResource(channels[i].second.first.c_str(), "TRUE");
                     }
                     else
                     {
                         drawingArea->Viewport.SetResource(channels[i].second.first.c_str(), "FALSE");
                     }

                 }
    }

}
int Diagnostics::receiveFromDDS(MPCMS_ServerType ServerID, string SvrDiagStr, int DiagStrID,CDataFeed * pDataFeed)
 {
    return  pDataFeed->ReadSvrDiagnosticStr(ServerID,SvrDiagStr,DiagStrID);
 }
void Diagnostics::printData()
{

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ChangeSerialConfiguration::ChangeSerialConfiguration()
 {

     mainMenuIndex = -1;
     subMenuIndex = -1;
     subMenuName =  CHANGESERIA_CONFIGURATION_LABEL_STRING;
     mainMenuName = UTILITY_LABEL_STRING;
     btnFinishInstate.first = BTN_FINISH_CHANGE_SERIAL_CONFIGURATION;
     btnFinishInstate.second = -1;
     btnCancelInstate.first = BTN_CANCEL_CHANGE_SERIAL_CONFIGURATION;
     btnCancelInstate.second = -1;
     pair<string,double> temp1;

     vector<pair<string,double>> portdata;
     for(int i=0;i < NUMBER_OF_PORTS;i++)
     {
         portdata.clear();
         for(int j=0;j<NUMBER_OF_SERIAL_CONFIG_DATA+1;j++)
         {

             if(j==0)
             {
                 temp1.first = SERIAL_CONFIG_PORTS[j];
                 temp1.second = i;
             }
             else if(j == 2 || j ==4 || j == 5)
             {
                 temp1.first = SERIAL_CONFIG_PORTS[j] + to_string(i) + "/Value";
                 temp1.second = 0;
             }
             else
             {
                 temp1.first = SERIAL_CONFIG_PORTS[j] + to_string(i) + "/SelectedIndex";
                 temp1.second = 0;
             }
             portdata.push_back(temp1);
         }
         ports.push_back(portdata);
     }
     statuslbl.first = STATUS_LABEL__CHANGE_SERIAL_CONFIGURATION;
     statuslbl.second = "";
     statuslblvisiibility.first = STATUS_LABEL__CHANGE_SERIAL_CONFIG_VISIBILITY;
     statuslblvisiibility.second = 0.0;
 }

 ChangeSerialConfiguration::~ChangeSerialConfiguration()
 {
     for(int i=0;i<ports.size();i++)
        ports[i].clear();
     ports.clear();
 }

 void ChangeSerialConfiguration::ProcessInput(string btn,GlgObjectC& viewport, GlgObjectC& message ,GlgDrawingArea *ptrDrawingArea,GlgSCADAViewer *ptr)
 {
     if(ptr->MainMenuIndex == this->mainMenuIndex && ptr->SubMenuIndex == this->subMenuIndex)
     {
         double visibility = -1;

         ptrDrawingArea->Viewport.GetResource(btnFinishInstate.first.c_str(),&btnFinishInstate.second);
         ptrDrawingArea->Viewport.GetResource(btnCancelInstate.first.c_str(),&btnCancelInstate.second);
         ptrDrawingArea->Viewport.GetResource("btnFinish/Visibility",&visibility);
         if(btnFinishInstate.second == 1 && visibility == 1.0)
         {
             /*for(int i = 0;i< NUMBER_OF_SERIAL_CONFIG_DATA;i++)
             {
                 ptrDrawingArea->Viewport.GetResource(configVariables[i].first.c_str(),&configVariables[i].second);
             }*/
             for(int i=0;i < NUMBER_OF_PORTS;i++)
             {
                 for(int j=1;j<NUMBER_OF_SERIAL_CONFIG_DATA+1;j++)
                 {
                     ptr->DrawingArea.Viewport.GetResource(ports[i][j].first.c_str(),&ports[i][j].second);
                 }

             }
             timer(0,  sendToDDS, ports,ptr);
         }
         else if(btnCancelInstate.second == 1)
         {
             ptr->SelectMainMenuItem((GlgLong)ptr->MainMenuIndex,0,true);
         }
         //printData();
         //for(int i = 0;i< NUM_OF_INPUT_VALUES;i++)
             //ptrDrawingArea->Viewport.SetResource(configVariables[i].first.c_str(),0.0);
     }
 }

 void ChangeSerialConfiguration::sendToDDS(  vector<vector<pair<string,double>>> ports,GlgSCADAViewer *ptr)
 {
     DEBUGF_VDT("STARTED ChangeSerialConfiguration::sendToDDS \n");
     string statuslbl = "In Process";
     ptr->DrawingArea.Viewport.SetResource("statuslbl/String",statuslbl.c_str());
     ptr->DrawingArea.Viewport.SetResource("statuslbl/Visibility",1.0);
     ptr->DrawingArea.Viewport.SetResource("btnFinish/Visibility",-0.3);
     int st = -1;



     for(int i=0;i<ports.size();i++)
     {
         for(int j=1;j< NUMBER_OF_SERIAL_CONFIG_DATA + 1;j++)
         {

             if(j == 1 || j== 3 || j==6)
             {
                 int ind = ports[i][j].second;
                 ports[i][j].second = (double )SERIAL_CONFIG_DATA_VALUES[j][ind];

             }
         }
        SERIALPORTCONFIGSTR scdata;
        scdata.portid = (long)ports[i][0].second;
        scdata.baud = (long)ports[i][1].second;
        scdata.bits = (long)ports[i][2].second;
        scdata.parity = (long)ports[i][3].second;
        scdata.stopbits = (long)ports[i][4].second;
        scdata.flowcontrol = (long)ports[i][5].second;
        //scdata.device= 13= ports[i][6].second;

        for(int j=0;j<ports[i].size();j++)
        {
              DEBUGF_VDT("[%s] = [%f]  ",ports[i][j].first.c_str(),ports[i][j].second);
        }
        DEBUGF_VDT("\n");

        st = ptr->pDataFeed->WriteSerialConfig(&scdata);
        if(st == -1)
        {
            statuslbl = "Server Error";
            ERRORF_VDT(" ChangeSerialConfiguration::sendToDDS Server ERROR Received status = [%d]\n",st);
        }
        else
        {
            statuslbl =  "Complete";
            DEBUGF_VDT(" ChangeSerialConfiguration::sendToDDS Server SUCCESS Received status = [%d]\n",st);
        }

     }
     ptr->DrawingArea.Viewport.SetResource("statuslbl/String",statuslbl.c_str());
     DEBUGF_VDT("FINISHED ChangeSerialConfiguration::sendToDDS \n");


 }
 void ChangeSerialConfiguration::ProcessInput(string action,string origin, GlgDrawingArea * drawingArea)
 {

     /*if(drawingArea->parent->MainMenuIndex == this->mainMenuIndex && drawingArea->parent->SubMenuIndex == this->subMenuIndex && origin.find("portid")  != string::npos)
     {

          receiveFromDDS(drawingArea->parent);
     }*/

 }
 void ChangeSerialConfiguration::timer(int d,  void (*f)(  vector<vector<pair<string,double>>> ports ,GlgSCADAViewer * ),  vector<vector<pair<string,double>>> ports,GlgSCADAViewer *ptr)
 {
      std::thread([d,f,ports,ptr](){
         std::this_thread::sleep_for(std::chrono::seconds(d));
         f(ports,ptr);
     }).detach();
 }

 void ChangeSerialConfiguration::receiveFromDDS(GlgSCADAViewer *ptr)
 {
     DEBUGF_VDT("STARTED ChangeSerialConfiguration::receiveFromDDS \n");
     SERIALPORTCONFIGSTR scdata;

     for(int i=0;i < NUMBER_OF_PORTS;i++)
     {

         for(int j=1;j<NUMBER_OF_SERIAL_CONFIG_DATA+1;j++)
         {
             if(j == 2)
             {
                  ports[i][j].second = 7.0;
             }
             else if(j == 4 || j == 5)
             {
                  ports[i][j].second = 1.0;
             }
             else
             {
                  ports[i][j].second = 0.0;
             }
             ptr->DrawingArea.Viewport.SetResource(ports[i][j].first.c_str(),ports[i][j].second);

         }
         int port = ports[i][0].second;
         int st =-1;

         st = ptr->pDataFeed->ReadSerialConfig(port,&scdata );
         if(st == -1)
         {
               ERRORF_VDT(" ChangeSerialConfiguration::receiveFromDDS Server ERROR Received status = [%d]\n",st);
         }
         else
         {

             ports[i][1].second = scdata.baud;
             ports[i][2].second= scdata.bits;
             ports[i][3].second = scdata.parity;
             ports[i][4].second= scdata.stopbits;
             ports[i][5].second = scdata.flowcontrol;
             ports[i][6].second = 13;
            for(int j=1;j< NUMBER_OF_SERIAL_CONFIG_DATA + 1;j++)
            {

                if(j == 1 || j== 3 || j==6)
                {
                    for(int k = 0;k<17;k++)
                    {
                        string a1= to_string((int)ports[i][j].second);
                        string a2=SERIAL_CONFIG_DATA_COUNT[j][k];
                        if(to_string((int)ports[i][j].second) == SERIAL_CONFIG_DATA_COUNT[j][k])
                        {
                            ports[i][j].second = k;
                            break;
                        }
                    }
                }
                ptr->DrawingArea.Viewport.SetResource(ports[i][j].first.c_str(),ports[i][j].second);
            }
            DEBUGF_VDT(" ChangeSerialConfiguration::receiveFromDDS Server SUCCESS Received status = [%d]\n",st);

         }
     }

     DEBUGF_VDT("FINISHED hangeSerialConfiguration::receiveFromDDS \n");

 }
