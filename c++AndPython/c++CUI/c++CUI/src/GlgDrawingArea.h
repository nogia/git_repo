?_R0?AUIMAPIContainer@@@8 ??_R3IMAPIContainer@@8 ??_R2IMAPIContainer@@8 ??_R1A@?0A@EA@IMAPIProp@@8 ??_R0?AUIMAPIProp@@@8 ??_R3IMAPIProp@@8 ??_R2IMAPIProp@@8 ??_R4CMAPIFolder@@6B@ ??_R0?AVCMAPIFolder@@@8 ??_R3CMAPIFolder@@8 ??_R2CMAPIFolder@@8 ??_R1A@?0A@EA@CMAPIFolder@@8 __RTC_InitBase.rtc$IMZ __RTC_Shutdown.rtc$TMZ                                                                                                                                                                                                   ing_name );
   
   void ProcessObjectCommand( GlgObjectC& selected_obj, int button_index );
   void ProcessCommandWriteValue( GlgObjectC& selected_obj, 
                                  GlgObjectC& command_obj );
   void ProcessAlarmACK( GlgObjectC& selected_obj );
   void ProcessAlarmStateACK( GlgObjectC& selected_obj );  
   void ProcessOffPageAlarm( GlgObjectC& selected_obj );   
   void WriteTagData( CONST char * tag_source, double value );
   
   // Input callback
   virtual void Input( GlgObjectC& viewport, GlgObjectC& message );
   //GlgSCADAViewer * getParent();
   GlgDrawingArea& operator= ( const GlgObjectC& object );
   void error( GlgErrorType message_type, CONST char * message, bool app_exit );
   void errorS( GlgErrorType message_type, 
                CONST char * message1, CONST char * message2, bool app_exit );
};
