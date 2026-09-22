#ifndef Application_h
#define Application_h

#include "rti_me_c.h"

/*e \dref_Example_Config_UseReliableQos
* Define USE_RELIABLE_QOS to use reliable
* reliability on the DataReader; otherwise, use
* best-effort reliability by default.
*/

/* #define USE_RELIABLE_QOS */

/*e \dref_Example_Config_UseDeadlineQos
* Define USE_DEADLINE_QOS to enable the deadline QoS policy
* on the DataReader.
*/

#define USE_DEADLINE_QOS

/*e \dref_Example_Config_UseSampleFilter
* Define USE_SAMPLE_FILTER to filter samples
* using call-backs on the DataReader's listener.
* Modify the following functions to implement the filter logic:
* - "ProximityTypeSubscriber_filter_sample"
* - "ProximityTypeSubscriber_on_before_sample_deserialize"
* - "ProximityTypeSubscriber_on_before_sample_commit"
* - "ProximityTypeSubscriber_deserialize_unsigned_long"
*/

/*#define USE_SAMPLE_FILTER*/

/*e \dref_Example_Config_FilterOnDeserialize
* Define FILTER_ON_DESERIALIZE to enable
* filtering on call-back on_before_sample_deserialize;
* otherwise use call-back on_before_sample_commit
* by default. */

/*#define FILTER_ON_DESERIALIZE*/

struct Application
{
    DDS_DomainParticipant *participant;
    DDS_Long sleep_time;
    DDS_Long count;
};

extern void
Application_publisher_help(char *appname);

extern void
Application_subscriber_help(char *appname);

extern struct Application*
Application_create(
    DDS_Long domain_id,
    char *udp_intf,
    const char *peer,
    DDS_Long sleep_time,
    DDS_Long count);

extern void Application_configure_periodic_writer_qos(
    struct DDS_DataWriterQos *qos,
    const struct DDS_Duration_t *const deadline);

extern void Application_configure_periodic_reader_qos(
    struct DDS_DataReaderQos *qos,
    const struct DDS_Duration_t *const deadline);

extern void Application_configure_status_writer_qos(
    struct DDS_DataWriterQos *qos,
    const struct DDS_Duration_t *const lease_duration);

extern void Application_configure_status_reader_qos(
    struct DDS_DataReaderQos *qos,
    const struct DDS_Duration_t *const lease_duration);

extern struct DDS_Duration_t Application_milliseconds_to_time(
    DDS_Long milliseconds);

#ifndef RTI_CERT
extern void
Application_delete(struct Application *application);

#endif
#endif

