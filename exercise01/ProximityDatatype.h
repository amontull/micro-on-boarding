/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ProximityDatatype.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef ProximityDatatype_1543506597_h
#define ProximityDatatype_1543506597_h

#ifndef rti_me_c_h
#include "rti_me_c.h"
#endif

#if DDS_XTYPES_IS_ENABLED
#include "dds_c/dds_c_typecode.h"
#include "xcdr/xcdr_dds_interpreter.h"
#endif

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    extern const char *ProximityTypeTYPENAME;

    typedef struct ProximityType {

        DDS_String   name ;
        DDS_Float   proximity ;

    } ProximityType ;
    #if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, start exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport DDS_TypeCode* ProximityType_get_typecode(void); /* Type code */
    NDDSUSERDllExport RTIXCdrTypePlugin *ProximityType_get_type_plugin_info(void);
    NDDSUSERDllExport RTIXCdrSampleAccessInfo *ProximityType_get_sample_access_info(void);
    #endif

    #define REDA_SEQUENCE_USER_API
    #define T ProximityType
    #define TSeq ProximityTypeSeq
    #define REDA_SEQUENCE_EXCLUDE_C_METHODS
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>
    #define REDA_SEQUENCE_USER_API
    #define T ProximityType
    #define TSeq ProximityTypeSeq
    #define REDA_SEQUENCE_EXCLUDE_STRUCT
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    NDDSUSERDllExport extern ProximityType*
    ProximityType_create(void);

    NDDSUSERDllExport extern void
    ProximityType_delete(ProximityType* sample);

    NDDSUSERDllExport
    RTIBool ProximityType_initialize(
        ProximityType* self);

    NDDSUSERDllExport
    RTIBool ProximityType_initialize_ex(
        ProximityType* self,
        RTIBool allocatePointers,
        RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ProximityType_initialize_w_params(
        ProximityType* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

    NDDSUSERDllExport
    RTIBool ProximityType_finalize(
        ProximityType* self);

    NDDSUSERDllExport
    RTIBool ProximityType_finalize_w_return(
        ProximityType* self);

    NDDSUSERDllExport
    void ProximityType_finalize_ex(
        ProximityType* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ProximityType_finalize_w_params(
        ProximityType* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ProximityType_finalize_optional_members(
        ProximityType* self, RTIBool deletePointers);

    NDDSUSERDllExport
    RTIBool ProximityType_copy(
        ProximityType* dst,
        const ProximityType* src);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols.
    */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    #if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    #ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ProximityDatatype */

