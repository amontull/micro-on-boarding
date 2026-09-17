/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ProximityDatatype.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ProximityDatatype.h"
#include "reda/reda_bufferpool.h"
#if DDS_XTYPES_IS_ENABLED
#include "xcdr/xcdr_interpreter.h"
#include "xcdr/xcdr_dds_xcdr_type_plugin.h"
#include "xcdr/xcdr_dds_interpreter.h"
#endif
#include "ProximityDatatypePlugin.h"

/*** SOURCE_BEGIN ***/
#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
ProximityTypePlugin_create_sample(
    struct DDS_TypePlugin *plugin,
    void **sample)
{
    UNUSED_ARG(plugin);

    *sample = (void *) ProximityType_create();
    return (*sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
ProximityTypePlugin_delete_sample(
    struct DDS_TypePlugin *plugin,
    void *sample)
{
    UNUSED_ARG(plugin);

    #ifndef RTI_CERT
    /* ProximityType_delete() is a void function
    * which expects (sample != NULL). Since
    * ProximityTypePlugin_delete_sample
    * is an internal function, sample is assumed to be a valid pointer
    */
    ProximityType_delete((ProximityType *) sample);
    #endif

    return RTI_TRUE;
}
#endif

RTI_BOOL
ProximityTypePlugin_copy_sample(
    struct DDS_TypePlugin *plugin,
    void *dst,
    const void *src)
{
    UNUSED_ARG(plugin);

    return ProximityType_copy(
        (ProximityType*)dst,
        (const ProximityType*)src);
}
/* --------------------------------------------------------------------------
*  Type ProximityType Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation ProximityTypeEncapsulationKind[] =
{
    {
        DDS_ENCAPSULATION_ID_CDR_LE,
        DDS_ENCAPSULATION_ID_CDR_BE,
        0
    }
};

NDDSCDREncapsulation ProximityTypeV2EncapsulationKind[] =
{
    {

        DDS_ENCAPSULATION_ID_XCDR2_A_LE,
        DDS_ENCAPSULATION_ID_XCDR2_A_BE,
        0

    }
};

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
ProximityTypeTypePlugin_initialize_sample(struct DDS_TypePlugin *plugin, void *buffer)
{
    UNUSED_ARG(plugin);
    return ProximityType_initialize((ProximityType*)buffer);
}

RTI_PRIVATE RTI_UINT32
ProximityType_get_user_sample_size(
    struct DDS_TypePlugin *tp)
{
    UNUSED_ARG(tp);
    return sizeof(struct ProximityType);
}

MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
ProximityType_cdr_initialize(void *init_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)init_config;
    void *sample;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!ProximityTypePlugin_create_sample(&plugin->_parent,&sample))
    {
        return RTI_FALSE;
    }

    sh->sample = sample;

    return RTI_TRUE;
}

#ifndef RTI_CERT
MUST_CHECK_RETURN RTI_PRIVATE RTI_BOOL
ProximityType_cdr_finalize(void *finalize_config, void *buffer)
{
    struct DDS_TypePluginDefault *plugin = (struct DDS_TypePluginDefault*)finalize_config;
    struct DDS_TypePluginSampleHolder *sh = (struct DDS_TypePluginSampleHolder*)buffer;

    if (!ProximityTypePlugin_delete_sample(&plugin->_parent,sh->sample))
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}
#endif

RTI_PRIVATE void
ProximityTypeTypePlugin_return_sample(
    struct DDS_TypePlugin *tp,
    struct DDS_TypePluginSampleHolder *sample)
{
    ProximityType_finalize_optional_members((ProximityType*)sample->sample, RTI_FALSE);
    XCDR_GenericStreamPlugin_return_sample(tp, sample);
}

RTI_PRIVATE struct DDS_TypeMemoryPlugin*
ProximityTypeXTypesHeapPlugin_create(
    struct DDS_TypePlugin *tp,
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos)
{
    return DDS_XTypesHeapPlugin_create(
        tp,
        participant,
        dp_qos,
        endpoint_mode,
        endpoint,
        qos,
        NULL,
        NULL,
        ProximityType_cdr_initialize,
        #ifndef RTI_CERT
        ProximityType_cdr_finalize,
        #else
        NULL,
        #endif
        sizeof(ProximityType),
        RTI_FALSE
        );
}

RTI_PRIVATE struct DDS_TypeMemoryI ProximityType_fv_XTypesHeapPluginI =
{
    RTI_MEMORY_MANAGER_HEAP,
    RTI_MEMORY_TYPE_HEAP,
    ProximityTypePlugin_create_sample,
    #ifndef RTI_CERT
    ProximityTypePlugin_delete_sample,
    #else
    NULL,
    #endif
    NULL, /* get_address */
    NULL, /* return_address */
    NULL,
    DDS_XTypesHeapPlugin_get_sample_state,
    DDS_XTypesHeapPlugin_set_sample_state,
    DDS_XTypesHeapPlugin_is_owner,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ProximityTypeXTypesHeapPlugin_create,
    DDS_XTypesHeapPlugin_delete
};

RTI_PRIVATE DDS_Boolean
ProximityType_on_type_registered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    struct RTIXCdrInterpreterProgramsGenProperty programProperty =
    RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;

    programProperty.resolveAlias = RTI_XCDR_TRUE;
    programProperty.inlineStruct = RTI_XCDR_TRUE;
    programProperty.optimizeEnum = RTI_XCDR_TRUE;

    programs = RTIXCdrInterpreterPrograms_new(
        (RTIXCdrTypeCode *)ProximityType_get_typecode(),
        &programProperty,
        RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN);

    if (programs == NULL)
    {
        return DDS_BOOLEAN_FALSE;
    }

    DDS_TypeImpl_set_programs(type_impl, programs);
    DDS_TypeImpl_set_typecode(type_impl,  ProximityType_get_typecode());

    return DDS_BOOLEAN_TRUE;
}
RTI_PRIVATE DDS_Boolean
ProximityType_on_type_unregistered(struct DDS_TypeImpl* type_impl)
{
    struct RTIXCdrInterpreterPrograms *programs = NULL;
    programs = DDS_TypeImpl_get_programs(type_impl);

    if (programs != NULL)
    {
        RTIXCdrInterpreterPrograms_delete(programs);
    }
    DDS_TypeImpl_set_programs(type_impl, NULL);

    return DDS_BOOLEAN_TRUE;
}

RTI_PRIVATE
struct DDS_TypeEncapsulationI ProximityType_fv_XCDRv1PluginI =
{
    DDS_XCDR_DATA_REPRESENTATION,
    NULL,
    ProximityTypeEncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,
    ProximityTypeTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv1_StreamPlugin_get_serialized_sample_size,
    XCDRv1_StreamPlugin_create,
    XCDRv1_StreamPlugin_delete
};

RTI_PRIVATE struct DDS_TypeEncapsulationI ProximityType_fv_XCDRv2PluginI =
{
    DDS_XCDR2_DATA_REPRESENTATION,
    NULL,
    ProximityTypeV2EncapsulationKind,
    RTI_MEMORY_TYPE_HEAP,
    RTI_MEMORY_MANAGER_HEAP,
    NULL,
    NULL,
    XCDR_GenericStreamPlugin_get_buffer,
    XCDR_GenericStreamPlugin_return_buffer,
    XCDR_GenericStreamPlugin_get_sample,

    ProximityTypeTypePlugin_return_sample,
    XCDR_GenericStreamPlugin_serialize,
    XCDR_GenericStreamPlugin_deserialize,
    XCDRv2_StreamPlugin_get_serialized_sample_size,
    XCDRv2_StreamPlugin_create,
    XCDRv2_StreamPlugin_delete
};

RTI_PRIVATE struct DDS_TypeEncapsulationI *ProximityType_fv_WirePlugins[] =
{
    &ProximityType_fv_XCDRv2PluginI,
    &ProximityType_fv_XCDRv1PluginI,
    NULL
};

RTI_PRIVATE struct DDS_TypeMemoryI *ProximityType_fv_MemoryPlugins[] =
{
    &ProximityType_fv_XTypesHeapPluginI,
    NULL
};

RTI_PRIVATE const struct DDS_TypeInterfaceI ProximityType_fv_XCdrIntf =
{
    XCdrTypeInterfaceI_create_program,
    XCdrTypeInterfaceI_delete_program,
    XCdrTypeInterfaceI_create_execution_context,
    XCdrTypeInterfaceI_delete_execution_context,
    XCdrTypeInterfaceI_set_padding_options
};

RTI_PRIVATE struct DDS_TypePlugin*
ProximityTypeTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property);

RTI_PRIVATE RTI_BOOL
ProximityTypeTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin);

RTI_PRIVATE struct DDS_TypePluginI ProximityType_fv_TypePluginI =
{
    /**************************************************************************
    *                   Type information functions
    **************************************************************************/

    NULL,                       /* DDS_TypeCode_t* */
    NDDS_TYPEPLUGIN_USER_KEY,   /* NDDS_TypePluginKeyKind */

    NDDS_TYPEPLUGIN_EH_LOCATION_PAYLOAD,
    ProximityType_get_user_sample_size,
    RTI_MEMORY_TYPE_HEAP,
    XCDR_GenericTypePlugin_instance_to_keyhash,
    ProximityTypePlugin_copy_sample,

    ProximityTypeTypePlugin_initialize_sample,

    XCDR_GenericTypePlugin_serialize_key,
    XCDR_GenericTypePlugin_deserialize_key,
    XCDR_GenericTypelugin_get_serialized_key_size,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ProximityType_fv_MemoryPlugins,
    ProximityType_fv_WirePlugins,

    /**************************************************************************
    *       Helper APIs to create language binding wrapper Functions
    **************************************************************************/

    NULL, NULL, NULL, NULL,  /* endpoint wrappers not used in C */
    ProximityTypeTypePlugin_create_plugin,
    ProximityTypeTypePlugin_delete_plugin,
    ProximityType_on_type_registered,
    ProximityType_on_type_unregistered,
    &ProximityType_fv_XCdrIntf
};

/* --------------------------------------------------------------------------
*  Type ProximityType Plugin Methods
* -------------------------------------------------------------------------- */

struct DDS_TypePluginI*
ProximityTypeTypePlugin_get(void)
{
    return &ProximityType_fv_TypePluginI;
}

RTI_PRIVATE struct DDS_TypePlugin*
ProximityTypeTypePlugin_create_plugin(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_TypePluginMode_T endpoint_mode,
    DDS_TypePluginEndpoint *endpoint,
    DDS_TypePluginEndpointQos *qos,
    struct DDS_TypePluginProperty *const property)
{
    return DDS_TypePluginDefault_create(&ProximityType_fv_TypePluginI,
    participant,dp_qos,
    endpoint_mode,endpoint,qos,
    property);
}

RTI_PRIVATE RTI_BOOL
ProximityTypeTypePlugin_delete_plugin(struct DDS_TypePlugin *plugin)
{
    return DDS_TypePluginDefault_delete(plugin);
}

struct DDS_TypePlugin*
ProximityTypeWriterTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataWriter *writer,
    struct DDS_DataWriterQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &ProximityType_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_WRITER,
        (DDS_TypePluginEndpoint*)writer,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

struct DDS_TypePlugin*
ProximityTypeReaderTypePlugin_create(
    DDS_DomainParticipant *participant,
    struct DDS_DomainParticipantQos *dp_qos,
    DDS_DataReader *reader,
    struct DDS_DataReaderQos *qos,
    struct DDS_TypePluginProperty *property)
{
    return DDS_TypePlugin_create_w_intf(
        &ProximityType_fv_TypePluginI,
        participant,dp_qos,
        DDS_TYPEPLUGIN_MODE_READER,
        (DDS_TypePluginEndpoint*)reader,
        (DDS_TypePluginEndpointQos*)qos,
        property);
}

const char*
ProximityTypeTypePlugin_get_default_type_name(void)
{
    return ProximityTypeTYPENAME;
}

NDDS_TypePluginKeyKind
ProximityTypeI_get_key_kind(void)
{
    return ProximityType_fv_TypePluginI.key_kind;
}

