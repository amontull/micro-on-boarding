/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ProximityDatatype.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ProximityDatatype.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#if DDS_XTYPES_IS_ENABLED
#include "dds_c/dds_c_typecode.h"
#endif
#ifndef NDDS_STANDALONE_TYPE
#include "osapi/osapi_atomic.h"
#endif

/*** SOURCE_BEGIN ***/

ProximityType *
ProximityType_create(void)
{
    ProximityType* sample;
    OSAPI_Heap_allocate_struct(&sample, ProximityType);
    if (sample != NULL)
    {
        if (!ProximityType_initialize(sample))
        {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}
#ifndef RTI_CERT
#ifndef RTI_CERT
void
ProximityType_delete(ProximityType* sample)
{
    if (sample != NULL)
    {
        /* ProximityType_finalize() always
        returns RTI_TRUE when called with sample != NULL */
        ProximityType_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}
#endif
#endif

/* ========================================================================= */
const char *ProximityTypeTYPENAME = "ProximityType";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode * ProximityType_get_typecode(void)
{
    static RTI_ATOMIC(RTI_INT32) is_initialized = 0;

    static DDS_TypeCode ProximityType_g_tc_name_string = DDS_INITIALIZE_STRING_TYPECODE((16L));

    static DDS_TypeCode_Member ProximityType_g_tc_members[2]=
    {

        {
            (char *)"name",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_KEY_MEMBER , /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"proximity",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode ProximityType_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"ProximityType", /* Name */
            NULL, /* Ignored */ 
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            2, /* Number of members */
            ProximityType_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for ProximityType*/

    if (OSAPI_Atomic_load(&is_initialized, OSAPI_ATOMIC_MEMORY_ORDER_ACQUIRE))
    {
        return &ProximityType_g_tc;
    }

    ProximityType_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    ProximityType_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&ProximityType_g_tc_name_string;
    ProximityType_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

    /* Initialize the values for member annotations. */
    ProximityType_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
    ProximityType_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

    ProximityType_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
    ProximityType_g_tc_members[1]._annotations._defaultValue._u.float_value = 0.0f;
    ProximityType_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
    ProximityType_g_tc_members[1]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
    ProximityType_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
    ProximityType_g_tc_members[1]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;

    ProximityType_g_tc._data._sampleAccessInfo =
    ProximityType_get_sample_access_info();
    ProximityType_g_tc._data._typePlugin =
    ProximityType_get_type_plugin_info();

    OSAPI_Atomic_store(&is_initialized, 1, OSAPI_ATOMIC_MEMORY_ORDER_RELEASE);

    return &ProximityType_g_tc;
}

RTIXCdrSampleAccessInfo *ProximityType_get_sample_access_info(void)
{
    static RTI_ATOMIC(RTI_INT32) is_initialized = 0;

    static RTIXCdrMemberAccessInfo ProximityType_g_memberAccessInfos[2] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo ProximityType_g_sampleAccessInfo =
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (OSAPI_Atomic_load(&is_initialized, OSAPI_ATOMIC_MEMORY_ORDER_ACQUIRE))
    {
        return (RTIXCdrSampleAccessInfo*) &ProximityType_g_sampleAccessInfo;
    }

    ProximityType_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToUnsignedLongLong(&((ProximityType *)NULL)->name);

    ProximityType_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToUnsignedLongLong(&((ProximityType *)NULL)->proximity);

    ProximityType_g_sampleAccessInfo.memberAccessInfos =
    ProximityType_g_memberAccessInfos;

    {
        RTI_SIZE_T candidateTypeSize = sizeof(ProximityType);

        if (candidateTypeSize > RTIXCdrLong_MAX) {
            ProximityType_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrLong_MAX;
        } else {
            ProximityType_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    ProximityType_g_sampleAccessInfo.languageBinding =
    RTI_XCDR_TYPE_BINDING_C ;

    OSAPI_Atomic_store(&is_initialized, 1, OSAPI_ATOMIC_MEMORY_ORDER_RELEASE);
    return (RTIXCdrSampleAccessInfo*) &ProximityType_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *ProximityType_get_type_plugin_info(void)
{
    static RTIXCdrTypePlugin ProximityType_g_typePlugin =
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction)
        ProximityType_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        ProximityType_finalize_w_return,
        NULL,
        NULL
    };

    return &ProximityType_g_typePlugin;
}
#endif

RTIBool ProximityType_initialize(
    ProximityType* sample)
{
    return ProximityType_initialize_ex(sample, RTI_TRUE, RTI_TRUE);
}

RTIBool ProximityType_initialize_ex(
    ProximityType* sample,
    RTIBool allocatePointers,
    RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return ProximityType_initialize_w_params(
        sample,
        &allocParams);

}

RTIBool ProximityType_initialize_w_params(
    ProximityType* sample,
    const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    if (allocParams == NULL)
    {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        const DDS_Char stringValue[] = "";
        const DDS_String temp = (DDS_String)stringValue;
        sample->name = DDS_String_alloc((16L));
        if (sample->name == NULL) {
            return RTI_FALSE;
        }
        if (!CDR_String_copy(&sample->name, &temp, (16L)))
        {
            return RTI_FALSE;
        }
    } else {
        if (sample->name != NULL) {
            const DDS_Char stringValue[] = "";
            const DDS_String temp = (DDS_String)stringValue;
            if (!CDR_String_copy(&sample->name, &temp, (16L)))
            {
                return RTI_FALSE;
            }
        } else {
            return RTI_FALSE;
        }
    }

    sample->proximity = 0.0f;

    return RTI_TRUE;
}

RTIBool ProximityType_finalize(
    ProximityType* sample)
{
    #ifndef RTI_CERT
    ProximityType_finalize_ex(sample,RTI_TRUE);
    #else
    UNUSED_ARG(sample);
    #endif
    return RTI_TRUE;
}

RTIBool ProximityType_finalize_w_return(
    ProximityType* sample)
{

    #ifndef RTI_CERT
    ProximityType_finalize_ex(sample,RTI_TRUE);
    #else
    UNUSED_ARG(sample);
    #endif
    return RTI_TRUE;
}

void ProximityType_finalize_ex(
    ProximityType* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample == NULL)
    {
        return;
    }

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    ProximityType_finalize_w_params(
        sample,&deallocParams);
}

void ProximityType_finalize_w_params(
    ProximityType* sample,
    const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample == NULL)
    {
        return;
    }

    if (deallocParams == NULL)
    {
        return;
    }

    #ifndef RTI_CERT
    if (sample->name != NULL) {
        DDS_String_free(sample->name);
        sample->name=NULL;

    }

    #endif
}

void ProximityType_finalize_optional_members(
    ProximityType* sample,
    RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample == NULL)
    {
        return;
    }

    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool ProximityType_copy(
    ProximityType* dst,
    const ProximityType* src)
{

    if (dst == NULL || src == NULL)
    {
        return RTI_FALSE;
    }

    if (!DDS_String_copy (
        &dst->name, &src->name,
        (16L) + 1)){
        return RTI_FALSE;
    }
    DDS_Primitive_copy (&dst->proximity, &src->proximity);

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'ProximityType' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T ProximityType
#define TSeq ProximityTypeSeq

#define T_initialize ProximityType_initialize

#define T_finalize   ProximityType_finalize
#define T_copy       ProximityType_copy

#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

#undef T_copy
#undef T_finalize

#undef T_initialize

#undef TSeq
#undef T

