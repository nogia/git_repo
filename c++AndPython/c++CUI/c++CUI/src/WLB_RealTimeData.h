
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from WLB_RealTimeData.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef WLB_RealTimeData_727919327_h
#define WLB_RealTimeData_727919327_h

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
 
typedef enum WLB_CLASS_TYPE
{
    WCT_A = 0,
    WCT_B
} WLB_CLASS_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* WLB_CLASS_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(WLB_CLASS_TYPESeq, WLB_CLASS_TYPE);
        
NDDSUSERDllExport
RTIBool WLB_CLASS_TYPE_initialize(
        WLB_CLASS_TYPE* self);
        
NDDSUSERDllExport
RTIBool WLB_CLASS_TYPE_initialize_ex(
        WLB_CLASS_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool WLB_CLASS_TYPE_initialize_w_params(
        WLB_CLASS_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void WLB_CLASS_TYPE_finalize(
        WLB_CLASS_TYPE* self);
                        
NDDSUSERDllExport
void WLB_CLASS_TYPE_finalize_ex(
        WLB_CLASS_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void WLB_CLASS_TYPE_finalize_w_params(
        WLB_CLASS_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void WLB_CLASS_TYPE_finalize_optional_members(
        WLB_CLASS_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool WLB_CLASS_TYPE_copy(
        WLB_CLASS_TYPE* dst,
        const WLB_CLASS_TYPE* src);


NDDSUSERDllExport
RTIBool WLB_CLASS_TYPE_getValues(WLB_CLASS_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ALARM_STATE_TYPE
{
    AST_CLEAR = 0,
    AST_IN_DELAY,
    AST_ACTIVE
} ALARM_STATE_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ALARM_STATE_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ALARM_STATE_TYPESeq, ALARM_STATE_TYPE);
        
NDDSUSERDllExport
RTIBool ALARM_STATE_TYPE_initialize(
        ALARM_STATE_TYPE* self);
        
NDDSUSERDllExport
RTIBool ALARM_STATE_TYPE_initialize_ex(
        ALARM_STATE_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ALARM_STATE_TYPE_initialize_w_params(
        ALARM_STATE_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ALARM_STATE_TYPE_finalize(
        ALARM_STATE_TYPE* self);
                        
NDDSUSERDllExport
void ALARM_STATE_TYPE_finalize_ex(
        ALARM_STATE_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ALARM_STATE_TYPE_finalize_w_params(
        ALARM_STATE_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ALARM_STATE_TYPE_finalize_optional_members(
        ALARM_STATE_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ALARM_STATE_TYPE_copy(
        ALARM_STATE_TYPE* dst,
        const ALARM_STATE_TYPE* src);


NDDSUSERDllExport
RTIBool ALARM_STATE_TYPE_getValues(ALARM_STATE_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ALARM_ACK_TYPE
{
    AAT_UNACKNOWLEDGED = 0,
    AAT_ACKNOWLEDGED
} ALARM_ACK_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ALARM_ACK_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ALARM_ACK_TYPESeq, ALARM_ACK_TYPE);
        
NDDSUSERDllExport
RTIBool ALARM_ACK_TYPE_initialize(
        ALARM_ACK_TYPE* self);
        
NDDSUSERDllExport
RTIBool ALARM_ACK_TYPE_initialize_ex(
        ALARM_ACK_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ALARM_ACK_TYPE_initialize_w_params(
        ALARM_ACK_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ALARM_ACK_TYPE_finalize(
        ALARM_ACK_TYPE* self);
                        
NDDSUSERDllExport
void ALARM_ACK_TYPE_finalize_ex(
        ALARM_ACK_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ALARM_ACK_TYPE_finalize_w_params(
        ALARM_ACK_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ALARM_ACK_TYPE_finalize_optional_members(
        ALARM_ACK_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ALARM_ACK_TYPE_copy(
        ALARM_ACK_TYPE* dst,
        const ALARM_ACK_TYPE* src);


NDDSUSERDllExport
RTIBool ALARM_ACK_TYPE_getValues(ALARM_ACK_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ALARM_INHIBIT_TYPE
{
    AIT_UNINHIBITED = 0,
    AIT_INHIBITED
} ALARM_INHIBIT_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ALARM_INHIBIT_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ALARM_INHIBIT_TYPESeq, ALARM_INHIBIT_TYPE);
        
NDDSUSERDllExport
RTIBool ALARM_INHIBIT_TYPE_initialize(
        ALARM_INHIBIT_TYPE* self);
        
NDDSUSERDllExport
RTIBool ALARM_INHIBIT_TYPE_initialize_ex(
        ALARM_INHIBIT_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ALARM_INHIBIT_TYPE_initialize_w_params(
        ALARM_INHIBIT_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ALARM_INHIBIT_TYPE_finalize(
        ALARM_INHIBIT_TYPE* self);
                        
NDDSUSERDllExport
void ALARM_INHIBIT_TYPE_finalize_ex(
        ALARM_INHIBIT_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ALARM_INHIBIT_TYPE_finalize_w_params(
        ALARM_INHIBIT_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ALARM_INHIBIT_TYPE_finalize_optional_members(
        ALARM_INHIBIT_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ALARM_INHIBIT_TYPE_copy(
        ALARM_INHIBIT_TYPE* dst,
        const ALARM_INHIBIT_TYPE* src);


NDDSUSERDllExport
RTIBool ALARM_INHIBIT_TYPE_getValues(ALARM_INHIBIT_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ALARM_LOCATION_TYPE
{
    ALT_ECCC = 0,
    ALT_MSCC,
    ALT_BOTH
} ALARM_LOCATION_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ALARM_LOCATION_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ALARM_LOCATION_TYPESeq, ALARM_LOCATION_TYPE);
        
NDDSUSERDllExport
RTIBool ALARM_LOCATION_TYPE_initialize(
        ALARM_LOCATION_TYPE* self);
        
NDDSUSERDllExport
RTIBool ALARM_LOCATION_TYPE_initialize_ex(
        ALARM_LOCATION_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ALARM_LOCATION_TYPE_initialize_w_params(
        ALARM_LOCATION_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ALARM_LOCATION_TYPE_finalize(
        ALARM_LOCATION_TYPE* self);
                        
NDDSUSERDllExport
void ALARM_LOCATION_TYPE_finalize_ex(
        ALARM_LOCATION_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ALARM_LOCATION_TYPE_finalize_w_params(
        ALARM_LOCATION_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ALARM_LOCATION_TYPE_finalize_optional_members(
        ALARM_LOCATION_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ALARM_LOCATION_TYPE_copy(
        ALARM_LOCATION_TYPE* dst,
        const ALARM_LOCATION_TYPE* src);


NDDSUSERDllExport
RTIBool ALARM_LOCATION_TYPE_getValues(ALARM_LOCATION_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ALARM_SUMMARY_GROUP_TYPE
{
    ASGT_NONE = 0,
    ASGT_THRUSTER_MALF,
    ASGT_BOW_THRUSTER_MALF,
    ASGT_STERN_THRUSTER_MALF
} ALARM_SUMMARY_GROUP_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ALARM_SUMMARY_GROUP_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ALARM_SUMMARY_GROUP_TYPESeq, ALARM_SUMMARY_GROUP_TYPE);
        
NDDSUSERDllExport
RTIBool ALARM_SUMMARY_GROUP_TYPE_initialize(
        ALARM_SUMMARY_GROUP_TYPE* self);
        
NDDSUSERDllExport
RTIBool ALARM_SUMMARY_GROUP_TYPE_initialize_ex(
        ALARM_SUMMARY_GROUP_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ALARM_SUMMARY_GROUP_TYPE_initialize_w_params(
        ALARM_SUMMARY_GROUP_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ALARM_SUMMARY_GROUP_TYPE_finalize(
        ALARM_SUMMARY_GROUP_TYPE* self);
                        
NDDSUSERDllExport
void ALARM_SUMMARY_GROUP_TYPE_finalize_ex(
        ALARM_SUMMARY_GROUP_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ALARM_SUMMARY_GROUP_TYPE_finalize_w_params(
        ALARM_SUMMARY_GROUP_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ALARM_SUMMARY_GROUP_TYPE_finalize_optional_members(
        ALARM_SUMMARY_GROUP_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ALARM_SUMMARY_GROUP_TYPE_copy(
        ALARM_SUMMARY_GROUP_TYPE* dst,
        const ALARM_SUMMARY_GROUP_TYPE* src);


NDDSUSERDllExport
RTIBool ALARM_SUMMARY_GROUP_TYPE_getValues(ALARM_SUMMARY_GROUP_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


 /**********************************************************************

 Analog Points

 -- Analog Input

 -- Analog Output

 ***********************************************************************/
 
typedef enum ANALOG_FAULT_TYPE
{
    AFT_NO_FAULT = 0,
    AFT_FAULT
} ANALOG_FAULT_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ANALOG_FAULT_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ANALOG_FAULT_TYPESeq, ANALOG_FAULT_TYPE);
        
NDDSUSERDllExport
RTIBool ANALOG_FAULT_TYPE_initialize(
        ANALOG_FAULT_TYPE* self);
        
NDDSUSERDllExport
RTIBool ANALOG_FAULT_TYPE_initialize_ex(
        ANALOG_FAULT_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ANALOG_FAULT_TYPE_initialize_w_params(
        ANALOG_FAULT_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ANALOG_FAULT_TYPE_finalize(
        ANALOG_FAULT_TYPE* self);
                        
NDDSUSERDllExport
void ANALOG_FAULT_TYPE_finalize_ex(
        ANALOG_FAULT_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ANALOG_FAULT_TYPE_finalize_w_params(
        ANALOG_FAULT_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ANALOG_FAULT_TYPE_finalize_optional_members(
        ANALOG_FAULT_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ANALOG_FAULT_TYPE_copy(
        ANALOG_FAULT_TYPE* dst,
        const ANALOG_FAULT_TYPE* src);


NDDSUSERDllExport
RTIBool ANALOG_FAULT_TYPE_getValues(ANALOG_FAULT_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ANALOG_ALARM_TYPE
{
    AAT_HIHI = 0,
    AAT_HI,
    AAT_LO,
    AAT_LOLO
} ANALOG_ALARM_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ANALOG_ALARM_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ANALOG_ALARM_TYPESeq, ANALOG_ALARM_TYPE);
        
NDDSUSERDllExport
RTIBool ANALOG_ALARM_TYPE_initialize(
        ANALOG_ALARM_TYPE* self);
        
NDDSUSERDllExport
RTIBool ANALOG_ALARM_TYPE_initialize_ex(
        ANALOG_ALARM_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ANALOG_ALARM_TYPE_initialize_w_params(
        ANALOG_ALARM_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ANALOG_ALARM_TYPE_finalize(
        ANALOG_ALARM_TYPE* self);
                        
NDDSUSERDllExport
void ANALOG_ALARM_TYPE_finalize_ex(
        ANALOG_ALARM_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ANALOG_ALARM_TYPE_finalize_w_params(
        ANALOG_ALARM_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ANALOG_ALARM_TYPE_finalize_optional_members(
        ANALOG_ALARM_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ANALOG_ALARM_TYPE_copy(
        ANALOG_ALARM_TYPE* dst,
        const ANALOG_ALARM_TYPE* src);


NDDSUSERDllExport
RTIBool ANALOG_ALARM_TYPE_getValues(ANALOG_ALARM_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum ANALOG_STATUS_TYPE
{
    AST_NORMAL = 0,
    AST_UNACK_ALARM,
    AST_ACK_ALARM,
    AST_INHIB_ALARM,
    AST_UNACK_FAULT,
    AST_ACK_FAULT,
    AST_RTU_FAIL
} ANALOG_STATUS_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ANALOG_STATUS_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ANALOG_STATUS_TYPESeq, ANALOG_STATUS_TYPE);
        
NDDSUSERDllExport
RTIBool ANALOG_STATUS_TYPE_initialize(
        ANALOG_STATUS_TYPE* self);
        
NDDSUSERDllExport
RTIBool ANALOG_STATUS_TYPE_initialize_ex(
        ANALOG_STATUS_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ANALOG_STATUS_TYPE_initialize_w_params(
        ANALOG_STATUS_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ANALOG_STATUS_TYPE_finalize(
        ANALOG_STATUS_TYPE* self);
                        
NDDSUSERDllExport
void ANALOG_STATUS_TYPE_finalize_ex(
        ANALOG_STATUS_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void ANALOG_STATUS_TYPE_finalize_w_params(
        ANALOG_STATUS_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ANALOG_STATUS_TYPE_finalize_optional_members(
        ANALOG_STATUS_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool ANALOG_STATUS_TYPE_copy(
        ANALOG_STATUS_TYPE* dst,
        const ANALOG_STATUS_TYPE* src);


NDDSUSERDllExport
RTIBool ANALOG_STATUS_TYPE_getValues(ANALOG_STATUS_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define AnalogPoint_LAST_MEMBER_ID 15
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *AnalogPointTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct AnalogPointSeq;

#ifndef NDDS_STANDALONE_TYPE
    class AnalogPointTypeSupport;
    class AnalogPointDataWriter;
    class AnalogPointDataReader;
#endif

#endif

            
    
class AnalogPoint                                        
{
public:            
#ifdef __cplusplus
    typedef struct AnalogPointSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef AnalogPointTypeSupport TypeSupport;
    typedef AnalogPointDataWriter DataWriter;
    typedef AnalogPointDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    WLB_CLASS_TYPE  Class;

    DDS_Long  Counts;

    DDS_Double  Value;

    DDS_Boolean  CommFailure;

    ANALOG_FAULT_TYPE  Fault;

    ALARM_STATE_TYPE  AlarmState;

    ANALOG_ALARM_TYPE  SetPointAlarmType;

    ALARM_INHIBIT_TYPE  AlarmInhibit;

    ALARM_ACK_TYPE  AlarmAck;

    ALARM_SUMMARY_GROUP_TYPE  AlarmSmryGroup1;

    ALARM_SUMMARY_GROUP_TYPE  AlarmSmryGroup2;

    DDS_UnsignedLongLong  AlarmTime;

    DDS_UnsignedLongLong  AlarmAckTime;

    DDS_UnsignedLongLong  AlarmAnnuncTime;

    DDS_UnsignedLongLong  AlarmClearTime;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* AnalogPoint_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(AnalogPointSeq, AnalogPoint);
        
NDDSUSERDllExport
RTIBool AnalogPoint_initialize(
        AnalogPoint* self);
        
NDDSUSERDllExport
RTIBool AnalogPoint_initialize_ex(
        AnalogPoint* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool AnalogPoint_initialize_w_params(
        AnalogPoint* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void AnalogPoint_finalize(
        AnalogPoint* self);
                        
NDDSUSERDllExport
void AnalogPoint_finalize_ex(
        AnalogPoint* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void AnalogPoint_finalize_w_params(
        AnalogPoint* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void AnalogPoint_finalize_optional_members(
        AnalogPoint* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool AnalogPoint_copy(
        AnalogPoint* dst,
        const AnalogPoint* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * ANALOG_REALTIME_TOPIC = "Analog Point Real Time Data";
 /**********************************************************************

 Digital Input Points

 -- Status Input   (DI)

 -- Original Ada type Contact_States_Type has been maintained for

 --    consistency with server.  Also, original Ada subtypes used by

 --    Software generated points have been dropped

 -- Contact Alarm  (DI)

 ***********************************************************************/
 
typedef enum STATUS_FAULT_TYPE
{
    SIFT_NO_FAULT = 0,
    SIFT_SC_FAULT,
    SIFT_USC_FAULT,
    SIFT_CF_FAULT
} STATUS_FAULT_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* STATUS_FAULT_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(STATUS_FAULT_TYPESeq, STATUS_FAULT_TYPE);
        
NDDSUSERDllExport
RTIBool STATUS_FAULT_TYPE_initialize(
        STATUS_FAULT_TYPE* self);
        
NDDSUSERDllExport
RTIBool STATUS_FAULT_TYPE_initialize_ex(
        STATUS_FAULT_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool STATUS_FAULT_TYPE_initialize_w_params(
        STATUS_FAULT_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void STATUS_FAULT_TYPE_finalize(
        STATUS_FAULT_TYPE* self);
                        
NDDSUSERDllExport
void STATUS_FAULT_TYPE_finalize_ex(
        STATUS_FAULT_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void STATUS_FAULT_TYPE_finalize_w_params(
        STATUS_FAULT_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void STATUS_FAULT_TYPE_finalize_optional_members(
        STATUS_FAULT_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool STATUS_FAULT_TYPE_copy(
        STATUS_FAULT_TYPE* dst,
        const STATUS_FAULT_TYPE* src);


NDDSUSERDllExport
RTIBool STATUS_FAULT_TYPE_getValues(STATUS_FAULT_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum DIGITAL_STATUS_TYPE
{
    DST_NORMAL = 0,
    DST_UNACK_ALARM,
    DST_ACK_ALARM,
    DST_INHIB_ALARM,
    DST_UNACK_FAULT,
    DST_ACK_FAULT,
    DST_RTU_FAIL
} DIGITAL_STATUS_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* DIGITAL_STATUS_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(DIGITAL_STATUS_TYPESeq, DIGITAL_STATUS_TYPE);
        
NDDSUSERDllExport
RTIBool DIGITAL_STATUS_TYPE_initialize(
        DIGITAL_STATUS_TYPE* self);
        
NDDSUSERDllExport
RTIBool DIGITAL_STATUS_TYPE_initialize_ex(
        DIGITAL_STATUS_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool DIGITAL_STATUS_TYPE_initialize_w_params(
        DIGITAL_STATUS_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void DIGITAL_STATUS_TYPE_finalize(
        DIGITAL_STATUS_TYPE* self);
                        
NDDSUSERDllExport
void DIGITAL_STATUS_TYPE_finalize_ex(
        DIGITAL_STATUS_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void DIGITAL_STATUS_TYPE_finalize_w_params(
        DIGITAL_STATUS_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void DIGITAL_STATUS_TYPE_finalize_optional_members(
        DIGITAL_STATUS_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool DIGITAL_STATUS_TYPE_copy(
        DIGITAL_STATUS_TYPE* dst,
        const DIGITAL_STATUS_TYPE* src);


NDDSUSERDllExport
RTIBool DIGITAL_STATUS_TYPE_getValues(DIGITAL_STATUS_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum CONTACT_STATES_TYPE
{
    CST_NULL_STATE = 0,
    CST_ACKNOWLEDGE,
    CST_ACTIVE,
    CST_AHD_D_SLOW,
    CST_AHD_FULL,
    CST_AHD_HALF,
    CST_AHD_SLOW,
    CST_AHEAD,
    CST_ALARM,
    CST_ALIGNED,
    CST_ASTERN,
    CST_AST_D_SLOW,
    CST_AST_FULL,
    CST_AST_HALF,
    CST_AST_SLOW,
    CST_ATTENDED,
    CST_AUTO,
    CST_AUTO_RUN,
    CST_AUTO_STOP,
    CST_AVAILABLE,
    CST_BLG_AMR_2,
    CST_BLG_PMR,
    CST_BRDG_CTRL,
    CST_CLOSED,
    CST_CLEAR_SC,
    CST_CLEAR_USC,
    CST_CLEAR_CF,
    CST_CLEAR_FLT,
    CST_DISENGAGE,
    CST_DOWN,
    CST_DPS_CTRL,
    CST_ENGAGE,
    CST_ENGAGED,
    CST_EOS,
    CST_ERROR,
    CST_EXTEND,
    CST_E_STOPPED,
    CST_FAILED,
    CST_FAULT_SC,
    CST_FAULT_USC,
    CST_FAULT_CF,
    CST_FAULT_ANLG,
    CST_FOLLOW_UP,
    CST_HIGH,
    CST_IN_TRANSIT,
    CST_INACTIVE,
    CST_INSTALLED,
    CST_LOW,
    CST_MANEUVER,
    CST_MANUAL,
    CST_MNL_RUN,
    CST_MNL_STOP,
    CST_NO,
    CST_NO_THRUST,
    CST_NON_FLW_UP,
    CST_NORMAL,
    CST_NOT_ENGAGD,
    CST_NOT_E_STOP,
    CST_NOT_INST,
    CST_NOT_ON_BAT,
    CST_NOT_PRESSD,
    CST_NOT_READY,
    CST_OFF,
    CST_OFFLINE,
    CST_ON,
    CST_ON_BATTERY,
    CST_ONLINE,
    CST_OPEN,
    CST_OTHER,
    CST_PORT,
    CST_PORT_THRST,
    CST_POSN_1,
    CST_POSN_2,
    CST_POSN_3,
    CST_PRESSED,
    CST_PRI_STBY,
    CST_PRL_ENBL,
    CST_PRL_DSBL,
    CST_PROGRAMMED,
    CST_READY,
    CST_REMOTE,
    CST_REPORT,
    CST_RETRACT,
    CST_ROUGH,
    CST_RUN,
    CST_RUNNING,
    CST_RUN_STBY,
    CST_SATISFAC,
    CST_SEC_STBY,
    CST_SELECTED,
    CST_SPEED,
    CST_SS_AIR,
    CST_STANDBY,
    CST_START,
    CST_START_AIR,
    CST_STARTING,
    CST_STBD,
    CST_STBD_THRST,
    CST_STOP,
    CST_STOPPING,
    CST_STOPPED,
    CST_STOP_STBY,
    CST_SW_COOLING,
    CST_TEST,
    CST_TRANSIT,
    CST_TRIPPED,
    CST_UNALIGNED,
    CST_UNATTENDED,
    CST_UNAVAIL,
    CST_UP_LOCKED,
    CST_VOLTAGE,
    CST_WHEELHOUSE,
    CST_WRONG_POS,
    CST_YES,
    CST_LOCAL,
    CST_EMRG_MNL,
    CST_PRG_CNTRL,
    CST_ICE_BRK,
    CST_NO_ICE_BRK,
    CST_ECCCS,
    CST_MSCCS,
    CST_PSCS,
    CST_SSCS,
    CST_DPS,
    CST_ECCC_T_O,
    CST_E_T_O_DPS,
    CST_MSCC_REQ,
    CST_ECCC_OFRD,
    CST_MSCC_OFRD,
    CST_M_T_O_P,
    CST_M_T_O_S,
    CST_M_T_O_DPS,
    CST_PSCS_OFRD,
    CST_SSCS_OFRD,
    CST_DPS_REQ,
    CST_DPS_DROP
} CONTACT_STATES_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* CONTACT_STATES_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(CONTACT_STATES_TYPESeq, CONTACT_STATES_TYPE);
        
NDDSUSERDllExport
RTIBool CONTACT_STATES_TYPE_initialize(
        CONTACT_STATES_TYPE* self);
        
NDDSUSERDllExport
RTIBool CONTACT_STATES_TYPE_initialize_ex(
        CONTACT_STATES_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool CONTACT_STATES_TYPE_initialize_w_params(
        CONTACT_STATES_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void CONTACT_STATES_TYPE_finalize(
        CONTACT_STATES_TYPE* self);
                        
NDDSUSERDllExport
void CONTACT_STATES_TYPE_finalize_ex(
        CONTACT_STATES_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void CONTACT_STATES_TYPE_finalize_w_params(
        CONTACT_STATES_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void CONTACT_STATES_TYPE_finalize_optional_members(
        CONTACT_STATES_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool CONTACT_STATES_TYPE_copy(
        CONTACT_STATES_TYPE* dst,
        const CONTACT_STATES_TYPE* src);


NDDSUSERDllExport
RTIBool CONTACT_STATES_TYPE_getValues(CONTACT_STATES_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define StatusPoint_LAST_MEMBER_ID 13
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *StatusPointTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct StatusPointSeq;

#ifndef NDDS_STANDALONE_TYPE
    class StatusPointTypeSupport;
    class StatusPointDataWriter;
    class StatusPointDataReader;
#endif

#endif

            
    
class StatusPoint                                        
{
public:            
#ifdef __cplusplus
    typedef struct StatusPointSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef StatusPointTypeSupport TypeSupport;
    typedef StatusPointDataWriter DataWriter;
    typedef StatusPointDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    WLB_CLASS_TYPE  Class;

    DDS_Long  Value;

    DDS_Boolean  CommFailure;

    STATUS_FAULT_TYPE  Fault;

    ALARM_STATE_TYPE  AlarmState;

    ALARM_INHIBIT_TYPE  AlarmInhibit;

    ALARM_ACK_TYPE  AlarmAck;

    ALARM_SUMMARY_GROUP_TYPE  AlarmSmryGroup1;

    ALARM_SUMMARY_GROUP_TYPE  AlarmSmryGroup2;

    DDS_UnsignedLongLong  AlarmTime;

    DDS_UnsignedLongLong  AlarmAckTime;

    DDS_UnsignedLongLong  AlarmAnnuncTime;

    DDS_UnsignedLongLong  AlarmClearTime;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* StatusPoint_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(StatusPointSeq, StatusPoint);
        
NDDSUSERDllExport
RTIBool StatusPoint_initialize(
        StatusPoint* self);
        
NDDSUSERDllExport
RTIBool StatusPoint_initialize_ex(
        StatusPoint* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool StatusPoint_initialize_w_params(
        StatusPoint* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void StatusPoint_finalize(
        StatusPoint* self);
                        
NDDSUSERDllExport
void StatusPoint_finalize_ex(
        StatusPoint* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void StatusPoint_finalize_w_params(
        StatusPoint* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void StatusPoint_finalize_optional_members(
        StatusPoint* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool StatusPoint_copy(
        StatusPoint* dst,
        const StatusPoint* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * STATUS_REALTIME_TOPIC = "Status Point Real Time Data"; 
typedef enum CONTACT_ALARM_TYPE
{
    CAT_CLEAR = 0,
    CAT_ALARM
} CONTACT_ALARM_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* CONTACT_ALARM_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(CONTACT_ALARM_TYPESeq, CONTACT_ALARM_TYPE);
        
NDDSUSERDllExport
RTIBool CONTACT_ALARM_TYPE_initialize(
        CONTACT_ALARM_TYPE* self);
        
NDDSUSERDllExport
RTIBool CONTACT_ALARM_TYPE_initialize_ex(
        CONTACT_ALARM_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool CONTACT_ALARM_TYPE_initialize_w_params(
        CONTACT_ALARM_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void CONTACT_ALARM_TYPE_finalize(
        CONTACT_ALARM_TYPE* self);
                        
NDDSUSERDllExport
void CONTACT_ALARM_TYPE_finalize_ex(
        CONTACT_ALARM_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void CONTACT_ALARM_TYPE_finalize_w_params(
        CONTACT_ALARM_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void CONTACT_ALARM_TYPE_finalize_optional_members(
        CONTACT_ALARM_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool CONTACT_ALARM_TYPE_copy(
        CONTACT_ALARM_TYPE* dst,
        const CONTACT_ALARM_TYPE* src);


NDDSUSERDllExport
RTIBool CONTACT_ALARM_TYPE_getValues(CONTACT_ALARM_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

 
typedef enum CONTACT_ALARM_FAULT_TYPE
{
    CAFT_NO_FAULT = 0,
    CAFT_SC_FAULT
} CONTACT_ALARM_FAULT_TYPE;
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* CONTACT_ALARM_FAULT_TYPE_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(CONTACT_ALARM_FAULT_TYPESeq, CONTACT_ALARM_FAULT_TYPE);
        
NDDSUSERDllExport
RTIBool CONTACT_ALARM_FAULT_TYPE_initialize(
        CONTACT_ALARM_FAULT_TYPE* self);
        
NDDSUSERDllExport
RTIBool CONTACT_ALARM_FAULT_TYPE_initialize_ex(
        CONTACT_ALARM_FAULT_TYPE* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool CONTACT_ALARM_FAULT_TYPE_initialize_w_params(
        CONTACT_ALARM_FAULT_TYPE* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void CONTACT_ALARM_FAULT_TYPE_finalize(
        CONTACT_ALARM_FAULT_TYPE* self);
                        
NDDSUSERDllExport
void CONTACT_ALARM_FAULT_TYPE_finalize_ex(
        CONTACT_ALARM_FAULT_TYPE* self,RTIBool deletePointers);
        
NDDSUSERDllExport
void CONTACT_ALARM_FAULT_TYPE_finalize_w_params(
        CONTACT_ALARM_FAULT_TYPE* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void CONTACT_ALARM_FAULT_TYPE_finalize_optional_members(
        CONTACT_ALARM_FAULT_TYPE* self, RTIBool deletePointers);
                
NDDSUSERDllExport
RTIBool CONTACT_ALARM_FAULT_TYPE_copy(
        CONTACT_ALARM_FAULT_TYPE* dst,
        const CONTACT_ALARM_FAULT_TYPE* src);


NDDSUSERDllExport
RTIBool CONTACT_ALARM_FAULT_TYPE_getValues(CONTACT_ALARM_FAULT_TYPESeq * values);
    

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define ContactAlarm_LAST_MEMBER_ID 13
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *ContactAlarmTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct ContactAlarmSeq;

#ifndef NDDS_STANDALONE_TYPE
    class ContactAlarmTypeSupport;
    class ContactAlarmDataWriter;
    class ContactAlarmDataReader;
#endif

#endif

            
    
class ContactAlarm                                        
{
public:            
#ifdef __cplusplus
    typedef struct ContactAlarmSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef ContactAlarmTypeSupport TypeSupport;
    typedef ContactAlarmDataWriter DataWriter;
    typedef ContactAlarmDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    WLB_CLASS_TYPE  Class;

    CONTACT_ALARM_TYPE  Value;

    DDS_Boolean  CommFailure;

    CONTACT_ALARM_FAULT_TYPE  Fault;

    ALARM_STATE_TYPE  AlarmState;

    ALARM_INHIBIT_TYPE  AlarmInhibit;

    ALARM_ACK_TYPE  AlarmAck;

    ALARM_SUMMARY_GROUP_TYPE  AlarmSmryGroup1;

    ALARM_SUMMARY_GROUP_TYPE  AlarmSmryGroup2;

    DDS_UnsignedLongLong  AlarmTime;

    DDS_UnsignedLongLong  AlarmAckTime;

    DDS_UnsignedLongLong  AlarmAnnuncTime;

    DDS_UnsignedLongLong  AlarmClearTime;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* ContactAlarm_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(ContactAlarmSeq, ContactAlarm);
        
NDDSUSERDllExport
RTIBool ContactAlarm_initialize(
        ContactAlarm* self);
        
NDDSUSERDllExport
RTIBool ContactAlarm_initialize_ex(
        ContactAlarm* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool ContactAlarm_initialize_w_params(
        ContactAlarm* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void ContactAlarm_finalize(
        ContactAlarm* self);
                        
NDDSUSERDllExport
void ContactAlarm_finalize_ex(
        ContactAlarm* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void ContactAlarm_finalize_w_params(
        ContactAlarm* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void ContactAlarm_finalize_optional_members(
        ContactAlarm* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool ContactAlarm_copy(
        ContactAlarm* dst,
        const ContactAlarm* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * DI_ALARMS_TOPIC = "Contact Alarms Real Time Data";
 /**********************************************************************

 Digital Output Points

 -- Digital Output (DO)

 ***********************************************************************/

#define DigitalOutputValue_LAST_MEMBER_ID 2
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *DigitalOutputValueTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct DigitalOutputValueSeq;

#ifndef NDDS_STANDALONE_TYPE
    class DigitalOutputValueTypeSupport;
    class DigitalOutputValueDataWriter;
    class DigitalOutputValueDataReader;
#endif

#endif

            
    
class DigitalOutputValue                                        
{
public:            
#ifdef __cplusplus
    typedef struct DigitalOutputValueSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef DigitalOutputValueTypeSupport TypeSupport;
    typedef DigitalOutputValueDataWriter DataWriter;
    typedef DigitalOutputValueDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    WLB_CLASS_TYPE  Class;

    DDS_Boolean  Value;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* DigitalOutputValue_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(DigitalOutputValueSeq, DigitalOutputValue);
        
NDDSUSERDllExport
RTIBool DigitalOutputValue_initialize(
        DigitalOutputValue* self);
        
NDDSUSERDllExport
RTIBool DigitalOutputValue_initialize_ex(
        DigitalOutputValue* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool DigitalOutputValue_initialize_w_params(
        DigitalOutputValue* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void DigitalOutputValue_finalize(
        DigitalOutputValue* self);
                        
NDDSUSERDllExport
void DigitalOutputValue_finalize_ex(
        DigitalOutputValue* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void DigitalOutputValue_finalize_w_params(
        DigitalOutputValue* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void DigitalOutputValue_finalize_optional_members(
        DigitalOutputValue* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool DigitalOutputValue_copy(
        DigitalOutputValue* dst,
        const DigitalOutputValue* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * DO_REALTIME_TOPIC = "Digital Output Real Time Data";
 /**********************************************************************

 **********************  OPERATOR COMMAND TOPICS  **********************

 ***********************************************************************/

 /**********************************************************************

 Analog Machinery Commands

 ***********************************************************************/

#define AnalogCommandRequest_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *AnalogCommandRequestTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct AnalogCommandRequestSeq;

#ifndef NDDS_STANDALONE_TYPE
    class AnalogCommandRequestTypeSupport;
    class AnalogCommandRequestDataWriter;
    class AnalogCommandRequestDataReader;
#endif

#endif

            
    
class AnalogCommandRequest                                        
{
public:            
#ifdef __cplusplus
    typedef struct AnalogCommandRequestSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef AnalogCommandRequestTypeSupport TypeSupport;
    typedef AnalogCommandRequestDataWriter DataWriter;
    typedef AnalogCommandRequestDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    DDS_Float  CommandRequest;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* AnalogCommandRequest_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(AnalogCommandRequestSeq, AnalogCommandRequest);
        
NDDSUSERDllExport
RTIBool AnalogCommandRequest_initialize(
        AnalogCommandRequest* self);
        
NDDSUSERDllExport
RTIBool AnalogCommandRequest_initialize_ex(
        AnalogCommandRequest* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool AnalogCommandRequest_initialize_w_params(
        AnalogCommandRequest* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void AnalogCommandRequest_finalize(
        AnalogCommandRequest* self);
                        
NDDSUSERDllExport
void AnalogCommandRequest_finalize_ex(
        AnalogCommandRequest* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void AnalogCommandRequest_finalize_w_params(
        AnalogCommandRequest* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void AnalogCommandRequest_finalize_optional_members(
        AnalogCommandRequest* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool AnalogCommandRequest_copy(
        AnalogCommandRequest* dst,
        const AnalogCommandRequest* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * AO_CMD_REQ_TOPIC = "Analog Machinery Command Request";
#define AnalogCommandReply_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *AnalogCommandReplyTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct AnalogCommandReplySeq;

#ifndef NDDS_STANDALONE_TYPE
    class AnalogCommandReplyTypeSupport;
    class AnalogCommandReplyDataWriter;
    class AnalogCommandReplyDataReader;
#endif

#endif

            
    
class AnalogCommandReply                                        
{
public:            
#ifdef __cplusplus
    typedef struct AnalogCommandReplySeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef AnalogCommandReplyTypeSupport TypeSupport;
    typedef AnalogCommandReplyDataWriter DataWriter;
    typedef AnalogCommandReplyDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    DDS_Float  CommandedValue;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* AnalogCommandReply_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(AnalogCommandReplySeq, AnalogCommandReply);
        
NDDSUSERDllExport
RTIBool AnalogCommandReply_initialize(
        AnalogCommandReply* self);
        
NDDSUSERDllExport
RTIBool AnalogCommandReply_initialize_ex(
        AnalogCommandReply* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool AnalogCommandReply_initialize_w_params(
        AnalogCommandReply* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void AnalogCommandReply_finalize(
        AnalogCommandReply* self);
                        
NDDSUSERDllExport
void AnalogCommandReply_finalize_ex(
        AnalogCommandReply* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void AnalogCommandReply_finalize_w_params(
        AnalogCommandReply* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void AnalogCommandReply_finalize_optional_members(
        AnalogCommandReply* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool AnalogCommandReply_copy(
        AnalogCommandReply* dst,
        const AnalogCommandReply* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * AO_CMD_REPLY_TOPIC = "Analog Machinery Command Reply";
 /**********************************************************************

 Digital Machinery Commands

 ***********************************************************************/

#define DigitalCommandRequest_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *DigitalCommandRequestTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct DigitalCommandRequestSeq;

#ifndef NDDS_STANDALONE_TYPE
    class DigitalCommandRequestTypeSupport;
    class DigitalCommandRequestDataWriter;
    class DigitalCommandRequestDataReader;
#endif

#endif

            
    
class DigitalCommandRequest                                        
{
public:            
#ifdef __cplusplus
    typedef struct DigitalCommandRequestSeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef DigitalCommandRequestTypeSupport TypeSupport;
    typedef DigitalCommandRequestDataWriter DataWriter;
    typedef DigitalCommandRequestDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    DDS_Boolean  CommandRequest;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* DigitalCommandRequest_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(DigitalCommandRequestSeq, DigitalCommandRequest);
        
NDDSUSERDllExport
RTIBool DigitalCommandRequest_initialize(
        DigitalCommandRequest* self);
        
NDDSUSERDllExport
RTIBool DigitalCommandRequest_initialize_ex(
        DigitalCommandRequest* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool DigitalCommandRequest_initialize_w_params(
        DigitalCommandRequest* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void DigitalCommandRequest_finalize(
        DigitalCommandRequest* self);
                        
NDDSUSERDllExport
void DigitalCommandRequest_finalize_ex(
        DigitalCommandRequest* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void DigitalCommandRequest_finalize_w_params(
        DigitalCommandRequest* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void DigitalCommandRequest_finalize_optional_members(
        DigitalCommandRequest* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool DigitalCommandRequest_copy(
        DigitalCommandRequest* dst,
        const DigitalCommandRequest* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * DO_CMD_REQ_TOPIC = "Digital Machinery Command Request";
#define DigitalCommandReply_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *DigitalCommandReplyTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct DigitalCommandReplySeq;

#ifndef NDDS_STANDALONE_TYPE
    class DigitalCommandReplyTypeSupport;
    class DigitalCommandReplyDataWriter;
    class DigitalCommandReplyDataReader;
#endif

#endif

            
    
class DigitalCommandReply                                        
{
public:            
#ifdef __cplusplus
    typedef struct DigitalCommandReplySeq Seq;

#ifndef NDDS_STANDALONE_TYPE
    typedef DigitalCommandReplyTypeSupport TypeSupport;
    typedef DigitalCommandReplyDataWriter DataWriter;
    typedef DigitalCommandReplyDataReader DataReader;
#endif

#endif
    
    char*  PointID; /* maximum length = (255) */

    DDS_Boolean  CommandedValue;

            
};                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* DigitalCommandReply_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(DigitalCommandReplySeq, DigitalCommandReply);
        
NDDSUSERDllExport
RTIBool DigitalCommandReply_initialize(
        DigitalCommandReply* self);
        
NDDSUSERDllExport
RTIBool DigitalCommandReply_initialize_ex(
        DigitalCommandReply* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool DigitalCommandReply_initialize_w_params(
        DigitalCommandReply* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void DigitalCommandReply_finalize(
        DigitalCommandReply* self);
                        
NDDSUSERDllExport
void DigitalCommandReply_finalize_ex(
        DigitalCommandReply* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void DigitalCommandReply_finalize_w_params(
        DigitalCommandReply* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void DigitalCommandReply_finalize_optional_members(
        DigitalCommandReply* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool DigitalCommandReply_copy(
        DigitalCommandReply* dst,
        const DigitalCommandReply* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

             
static const char * DO_CMD_REPLY_TOPIC = "Digital Machinery Command Reply";
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


#endif /* WLB_RealTimeData_727919327_h */
