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

#define DEVICE_ID_MAX_LENGTH 16U


static void
ProximityTypePublisher_on_publication_matched(
    void *listener_data,
    DDS_DataWriter *writer,
    const struct DDS_PublicationMatchedStatus *status)
{
    (void)listener_data;
    (void)writer;

    if (status->current_count_change > 0)
    {
        printf("Matched a subscriber\n");
    }
    else if (status->current_count_change < 0)
    {
        printf("Unmatched a subscriber\n");
    }
}

static int
publisher_main_w_args(
    DDS_Long domain_id,
    char *udp_intf,
    const char *peer,
    DDS_Long sleep_time,
    DDS_Long count,
    const char *sensor_name)
{
    DDS_Publisher *publisher;
    DDS_DataWriter *datawriter;
    ProximityTypeDataWriter *proximity_dw;
    DeviceStatusDataWriter *device_status_dw;
    DDS_ReturnCode_t retcode;
    ProximityType *proximity_sample = NULL;
    DeviceStatus *device_status_sample = NULL;
    struct Application *application = NULL;
    DDS_Long i;
    struct DDS_DataWriterListener dw_listener = DDS_DataWriterListener_INITIALIZER;
    int ret_value = -1;

    if (sensor_name == NULL || strlen(sensor_name) > DEVICE_ID_MAX_LENGTH)
    {
        printf("sensor name must be between 1 and %u characters\n",
               (unsigned int)DEVICE_ID_MAX_LENGTH);
        return -1;
    }

    proximity_sample = ProximityTypeTypeSupport_create_data();
    if (proximity_sample == NULL)
    {
        printf("failed ProximityTypeTypeSupport_create_data\n");
        return -1;
    }

    device_status_sample = DeviceStatusTypeSupport_create_data();
    if (device_status_sample == NULL)
    {
        printf("failed DeviceStatusTypeSupport_create_data\n");
        return -1;
    }

    application = Application_create(
        "DeviceParticipantLibrary::ProximitySensorParticipant",
        domain_id,
        udp_intf,
        peer,
        sleep_time,
        count);

    if (application == NULL)
    {
        printf("failed Application create\n");
        goto done;
    }

    publisher = DDS_DomainParticipant_lookup_publisher_by_name(
        application->participant, "ProximityPublisher");
    if (publisher == NULL)
    {
        printf("publisher == NULL\n");
        goto done;
    }


    dw_listener.on_publication_matched = ProximityTypePublisher_on_publication_matched;

    datawriter = DDS_Publisher_lookup_datawriter_by_name(
        publisher, "ProximityWriter");

    if (datawriter == NULL)
    {
        printf("datawriter == NULL\n");
        goto done;
    }

    retcode = DDS_DataWriter_set_listener(
        datawriter, &dw_listener, DDS_PUBLICATION_MATCHED_STATUS);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to set proximity writer listener\n");
        goto done;
    }

    proximity_dw = ProximityTypeDataWriter_narrow(datawriter);

    datawriter = DDS_Publisher_lookup_datawriter_by_name(
        publisher, "DeviceStatusWriter");

    if (datawriter == NULL)
    {
        printf("device_status_datawriter == NULL\n");
        goto done;
    }

    device_status_dw = DeviceStatusDataWriter_narrow(
        datawriter);

    retcode = DDS_DataWriter_set_listener(
        datawriter, &dw_listener, DDS_PUBLICATION_MATCHED_STATUS);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to set writer listener\n");
        goto done;
    }

    device_status_sample->deviceId = (DDS_String)sensor_name;
    device_status_sample->deviceKind = SENSOR;
    device_status_sample->deviceKindDetail._d = SENSOR;
    device_status_sample->deviceKindDetail._u.sensorKind = PROXIMITY;
    device_status_sample->status = ON;
    device_status_sample->extraInformation = (DDS_String)"";

    #ifdef RTI_CERT
    #ifdef RTI_VXWORKS
    /** End initialization, disable further dynamic memory allocation ***/
    memAllocDisable();
    #endif
    #endif

    for (i = 0; (application->count <= 0) || (i < application->count); ++i)
    {

        /* set sample attributes here */
        proximity_sample->proximity = (float)i;
        proximity_sample->name = (DDS_String)sensor_name;

        retcode = ProximityTypeDataWriter_write(
            proximity_dw,
            proximity_sample,
            &DDS_HANDLE_NIL);
        if (retcode != DDS_RETCODE_OK)
        {
            printf("Failed to write sample\n");
        }
        else
        {
            printf("Wrote sample #%d\n",(i+1));
        }

        retcode = DeviceStatusDataWriter_write(
            device_status_dw,
            device_status_sample,
            &DDS_HANDLE_NIL);
        if (retcode != DDS_RETCODE_OK)
        {
            printf("Failed to write device status sample\n");
        }

        OSAPI_Thread_sleep((RTI_UINT32)application->sleep_time);
    }

    ret_value = 0;

    done:

    #ifndef RTI_CERT
    if (application != NULL)
    {
        Application_delete(application);
    }

    if (proximity_sample != NULL)
    {
        ProximityTypeTypeSupport_delete_data(proximity_sample);
    }

    if (device_status_sample != NULL)
    {
        DeviceStatusTypeSupport_delete_data(device_status_sample);
    }

    #endif
    #ifndef RTI_CERT
    #endif

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
    DDS_Long sleep_time = 100;
    DDS_Long count = 300;
    const char *sensor_name = "ProximitySensor";

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
        else if (!strcmp(argv[i], "-sensorName"))
        {
            ++i;
            if (i == argc)
            {
                printf("-sensorName <name>\n");
                return -1;
            }
            sensor_name = argv[i];
        }
        else if (!strcmp(argv[i], "-h"))
        {
            Application_publisher_help(argv[0]);
            return 0;
        }
        else
        {
            printf("unknown option: %s\n", argv[i]);
            return -1;
        }
    }

    return publisher_main_w_args(
        domain_id, udp_intf, peer, sleep_time, count, sensor_name);
}
#elif defined(RTI_VXWORKS)
int
publisher_main(void)
{
    /* Explicitly configure args below */
    DDS_Long domain_id = 0;
    const char *peer = "_udp://127.0.0.1";
    char *udp_intf = NULL;
    DDS_Long sleep_time = 1000;
    DDS_Long count = 0;
    const char *sensor_name = "ProximitySensor";

    return publisher_main_w_args(
        domain_id, udp_intf, peer, sleep_time, count, sensor_name);
}
#endif
