
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from WLB_RealTimeData.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef WLB_RealTimeDataSupport_727919327_h
#define WLB_RealTimeDataSupport_727919327_h

/* Uses */
#include "WLB_RealTimeData.h"



#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif


 /******************************************************************************

 Initial data structures based on legacy WLB database structure.



 Point IDs in original implementation were calculated dynamically by combination

 of DB CLASS and DB NUMBER fields, separated by hyphen (Ex: MPE1-100).





 11/21/2014

 ccarroll

 ******************************************************************************/

 /**********************************************************************

 **********************   REAL TIME DATA TOPICS   **********************

 ***********************************************************************/

 /**********************************************************************

 Common Types for multiple topics

 ***********************************************************************/

 /**********************************************************************

 Analog Points

 -- Analog Input

 -- Analog Output

 ***********************************************************************/
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(AnalogPointTypeSupport, AnalogPoint);

DDS_DATAWRITER_CPP(AnalogPointDataWriter, AnalogPoint);
DDS_DATAREADER_CPP(AnalogPointDataReader, AnalogPointSeq, AnalogPoint);


#else

DDS_TYPESUPPORT_C(AnalogPointTypeSupport, AnalogPoint);
DDS_DATAWRITER_C(AnalogPointDataWriter, AnalogPoint);
DDS_DATAREADER_C(AnalogPointDataReader, AnalogPointSeq, AnalogPoint);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


 /**********************************************************************

 Digital Input Points

 -- Status Input   (DI)

 -- Original Ada type Contact_States_Type has been maintained for

 --    consistency with server.  Also, original Ada subtypes used by

 --    Software generated points have been dropped

 -- Contact Alarm  (DI)

 ***********************************************************************/
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(StatusPointTypeSupport, StatusPoint);

DDS_DATAWRITER_CPP(StatusPointDataWriter, StatusPoint);
DDS_DATAREADER_CPP(StatusPointDataReader, StatusPointSeq, StatusPoint);


#else

DDS_TYPESUPPORT_C(StatusPointTypeSupport, StatusPoint);
DDS_DATAWRITER_C(StatusPointDataWriter, StatusPoint);
DDS_DATAREADER_C(StatusPointDataReader, StatusPointSeq, StatusPoint);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(ContactAlarmTypeSupport, ContactAlarm);

DDS_DATAWRITER_CPP(ContactAlarmDataWriter, ContactAlarm);
DDS_DATAREADER_CPP(ContactAlarmDataReader, ContactAlarmSeq, ContactAlarm);


#else

DDS_TYPESUPPORT_C(ContactAlarmTypeSupport, ContactAlarm);
DDS_DATAWRITER_C(ContactAlarmDataWriter, ContactAlarm);
DDS_DATAREADER_C(ContactAlarmDataReader, ContactAlarmSeq, ContactAlarm);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


 /**********************************************************************

 Digital Output Points

 -- Digital Output (DO)

 ***********************************************************************/
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(DigitalOutputValueTypeSupport, DigitalOutputValue);

DDS_DATAWRITER_CPP(DigitalOutputValueDataWriter, DigitalOutputValue);
DDS_DATAREADER_CPP(DigitalOutputValueDataReader, DigitalOutputValueSeq, DigitalOutputValue);


#else

DDS_TYPESUPPORT_C(DigitalOutputValueTypeSupport, DigitalOutputValue);
DDS_DATAWRITER_C(DigitalOutputValueDataWriter, DigitalOutputValue);
DDS_DATAREADER_C(DigitalOutputValueDataReader, DigitalOutputValueSeq, DigitalOutputValue);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


 /**********************************************************************

 **********************  OPERATOR COMMAND TOPICS  **********************

 ***********************************************************************/

 /**********************************************************************

 Analog Machinery Commands

 ***********************************************************************/
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(AnalogCommandRequestTypeSupport, AnalogCommandRequest);

DDS_DATAWRITER_CPP(AnalogCommandRequestDataWriter, AnalogCommandRequest);
DDS_DATAREADER_CPP(AnalogCommandRequestDataReader, AnalogCommandRequestSeq, AnalogCommandRequest);


#else

DDS_TYPESUPPORT_C(AnalogCommandRequestTypeSupport, AnalogCommandRequest);
DDS_DATAWRITER_C(AnalogCommandRequestDataWriter, AnalogCommandRequest);
DDS_DATAREADER_C(AnalogCommandRequestDataReader, AnalogCommandRequestSeq, AnalogCommandRequest);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(AnalogCommandReplyTypeSupport, AnalogCommandReply);

DDS_DATAWRITER_CPP(AnalogCommandReplyDataWriter, AnalogCommandReply);
DDS_DATAREADER_CPP(AnalogCommandReplyDataReader, AnalogCommandReplySeq, AnalogCommandReply);


#else

DDS_TYPESUPPORT_C(AnalogCommandReplyTypeSupport, AnalogCommandReply);
DDS_DATAWRITER_C(AnalogCommandReplyDataWriter, AnalogCommandReply);
DDS_DATAREADER_C(AnalogCommandReplyDataReader, AnalogCommandReplySeq, AnalogCommandReply);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


 /**********************************************************************

 Digital Machinery Commands

 ***********************************************************************/
        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(DigitalCommandRequestTypeSupport, DigitalCommandRequest);

DDS_DATAWRITER_CPP(DigitalCommandRequestDataWriter, DigitalCommandRequest);
DDS_DATAREADER_CPP(DigitalCommandRequestDataReader, DigitalCommandRequestSeq, DigitalCommandRequest);


#else

DDS_TYPESUPPORT_C(DigitalCommandRequestTypeSupport, DigitalCommandRequest);
DDS_DATAWRITER_C(DigitalCommandRequestDataWriter, DigitalCommandRequest);
DDS_DATAREADER_C(DigitalCommandRequestDataReader, DigitalCommandRequestSeq, DigitalCommandRequest);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(DigitalCommandReplyTypeSupport, DigitalCommandReply);

DDS_DATAWRITER_CPP(DigitalCommandReplyDataWriter, DigitalCommandReply);
DDS_DATAREADER_CPP(DigitalCommandReplyDataReader, DigitalCommandReplySeq, DigitalCommandReply);


#else

DDS_TYPESUPPORT_C(DigitalCommandReplyTypeSupport, DigitalCommandReply);
DDS_DATAWRITER_C(DigitalCommandReplyDataWriter, DigitalCommandReply);
DDS_DATAREADER_C(DigitalCommandReplyDataReader, DigitalCommandReplySeq, DigitalCommandReply);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


 /**********************************************************************

 Alarms

 -- Analog

 -- Contact Alarm (DI)

 -- Frame Failure Alarm (DI)

 -- RTU Failure Alarm (DI)

 -- TANOnet Command Disable Alarm (DI)

 ***********************************************************************/

 /**********************************************************************

 Software Generated Points

 -- Access DB Source field = SOFT

 -- Original Ada subtypes of Contact_States_Type have been dropped (for

 --    consistency with server).

 ***********************************************************************/

 /**********************************************************************

 **********************   CONFIGURATION TOPICS    **********************

 ***********************************************************************/

 /**********************************************************************

 General Point Configuration

 ***********************************************************************/


#endif  /* WLB_RealTimeDataSupport_727919327_h */
