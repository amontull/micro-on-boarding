/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ProximityDatatype.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "ProximityDatatypeSupport.h"

/*** SOURCE_BEGIN ***/
/* =========================================================================== */

/* Requires */
#define TTYPENAME   ProximityTypeTYPENAME

/* 
ProximityTypeDataWriter (DDS_DataWriter)   
*/

/* Defines */
#define TDataWriter ProximityTypeDataWriter
#define TData       ProximityType

#include "dds_c/dds_c_tdatawriter_gen.h"

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
ProximityTypeDataReader (DDS_DataReader)   
*/

/* Defines */
#define TDataReader ProximityTypeDataReader
#define TDataSeq    ProximityTypeSeq
#define TData       ProximityType
#include "dds_c/dds_c_tdatareader_gen.h"
#undef TDataReader
#undef TDataSeq
#undef TData

DDS_ReturnCode_t
ProximityTypeTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = ProximityTypeTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    retcode = DDS_DomainParticipant_register_type(
        participant,
        type_name,
        ProximityTypeTypePlugin_get());

    if (retcode != DDS_RETCODE_OK)
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
ProximityTypeTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL)
    {
        goto done;
    }

    if (type_name == NULL)
    {
        type_name = ProximityTypeTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    if (ProximityTypeTypePlugin_get() !=
    DDS_DomainParticipant_unregister_type(participant,type_name))
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}
#endif
const char*
ProximityTypeTypeSupport_get_type_name(void)
{
    return ProximityTypeTYPENAME;
}
ProximityType *
ProximityTypeTypeSupport_create_data(void)
{
    ProximityType *data = NULL;

    data = ProximityType_create();

    return data;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
ProximityTypeTypeSupport_delete_data(
    ProximityType *data)
{
    ProximityType_delete(data);
    return DDS_RETCODE_OK;
}
#endif

static struct DDS_TypeProgramNode ProximityType_gv_ProgramNode = DDS_TypeProgramNode_INITIALIZER;

static DDS_DataRepresentationId_t ProximityType_gv_AutoRepresentation = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t ProximityType_gv_XCDR1 = DDS_XCDR_DATA_REPRESENTATION;
static DDS_DataRepresentationId_t ProximityType_gv_XCDR2 = DDS_XCDR2_DATA_REPRESENTATION;

DDS_ReturnCode_t
ProximityTypeTypeSupport_serialize_data_to_cdr_buffer_ex(
    char *buffer,
    unsigned int *length,
    const ProximityType *a_data,
    DDS_DataRepresentationId_t  representation)
{
    struct DDS_TypePlugin tp;
    DDS_EncapsulationId_t encapsulation;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    ProximityType_gv_ProgramNode.type_intf = ProximityTypeTypePlugin_get();

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        ProximityTypeTypePlugin_get(),
        &ProximityType_gv_ProgramNode,
        ProximityType_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    tp.property.program_context = ProximityType_gv_ProgramNode.context;

    DDS_TypePlugin_initialize_static(
        &tp,
        ProximityTypeTypePlugin_get(),
        programs);

    if (DDS_RETCODE_OK != DDS_TypeSupport_resolve_representation(
        &representation,
        ProximityType_gv_AutoRepresentation,
        ProximityType_gv_XCDR1,
        ProximityType_gv_XCDR2,
        &encapsulation))
    {
        return DDS_RETCODE_ERROR;
    }

    return XCDR_Interpreter_serialized_sample_to_buffer(
        &tp,
        buffer,
        length,
        (const void *)a_data,
        representation,
        encapsulation);
}

DDS_ReturnCode_t
ProximityTypeTypeSupport_serialize_data_to_cdr_buffer(
    char *buffer,
    unsigned int *length,
    const ProximityType *a_data)
{
    return ProximityTypeTypeSupport_serialize_data_to_cdr_buffer_ex(
        buffer,
        length,
        a_data,
        DDS_AUTO_DATA_REPRESENTATION);

}

DDS_ReturnCode_t
ProximityTypeTypeSupport_deserialize_data_from_cdr_buffer(
    ProximityType *a_data,
    const char *buffer,
    unsigned int length)
{
    struct CDR_Stream_t stream;
    struct DDS_TypePlugin tp;
    const struct RTIXCdrInterpreterPrograms *programs = NULL;

    DDS_TypePlugin_initialize(&tp);

    if (!CDR_Stream_initialize_w_buffer(&stream,buffer,length))
    {
        return DDS_RETCODE_ERROR;
    }

    programs = DDS_DomainParticipantFactory_assert_program(
        DDS_TheParticipantFactory,
        ProximityTypeTypePlugin_get(),
        &ProximityType_gv_ProgramNode,
        ProximityType_get_typecode());

    if (programs == NULL)
    {
        return DDS_RETCODE_ERROR;
    }

    tp.property.program_context = ProximityType_gv_ProgramNode.context;

    DDS_TypePlugin_initialize_static(
        &tp,
        ProximityTypeTypePlugin_get(),
        programs);

    if (!XCDR_Interpreter_deserialize(&tp,a_data,&stream,RTI_TRUE,RTI_TRUE,0))
    {
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

#undef TTYPENAME

