#include "rti_me_c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wh_sm/wh_sm_history.h"
#include "rh_sm/rh_sm_history.h"
#include "app_gen/app_gen_plugin.h"

#include "ApplicationCommon.h"
#include "../generated/SystemAppgen.h"

void
Application_publisher_help(char *appname)
{
    printf("%s [options]\n", appname);
    printf("options:\n");
    printf("-h                      - This text\n");
    printf("-domain <id>            - DomainId (default: 0)\n");
    printf("-udp_intf <intf>        - udp interface (no default)\n");
    printf("-peer <address>         - peer address (no default)\n");
    printf("-count <count>          - samples to publish (default: 300)\n");
    printf("-sleep <ms>             - delay between samples (default: 100)\n");
    printf("-sensorName <name>      - sensor name (default ProximitySensor)\n");
    printf("\n");
}

void
Application_subscriber_help(char *appname)
{
    printf("%s [options]\n", appname);
    printf("options:\n");
    printf("-h                      - This text\n");
    printf("-domain <id>            - DomainId (default: 0)\n");
    printf("-udp_intf <intf>        - udp interface (no default)\n");
    printf("-peer <address>         - peer address (no default)\n");
    printf("-count <count>          - receive iterations (default: 0)\n");
    printf("-sleep <ms>             - delay between checks (default: 1000)\n");
    printf("\n");
}

struct DDS_Duration_t Application_milliseconds_to_time(
    DDS_Long milliseconds)
{
    struct DDS_Duration_t time;

    if (milliseconds < 0)
    {
        milliseconds = 0;
    }

    time.sec = milliseconds / 1000;
    time.nanosec = (DDS_UnsignedLong)(milliseconds % 1000) * 1000000U;

    return time;
}

struct Application *
Application_create(
    const char *name,
    DDS_Long domain_id,
    char *udp_intf,
    const char *peer,
    DDS_Long sleep_time,
    DDS_Long count)
{
    DDS_DomainParticipantFactory *factory = NULL;
    DDS_Boolean success = DDS_BOOLEAN_FALSE;
    RT_Registry_T *registry = NULL;
    struct APPGEN_FactoryProperty appgen_property =
        APPGEN_FactoryProperty_INITIALIZER;
    struct Application *application = NULL;

    /* Uncomment to increase verbosity level:
    OSAPI_Log_set_verbosity(OSAPI_LOG_VERBOSITY_WARNING);
    */
    application = (struct Application *)malloc(sizeof(struct Application));

    if (application == NULL)
    {
        printf("failed to allocate application\n");
        goto done;
    }

    application->name = name;
    application->sleep_time = sleep_time;
    application->count = count;

    (void)domain_id;
    (void)udp_intf;
    (void)peer;

    factory = DDS_DomainParticipantFactory_get_instance();

    registry = DDS_DomainParticipantFactory_get_registry(factory);

    if (!RT_Registry_register(
        registry,
        DDSHST_WRITER_DEFAULT_HISTORY_NAME,
        WHSM_HistoryFactory_get_interface(),
        NULL,
        NULL))
    {
        printf("failed to register wh\n");
        goto done;
    }

    if (!RT_Registry_register(
        registry,
        DDSHST_READER_DEFAULT_HISTORY_NAME,
        RHSM_HistoryFactory_get_interface(),
        NULL,
        NULL))
    {
        printf("failed to register rh\n");
        goto done;
    }

    appgen_property._model = APPGEN_get_library_seq();
    if (!APPGEN_Factory_register(registry, &appgen_property))
    {
        printf("failed to register application generation model\n");
        goto done;
    }

    application->participant =
        DDS_DomainParticipantFactory_create_participant_from_config(
            factory,
            application->name
        );

    if (application->participant == NULL)
    {
        printf("failed to create participant\n");
        goto done;
    }

    success = DDS_BOOLEAN_TRUE;

    done:
    if (!success)
    {
        if (application != NULL)
        {
            #ifndef RTI_CERT
            free(application);
            #endif
            application = NULL;
        }
    }

    return application;
}

#ifndef RTI_CERT
void
Application_delete(struct Application *application)
{
    DDS_ReturnCode_t retcode;
    RT_Registry_T *registry = NULL;
    DDS_DomainParticipantFactory *factory = NULL;
    if (application == NULL)
    {
        return;
    }

    factory = DDS_DomainParticipantFactory_get_instance();

    if (application->participant != NULL)
    {
        retcode = DDS_DomainParticipant_delete_contained_entities(
            application->participant);
        if (retcode != DDS_RETCODE_OK)
        {
            printf("failed to delete contained entities (retcode=%d)\n",retcode);
        }

        retcode = DDS_DomainParticipantFactory_delete_participant(
            factory,
            application->participant);
        if (retcode != DDS_RETCODE_OK)
        {
            printf("failed to delete participant: %d\n", retcode);
            return;
        }
    }

    registry = DDS_DomainParticipantFactory_get_registry(factory);

    if (!APPGEN_Factory_unregister(registry, NULL))
    {
        printf("failed to unregister application generation model\n");
        return;
    }
    if (!RT_Registry_unregister(
        registry,
        DDSHST_READER_DEFAULT_HISTORY_NAME,
        NULL,
        NULL))
    {
        printf("failed to unregister rh\n");
        return;
    }

    if (!RT_Registry_unregister(
        registry,
        DDSHST_WRITER_DEFAULT_HISTORY_NAME,
        NULL,
        NULL))
    {
        printf("failed to unregister wh\n");
        return;
    }
    free(application);

    retcode = DDS_DomainParticipantFactory_finalize_instance();
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to finalize instance %d\n", retcode);
        return;
    }
}

#endif /* !RTI_CERT */
