#include "rti_me_c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wh_sm/wh_sm_history.h"
#include "rh_sm/rh_sm_history.h"

#include "DatatypeDefinitions.h"
#include "DatatypeDefinitionsSupport.h"
#include "DatatypeDefinitionsPlugin.h"

#include "ApplicationCommon.h"

#ifdef USE_SAMPLE_FILTER
#ifdef FILTER_ON_DESERIALIZE

/* See Wire Protocol Specification on http://www.omg.org/spec/DDSI-RTPS/2.2/
* for more details about CDR encapsulation.
*/

/*ci \brief Unsigned Long type size */
#define UNSIGNED_LONG_SIZE  4

/*i
* \brief Example helper function to deserialize an unsigned long
*
* \param[in]  src_buffer      Pointer to CDR stream buffer
* \param[in]  need_byte_swap  Indicates whether it is needed to swap bytes
* \param[out] instance        Deserialized unsigned long
*/
/*
* static void
* ProximityTypeSubscriber_deserialize_unsigned_long(
    *     char **src_buffer,
    *     RTI_BOOL need_byte_swap,
    *     DDS_UnsignedLong *instance)
    * {
    *     RTI_INT32 i;
    *     if (need_byte_swap)
    *     {
        *         for (i = 3; i >= 0; --i)
        *         {
            *             *((RTI_INT8*)instance + i) = *((*src_buffer)++);
            *         }
        *     }
    *     else
    *     {
        *         *instance = *(RTI_UINT32*)(*src_buffer);
        *         (*src_buffer) += CDR_LONG_SIZE;
        *     }
    * }
*/

/*i
* \brief Implementation of \ref DDS_DataReaderListener::on_before_sample_deserialize
*/
static DDS_Boolean
ProximityTypeSubscriber_on_before_sample_deserialize(
    void *listener_data,
    DDS_DataReader *reader,
    struct NDDS_Type_Plugin *plugin,
    struct CDR_Stream_t *stream,
    DDS_Boolean *dropped)
{
    (void)listener_data;
    (void)reader;
    (void)plugin;
    (void)stream;

    /* Filtering Example:
    * If we have a IDL with an attribute id, we can filter samples
    * based on the value of this attribute. The following code filters
    * out samples with even id values.
    *
    * Note primitive types must be aligned to their length in the CDR stream.
    * For example, a long must start on a 4-byte boundary. The boundaries are
    * counted from the start of the CDR stream.
    * As the sample 'id' is the first data in the stream it is already aligned.
    * Position 0 (beginning of the stream) is aligned to 4 (size of long).
    *
    * NOTE: If you want to use a different field for filtering (e.g. you type does
    * not have a field called id as first field), you will need to reimplement this
    * function and ProximityTypeSubscriber_deserialize_unsigned_long
    * to match your type.
    *
    * DDS_Long id = 0;
    * RTI_BOOL need_byte_swap = DDS_BOOLEAN_FALSE;
    * char *src_buffer = NULL;
    *
    * need_byte_swap = CDR_Stream_is_byte_swapped(stream);
    * src_buffer = CDR_Stream_get_current_position_ptr(stream);
    *
    * if (!CDR_Stream_check_size(stream, UNSIGNED_LONG_SIZE))
    * {
        *     printf("Failed to deserialize id. The stream is too short, missing data\n");
        *     goto done;
        * }
    *
    * ProximityTypeSubscriber_deserialize_unsigned_long(
        *     &src_buffer,
        *     need_byte_swap,
        *     (DDS_UnsignedLong*)&id);
    *
    * *dropped = (id % 2 == 0) ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
    */

    /* TODO implement filter logic here */
    *dropped = DDS_BOOLEAN_FALSE;

    return DDS_BOOLEAN_TRUE;
}

#else

/*i
* \brief Helper function to filter an ProximityType sample
*
* \param[in]  sample       A ProximityType data sample to filter
* \param[out] drop_sample  Out parameter determining whether the sample
*                          should be filtered out or not.
*/
static void
ProximityTypeSubscriber_filter_sample(
    ProximityType *sample,
    DDS_Boolean *drop_sample)
{
    (void)sample;

    /* Filtering Example:
    * If we have a IDL with an attribute id, we can filter samples
    * based on the value of this attribute. The following code
    * filters out samples with even id values.
    *
    * *drop_sample = (sample->id % 2 == 0) ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
    */

    /* TODO implement filter logic here */
    *drop_sample = DDS_BOOLEAN_FALSE;
}

/*i
* \brief Implementation of \ref DDS_DataReaderListener::on_before_sample_commit
*/
static DDS_Boolean
ProximityTypeSubscriber_on_before_sample_commit(
    void *listener_data,
    DDS_DataReader *reader,
    const void *const sample,
    const struct DDS_SampleInfo *const sample_info,
    DDS_Boolean *dropped)
{
    ProximityType *hw_sample = (ProximityType *)sample;

    (void)listener_data;
    (void)reader;
    (void)sample_info;

    ProximityTypeSubscriber_filter_sample(hw_sample, dropped);

    if (*dropped)
    {
        printf("\nSample filtered, before commit...\n");
    }

    return DDS_BOOLEAN_TRUE;
}
#endif /* FILTER_ON_DESERIALIZE */
#endif /* USE_SAMPLE_FILTER */

static void
ProximityTypeSubscriber_on_subscription_matched(
    void *listener_data,
    DDS_DataReader *reader,
    const struct DDS_SubscriptionMatchedStatus *status)
{
    (void)listener_data;
    (void)reader;

    if (status->current_count_change > 0)
    {
        printf("Matched a proximity topic publisher\n");
    }
    else if (status->current_count_change < 0)
    {
        printf("Unmatched a proximity topic publisher\n");
    }
}

static void
ProximityTypeSubscriber_on_data_available(
    void *listener_data,
    DDS_DataReader * reader)
{
    ProximityTypeDataReader *hw_reader = ProximityTypeDataReader_narrow(reader);
    DDS_ReturnCode_t retcode;
    struct DDS_SampleInfo *sample_info = NULL;
    ProximityType *sample = NULL;

    struct DDS_SampleInfoSeq info_seq =
    DDS_SEQUENCE_INITIALIZER;
    struct ProximityTypeSeq sample_seq =
    DDS_SEQUENCE_INITIALIZER;

    DDS_Long i;
    DDS_Long *proximity_total_samples = (DDS_Long*) listener_data;

    retcode = ProximityTypeDataReader_take(
        hw_reader,
        &sample_seq,
        &info_seq,
        DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE,
        DDS_ANY_VIEW_STATE,
        DDS_ANY_INSTANCE_STATE);

    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to take data, retcode(%d)\n", retcode);
        goto done;
    }

    /* Print each valid sample taken */
    for (i = 0; i < ProximityTypeSeq_get_length(&sample_seq); ++i)
    {
        sample_info = DDS_SampleInfoSeq_get_reference(&info_seq, i);

        if (sample_info->valid_data)
        {
            sample = ProximityTypeSeq_get_reference(&sample_seq, i);

            printf("Proximity sensor %s detects: %f m\n", sample->name, sample->proximity);

            *proximity_total_samples += 1;

            /* TODO read and process sample attributes here */
            (void)sample;

        }
        else
        {
            printf("\nSample received\n\tINVALID DATA\n");
        }
    }

    ProximityTypeDataReader_return_loan(hw_reader, &sample_seq, &info_seq);

    done:
    #ifndef RTI_CERT
    ProximityTypeSeq_finalize(&sample_seq);
    DDS_SampleInfoSeq_finalize(&info_seq);
    #else
    return;
    #endif
}

static void
ProximityTypeSubscriber_on_deadline_missed(
    void *listener_data,
    DDS_DataReader * reader,
    const struct DDS_RequestedDeadlineMissedStatus *status)
{
    printf(
        "ALERT: No sample received within the 2-second deadline.\n"
        "  total missed deadlines: %ld\n"
        "  new missed deadlines: %ld\n",
        (long) status->total_count,
        (long) status->total_count_change);
}


static void
DeviceStatusTypeSubscriber_on_subscription_matched(
    void *listener_data,
    DDS_DataReader *reader,
    const struct DDS_SubscriptionMatchedStatus *status)
{
    (void)listener_data;
    (void)reader;

    if (status->current_count_change > 0)
    {
        printf("Matched a device status publisher\n");
    }
    else if (status->current_count_change < 0)
    {
        printf("Unmatched a device status publisher\n");
    }
}

static void
DeviceStatusTypeSubscriber_on_data_available(
    void *listener_data,
    DDS_DataReader * reader)
{
    DeviceStatusDataReader *hw_reader = DeviceStatusDataReader_narrow(reader);
    DDS_ReturnCode_t retcode;
    struct DDS_SampleInfo *sample_info = NULL;
    struct DeviceStatusSeq sample_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;

    retcode = DeviceStatusDataReader_take(
        hw_reader,
        &sample_seq,
        &info_seq,
        DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE,
        DDS_ANY_VIEW_STATE,
        DDS_ANY_INSTANCE_STATE);

    DDS_Long i;
    DDS_Long *device_status_total_samples = (DDS_Long*) listener_data;

    struct DeviceStatus *sample = NULL;

    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to take data, retcode(%d)\n", retcode);
        goto done;
    }

    /* Print each valid sample taken */
    for (i = 0; i < DeviceStatusSeq_get_length(&sample_seq); ++i)
    {
        sample_info = DDS_SampleInfoSeq_get_reference(&info_seq, i);

        if (sample_info->valid_data)
        {
            sample = DeviceStatusSeq_get_reference(&sample_seq, i);

            printf("Device %s detected: %u m\n", sample->deviceId, sample->deviceKind);

            *device_status_total_samples += 1;

            /* TODO read and process sample attributes here */
            (void)sample;

        }
        else
        {
            printf("\nSample received\n\tINVALID DATA\n");
        }
    }

    DeviceStatusDataReader_return_loan(hw_reader, &sample_seq, &info_seq);

    done:
    #ifndef RTI_CERT
    DeviceStatusSeq_finalize(&sample_seq);
    DDS_SampleInfoSeq_finalize(&info_seq);
    #else
    return;
    #endif
}

static int
subscriber_main_w_args(
    DDS_Long domain_id,
    char *udp_intf,
    const char *peer,
    DDS_Long sleep_time,
    DDS_Long count)
{
    DDS_Subscriber *subscriber;
    DDS_DataReader *proximity_dr;
    DDS_DataReader *device_status_dr;
    struct DDS_DataReaderQos dr_qos = DDS_DataReaderQos_INITIALIZER;
    DDS_ReturnCode_t retcode;
    struct Application *application;

    struct DDS_DataReaderListener proximity_dr_listener =
    DDS_DataReaderListener_INITIALIZER;
    struct DDS_DataReaderListener device_status_dr_listener =
    DDS_DataReaderListener_INITIALIZER;

    int ret_value = -1;
    DDS_Long proximity_total_samples = 0;
    DDS_Long device_status_total_samples = 0;
    DDS_Long i;

    application = Application_create(
        "Controller",
        domain_id,
        udp_intf,
        peer,
        sleep_time,
        count);

    if (application == NULL)
    {
        printf("application cannot be created\n");
        goto done;
    }

    retcode = DeviceStatusTypeSupport_register_type(
        application->participant,
        DeviceStatusTypeSupport_get_type_name());
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to register DeviceStatus\n");
        goto done;
    }

    retcode = ProximityTypeTypeSupport_register_type(
        application->participant,
        ProximityTypeTypeSupport_get_type_name());
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to register ProximityType\n");
        goto done;
    }

    DDS_Topic *proximity_topic = DDS_DomainParticipant_create_topic(
        application->participant,
        PROXIMITY_TOPIC,
        ProximityTypeTypeSupport_get_type_name(),
        &DDS_TOPIC_QOS_DEFAULT,
        NULL,
        DDS_STATUS_MASK_NONE);
    if (proximity_topic == NULL)
    {
        printf("topic == NULL\n");
        goto done;
    }

    DDS_Topic *device_status_topic = DDS_DomainParticipant_create_topic(
        application->participant,
        DEVICE_STATUS_TOPIC,
        DeviceStatusTypeSupport_get_type_name(),
        &DDS_TOPIC_QOS_DEFAULT,
        NULL,
        DDS_STATUS_MASK_NONE);
    if (device_status_topic == NULL)
    {
        printf("device_status_topic == NULL\n");
        goto done;
    }

    subscriber = DDS_DomainParticipant_create_subscriber(
        application->participant,
        &DDS_SUBSCRIBER_QOS_DEFAULT,
        NULL,
        DDS_STATUS_MASK_NONE);
    if (subscriber == NULL)
    {
        printf("subscriber == NULL\n");
        goto done;
    }

    #ifdef USE_DEADLINE_QOS
    /* add deadline policy - 2 seconds */
    /* dr_qos.deadline.period.sec = 2; */
    /* dr_qos.deadline.period.nanosec = 0; */
    proximity_dr_listener.on_requested_deadline_missed = ProximityTypeSubscriber_on_deadline_missed;
    #endif


    #ifdef USE_SAMPLE_FILTER
    /* choose one callback to enable */
    #ifdef FILTER_ON_DESERIALIZE
    proximity_dr_listener.on_before_sample_deserialize =
    ProximityTypeSubscriber_on_before_sample_deserialize;
    #else
    proximity_dr_listener.on_before_sample_commit =
    ProximityTypeSubscriber_on_before_sample_commit;
    #endif  /* FILTER_ON_DESERIALIZE */
    #endif  /* USE_SAMPLE_FILTER */

    proximity_dr_listener.on_data_available = ProximityTypeSubscriber_on_data_available;
    proximity_dr_listener.on_subscription_matched = ProximityTypeSubscriber_on_subscription_matched;
    proximity_dr_listener.as_listener.listener_data = &proximity_total_samples;


    struct DDS_Duration_t deadline = {2, 0};
    Application_configure_periodic_reader_qos(&dr_qos, &deadline);

    proximity_dr = DDS_Subscriber_create_datareader(
        subscriber,
        DDS_Topic_as_topicdescription(proximity_topic),
        &dr_qos,
        &proximity_dr_listener,
        DDS_DATA_AVAILABLE_STATUS | DDS_SUBSCRIPTION_MATCHED_STATUS | DDS_REQUESTED_DEADLINE_MISSED_STATUS);

    if (proximity_dr == NULL)
    {
        printf("proximity_dr == NULL\n");
        goto done;
    }


    device_status_dr_listener.on_data_available = DeviceStatusTypeSubscriber_on_data_available;
    device_status_dr_listener.on_subscription_matched = DeviceStatusTypeSubscriber_on_subscription_matched;
    device_status_dr_listener.as_listener.listener_data = &device_status_total_samples;
    Application_configure_status_reader_qos(&dr_qos, NULL);

    device_status_dr = DDS_Subscriber_create_datareader(
        subscriber,
        DDS_Topic_as_topicdescription(device_status_topic),
        &dr_qos,
        &device_status_dr_listener,
        DDS_DATA_AVAILABLE_STATUS | DDS_SUBSCRIPTION_MATCHED_STATUS);

    if (device_status_dr == NULL)
    {
        printf("device_status_dr == NULL\n");
        goto done;
    }



    #ifdef RTI_CERT
    #ifdef RTI_VXWORKS
    /** End initialization, disable further dynamic memory allocation ***/
    memAllocDisable();
    #endif
    #endif

    for (i = 0; (application->count <= 0) || (i < application->count); ++i)
    {
        printf("Subscriber sleeping for %d msec...\n", application->sleep_time);

        OSAPI_Thread_sleep((RTI_UINT32)application->sleep_time);
    }

    ret_value = 0;

    done:

    #ifndef RTI_CERT
    if (application != NULL)
    {
        Application_delete(application);
    }

    #endif
    #ifndef RTI_CERT
    retcode = DDS_DataReaderQos_finalize(&dr_qos);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("Cannot finalize DataReaderQos\n");
        return -1;
    }

    #endif
    if (ret_value == 0)
    {
        printf("Samples received %d\n", proximity_total_samples);
        if (proximity_total_samples == 0)
        {
            return -1;
        }
    }

    return ret_value;
}

#if !(defined(RTI_VXWORKS) && !defined(__RTP__))
int
main(int argc, char **argv)
{
    DDS_Long i = 0;
    DDS_Long domain_id = 0;
    const char *peer = NULL;
    char *udp_intf = NULL;
    DDS_Long sleep_time = 1000;
    DDS_Long count = 0;

    for (i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-domain"))
        {
            ++i;
            if (i == argc)
            {
                printf("-domain <domain_id>\n");
                return -1;
            }
            domain_id = (DDS_Long)strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-udp_intf"))
        {
            ++i;
            if (i == argc)
            {
                printf("-udp_intf <interface>\n");
                return -1;
            }
            udp_intf = argv[i];
        }
        else if (!strcmp(argv[i], "-peer"))
        {
            ++i;
            if (i == argc)
            {
                printf("-peer <address>\n");
                return -1;
            }
            peer = argv[i];
        }
        else if (!strcmp(argv[i], "-sleep"))
        {
            ++i;
            if (i == argc)
            {
                printf("-sleep_time <sleep_time>\n");
                return -1;
            }
            sleep_time = (DDS_Long)strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-count"))
        {
            ++i;
            if (i == argc)
            {
                printf("-count <count>\n");
                return -1;
            }
            count = (DDS_Long)strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-h"))
        {
            Application_subscriber_help(argv[0]);
            return 0;
        }
        else
        {
            printf("unknown option: %s\n", argv[i]);
            return -1;
        }
    }

    return subscriber_main_w_args(domain_id, udp_intf, peer, sleep_time, count);
}
#elif defined(RTI_VXWORKS)
int
subscriber_main(void)
{
    /* Explicitly configure args below */
    DDS_Long domain_id = 0;
    const char *peer = "_udp://127.0.0.1";
    char *udp_intf = NULL;
    DDS_Long sleep_time = 1000;
    DDS_Long count = 0;

    return subscriber_main_w_args(domain_id, udp_intf, peer, sleep_time, count);
}
#endif

