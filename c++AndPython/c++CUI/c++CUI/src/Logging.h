
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from Logging.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef Logging_113521525_h
#define Logging_113521525_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif


#define DigAlarmModLog_LAST_MEMBER_ID 5
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *DigAlarmModLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct DigAlarmModLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class DigAlarmModLogTypeSupport;
    class DigAlarmModLogDataWriter;
    class DigAlarmModLogDataReader;
#endif

#endif

            
    
class DigAlarmModLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct DigAlarmModLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef DigAlarmModLogTypeSupport TypeSupport;
    typedef DigAlarmModLogDataWriter DataWriter;
    typedef DigAlarmModLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    char*  pointID; /* maximum length = (255) */

    char*  longName; /* maximum length = (255) */

    DDS_Long  time_delay;

    char*  operatorName; /* maximum length = (255) */

    char*  comment; /* maximum length = (255) */

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* DigAlarmModLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(DigAlarmModLogSeq, DigAlarmModLog);
        
NDDSUSERDllExport
RTIBool DigAlarmModLog_initialize(
        DigAlarmModLog* self);
        
NDDSUSERDllExport
RTIBool DigAlarmModLog_initialize_ex(
        DigAlarmModLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool DigAlarmModLog_initialize_w_params(
        DigAlarmModLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void DigAlarmModLog_finalize(
        DigAlarmModLog* self);
                        
NDDSUSERDllExport
void DigAlarmModLog_finalize_ex(
        DigAlarmModLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void DigAlarmModLog_finalize_w_params(
        DigAlarmModLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void DigAlarmModLog_finalize_optional_members(
        DigAlarmModLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool DigAlarmModLog_copy(
        DigAlarmModLog* dst,
        const DigAlarmModLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define AlogAlarmModLog_LAST_MEMBER_ID 18
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *AlogAlarmModLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct AlogAlarmModLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class AlogAlarmModLogTypeSupport;
    class AlogAlarmModLogDataWriter;
    class AlogAlarmModLogDataReader;
#endif

#endif

            
    
class AlogAlarmModLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct AlogAlarmModLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef AlogAlarmModLogTypeSupport TypeSupport;
    typedef AlogAlarmModLogDataWriter DataWriter;
    typedef AlogAlarmModLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    char*  pointID; /* maximum length = (255) */

    char*  longName; /* maximum length = (255) */

    DDS_Float  rangeLow;

    DDS_Float  rangeHigh;

    DDS_Float  setPtHighHigh;

    DDS_Float  setPtHigh;

    DDS_Float  setPtLow;

    DDS_Float  setPtLowLow;

    DDS_Float  resetPtHighHigh;

    DDS_Float  resetPtHigh;

    DDS_Float  resetPtLow;

    DDS_Float  resetPtLowLow;

    DDS_Float  timeDelayHighHigh;

    DDS_Float  timeDelayHigh;

    DDS_Float  timeDelayLow;

    DDS_Float  timeDelayLowLow;

    char*  operatorName; /* maximum length = (255) */

    char*  comment; /* maximum length = (255) */

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* AlogAlarmModLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(AlogAlarmModLogSeq, AlogAlarmModLog);
        
NDDSUSERDllExport
RTIBool AlogAlarmModLog_initialize(
        AlogAlarmModLog* self);
        
NDDSUSERDllExport
RTIBool AlogAlarmModLog_initialize_ex(
        AlogAlarmModLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool AlogAlarmModLog_initialize_w_params(
        AlogAlarmModLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void AlogAlarmModLog_finalize(
        AlogAlarmModLog* self);
                        
NDDSUSERDllExport
void AlogAlarmModLog_finalize_ex(
        AlogAlarmModLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void AlogAlarmModLog_finalize_w_params(
        AlogAlarmModLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void AlogAlarmModLog_finalize_optional_members(
        AlogAlarmModLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool AlogAlarmModLog_copy(
        AlogAlarmModLog* dst,
        const AlogAlarmModLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define CommentLog_LAST_MEMBER_ID 3
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *CommentLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct CommentLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class CommentLogTypeSupport;
    class CommentLogDataWriter;
    class CommentLogDataReader;
#endif

#endif

            
    
class CommentLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct CommentLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef CommentLogTypeSupport TypeSupport;
    typedef CommentLogDataWriter DataWriter;
    typedef CommentLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    DDS_Long  commentType;

    char*  operatorName; /* maximum length = (255) */

    char*  commentText; /* maximum length = (255) */

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* CommentLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(CommentLogSeq, CommentLog);
        
NDDSUSERDllExport
RTIBool CommentLog_initialize(
        CommentLog* self);
        
NDDSUSERDllExport
RTIBool CommentLog_initialize_ex(
        CommentLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool CommentLog_initialize_w_params(
        CommentLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void CommentLog_finalize(
        CommentLog* self);
                        
NDDSUSERDllExport
void CommentLog_finalize_ex(
        CommentLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void CommentLog_finalize_w_params(
        CommentLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void CommentLog_finalize_optional_members(
        CommentLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool CommentLog_copy(
        CommentLog* dst,
        const CommentLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define MachineryPlantStatusLog_LAST_MEMBER_ID 5
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *MachineryPlantStatusLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct MachineryPlantStatusLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class MachineryPlantStatusLogTypeSupport;
    class MachineryPlantStatusLogDataWriter;
    class MachineryPlantStatusLogDataReader;
#endif

#endif

            
    
class MachineryPlantStatusLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct MachineryPlantStatusLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef MachineryPlantStatusLogTypeSupport TypeSupport;
    typedef MachineryPlantStatusLogDataWriter DataWriter;
    typedef MachineryPlantStatusLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    DDS_Char  pointid[20];

    DDS_Long  nValue;

    DDS_Float  fValue;

    DDS_Long  digitalValue;

    DDS_Long  pointType;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* MachineryPlantStatusLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(MachineryPlantStatusLogSeq, MachineryPlantStatusLog);
        
NDDSUSERDllExport
RTIBool MachineryPlantStatusLog_initialize(
        MachineryPlantStatusLog* self);
        
NDDSUSERDllExport
RTIBool MachineryPlantStatusLog_initialize_ex(
        MachineryPlantStatusLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool MachineryPlantStatusLog_initialize_w_params(
        MachineryPlantStatusLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void MachineryPlantStatusLog_finalize(
        MachineryPlantStatusLog* self);
                        
NDDSUSERDllExport
void MachineryPlantStatusLog_finalize_ex(
        MachineryPlantStatusLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void MachineryPlantStatusLog_finalize_w_params(
        MachineryPlantStatusLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void MachineryPlantStatusLog_finalize_optional_members(
        MachineryPlantStatusLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool MachineryPlantStatusLog_copy(
        MachineryPlantStatusLog* dst,
        const MachineryPlantStatusLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define BellLog_LAST_MEMBER_ID 6
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *BellLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct BellLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class BellLogTypeSupport;
    class BellLogDataWriter;
    class BellLogDataReader;
#endif

#endif

            
    
class BellLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct BellLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef BellLogTypeSupport TypeSupport;
    typedef BellLogDataWriter DataWriter;
    typedef BellLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    DDS_Long  stnGenType;

    DDS_Float  stnGenThrottle;

    DDS_Long  stnInCtrlType;

    DDS_Float  stnInCtrlThrottle;

    DDS_Float  propShaftSpeed;

    DDS_Float  propellerPitch;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* BellLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(BellLogSeq, BellLog);
        
NDDSUSERDllExport
RTIBool BellLog_initialize(
        BellLog* self);
        
NDDSUSERDllExport
RTIBool BellLog_initialize_ex(
        BellLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool BellLog_initialize_w_params(
        BellLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void BellLog_finalize(
        BellLog* self);
                        
NDDSUSERDllExport
void BellLog_finalize_ex(
        BellLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void BellLog_finalize_w_params(
        BellLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void BellLog_finalize_optional_members(
        BellLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool BellLog_copy(
        BellLog* dst,
        const BellLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define AlarmChangeLog_LAST_MEMBER_ID 2
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *AlarmChangeLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct AlarmChangeLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class AlarmChangeLogTypeSupport;
    class AlarmChangeLogDataWriter;
    class AlarmChangeLogDataReader;
#endif

#endif

            
    
class AlarmChangeLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct AlarmChangeLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef AlarmChangeLogTypeSupport TypeSupport;
    typedef AlarmChangeLogDataWriter DataWriter;
    typedef AlarmChangeLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    char*  pointId; /* maximum length = (255) */

    DDS_Long  alarmChangeType;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* AlarmChangeLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(AlarmChangeLogSeq, AlarmChangeLog);
        
NDDSUSERDllExport
RTIBool AlarmChangeLog_initialize(
        AlarmChangeLog* self);
        
NDDSUSERDllExport
RTIBool AlarmChangeLog_initialize_ex(
        AlarmChangeLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool AlarmChangeLog_initialize_w_params(
        AlarmChangeLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void AlarmChangeLog_finalize(
        AlarmChangeLog* self);
                        
NDDSUSERDllExport
void AlarmChangeLog_finalize_ex(
        AlarmChangeLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void AlarmChangeLog_finalize_w_params(
        AlarmChangeLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void AlarmChangeLog_finalize_optional_members(
        AlarmChangeLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool AlarmChangeLog_copy(
        AlarmChangeLog* dst,
        const AlarmChangeLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define StatusChangeLog_LAST_MEMBER_ID 3
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *StatusChangeLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct StatusChangeLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class StatusChangeLogTypeSupport;
    class StatusChangeLogDataWriter;
    class StatusChangeLogDataReader;
#endif

#endif

            
    
class StatusChangeLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct StatusChangeLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef StatusChangeLogTypeSupport TypeSupport;
    typedef StatusChangeLogDataWriter DataWriter;
    typedef StatusChangeLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    char*  pointId; /* maximum length = (255) */

    DDS_Long  currentValue;

    DDS_Long  communicationStatus;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* StatusChangeLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(StatusChangeLogSeq, StatusChangeLog);
        
NDDSUSERDllExport
RTIBool StatusChangeLog_initialize(
        StatusChangeLog* self);
        
NDDSUSERDllExport
RTIBool StatusChangeLog_initialize_ex(
        StatusChangeLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool StatusChangeLog_initialize_w_params(
        StatusChangeLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void StatusChangeLog_finalize(
        StatusChangeLog* self);
                        
NDDSUSERDllExport
void StatusChangeLog_finalize_ex(
        StatusChangeLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void StatusChangeLog_finalize_w_params(
        StatusChangeLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void StatusChangeLog_finalize_optional_members(
        StatusChangeLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool StatusChangeLog_copy(
        StatusChangeLog* dst,
        const StatusChangeLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define AlogAlarmLog_LAST_MEMBER_ID 7
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *AlogAlarmLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct AlogAlarmLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class AlogAlarmLogTypeSupport;
    class AlogAlarmLogDataWriter;
    class AlogAlarmLogDataReader;
#endif

#endif

            
    
class AlogAlarmLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct AlogAlarmLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef AlogAlarmLogTypeSupport TypeSupport;
    typedef AlogAlarmLogDataWriter DataWriter;
    typedef AlogAlarmLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    DDS_Long  Alarm_Condition_Type;

    DDS_LongLong  Condition_Time;

    DDS_LongLong  Alarm_Time;

    char*  Point_ID; /* maximum length = (255) */

    DDS_Float  Value;

    DDS_Long  Setpoint_Violated;

    DDS_Float  Setpoint;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* AlogAlarmLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(AlogAlarmLogSeq, AlogAlarmLog);
        
NDDSUSERDllExport
RTIBool AlogAlarmLog_initialize(
        AlogAlarmLog* self);
        
NDDSUSERDllExport
RTIBool AlogAlarmLog_initialize_ex(
        AlogAlarmLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool AlogAlarmLog_initialize_w_params(
        AlogAlarmLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void AlogAlarmLog_finalize(
        AlogAlarmLog* self);
                        
NDDSUSERDllExport
void AlogAlarmLog_finalize_ex(
        AlogAlarmLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void AlogAlarmLog_finalize_w_params(
        AlogAlarmLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void AlogAlarmLog_finalize_optional_members(
        AlogAlarmLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool AlogAlarmLog_copy(
        AlogAlarmLog* dst,
        const AlogAlarmLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define DigAlarmLog_LAST_MEMBER_ID 5
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *DigAlarmLogTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct DigAlarmLogSeq;

#ifndef NDDS_STANDALONE_TYPE
    class DigAlarmLogTypeSupport;
    class DigAlarmLogDataWriter;
    class DigAlarmLogDataReader;
#endif

#endif

            
    
class DigAlarmLog                                        
{
public:            
#ifdef __cplusplus
    typedef struct DigAlarmLogSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef DigAlarmLogTypeSupport TypeSupport;
    typedef DigAlarmLogDataWriter DataWriter;
    typedef DigAlarmLogDataReader DataReader;
#endif

#endif
    
    DDS_LongLong  timestamp;

    DDS_Long  Alarm_Condition_Type;

    DDS_LongLong  Condition_Time;

    DDS_LongLong  Alarm_Time;

    char*  Point_ID; /* maximum length = (255) */

    DDS_Long  Status;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* DigAlarmLog_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(DigAlarmLogSeq, DigAlarmLog);
        
NDDSUSERDllExport
RTIBool DigAlarmLog_initialize(
        DigAlarmLog* self);
        
NDDSUSERDllExport
RTIBool DigAlarmLog_initialize_ex(
        DigAlarmLog* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool DigAlarmLog_initialize_w_params(
        DigAlarmLog* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void DigAlarmLog_finalize(
        DigAlarmLog* self);
                        
NDDSUSERDllExport
void DigAlarmLog_finalize_ex(
        DigAlarmLog* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void DigAlarmLog_finalize_w_params(
        DigAlarmLog* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void DigAlarmLog_finalize_optional_members(
        DigAlarmLog* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool DigAlarmLog_copy(
        DigAlarmLog* dst,
        const DigAlarmLog* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* Logging_113521525_h */
