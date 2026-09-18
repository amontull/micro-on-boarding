# Exercise 1. "Proximity Data" topic

This project is a small RTI Connext Micro example that publishes and subscribes
to a keyed `ProximityType` data type over UDP. The example is contained in
[`exercise01`](exercise01/).

The IDL defines one key field and one value field:

```idl
struct ProximityType {
		@key string<16> name;
		float proximity;
};
```

The generated application contains two executables:

- `ProximityDatatype_publisher`
- `ProximityDatatype_subscriber`

They communicate on the DDS topic `Example ProximityType` using Connext
Micro's dynamic participant and endpoint discovery (DPDE).


## Requirements

- RTI Connext Micro 4.3.0
- A supported C compiler
- CMake 3.12 or newer
- Linux, macOS, or Windows with a matching Connext Micro target library

The current Linux build uses the target
`x86_64leElfgcc13.3.0-Linux6`.

Set the Connext Micro installation and target before configuring CMake. For
example:

```bash
export RTIMEHOME=/path/to/rti_connext_dds_micro-4.3.0
export RTIME_TARGET_NAME=x86_64leElfgcc13.3.0-Linux6
```

`RTIME_TARGET_NAME` must match a directory under
`$RTIMEHOME/lib/`. Use the target supplied by your installation if it differs
from the example above.

### Generate the C Files

The type and application files in `exercise01/` can be generated from the IDL
with the Connext Micro templates:

```bash
cd exercise01
"$RTIMEHOME/rtiddsgen/scripts/rtiddsgen" \
	-micro -language C -example ProximityDatatype.idl
```

This generates or updates the type support and example sources, including:

- `ProximityDatatype.c`, `.h`
- `ProximityDatatypePlugin.c`, `.h`
- `ProximityDatatypeSupport.c`, `.h`
- `ProximityDatatypeApplication.c`, `.h`
- `ProximityDatatype_publisher.c`
- `ProximityDatatype_subscriber.c`
- `CMakeLists.txt` and `README.txt`

The generated type-support sources are required by both applications. Do not
edit generated files manually unless you intend to maintain those changes when
the IDL is regenerated.

## Build

From the repository root:

```bash
cmake -S exercise01 -B build \
	-DRTIMEHOME="$RTIMEHOME" \
	-DRTIME_TARGET_NAME="$RTIME_TARGET_NAME" \
	-DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

The executables are written to:

```text
exercise01/objs/x86_64leElfgcc13.3.0-Linux6/
```

To let CMake regenerate the type-support files when the IDL changes, add:

```bash
-DRTIME_IDL_ADD_REGENERATE_TYPESUPPORT_RULE=true
```

The generated CMake project also supports `EXCLUDE_SHMEM` and `EXCLUDE_ZCV2`
when those transports are not needed.

## Run

Start the subscriber and publisher in separate terminals. A finite run is
usually more convenient while testing:

```bash
# Terminal 1
./exercise01/objs/x86_64leElfgcc13.3.0-Linux6/ProximityDatatype_subscriber \
	-domain 0 -udp_intf lo -peer 127.0.0.1

# Terminal 2
./exercise01/objs/x86_64leElfgcc13.3.0-Linux6/ProximityDatatype_publisher \
	-domain 0 -udp_intf lo -peer 127.0.0.1 -count 10 -sleep 1000 \
	-sensorName ProximitySensor
```

The publisher options are:

| Option | Meaning | Default |
| --- | --- | --- |
| `-domain <id>` | DDS domain ID | `0` |
| `-udp_intf <interface>` | UDP network interface | platform fallback |
| `-peer <address>` | Initial discovery peer | loopback |
| `-count <count>` | Number of samples to publish | `300` |
| `-sleep <ms>` | Delay between published samples | `100` |
| `-sensorName <name>` | Key value assigned to each published sample | `ProximitySensor` |
| `-h` | Show help | |

The subscriber accepts the shared connection options plus `-count` and
`-sleep`. Its defaults are `0` receive iterations and a `1000` ms delay. The
subscriber does not accept `-sensorName` because it does not create samples.

## Subscribe from Admin Console

Convert the IDL to XML so Admin Console can decode the samples. Run this from
`exercise01`:

```bash
rtiddsgen -convertToXml ProximityDatatype.idl
```

This creates or updates [`ProximityDatatype.xml`](exercise01/ProximityDatatype.xml),
which describes `ProximityType`. It does not create the DDS topic; the running
publisher creates `ProximityTopic`.

In Admin Console:

1. Start the publisher on DDS domain `0`:

	```bash
	./objs/x86_64leElfgcc13.3.0-Linux6/ProximityDatatype_publisher \
		-domain 0 -udp_intf lo -peer 127.0.0.1 -count 10 -sensorName "MySensor"
	```

2. Join or add DDS domain `0` in the DDS Logical View.
3. Locate `ProximityTopic` and choose **Subscribe**.
4. Load `exercise01/ProximityDatatype.xml`, select `ProximityType`, and create
	the subscription.
5. Open **Topic Data** or **Sample Inspector** to view `name` and `proximity`.

Use best-effort reliability in Admin Console, with a requested deadline of one
second or longer. For a different host, replace `lo` with the publisher's real
interface and `127.0.0.1` with a reachable discovery peer; allow DDS/RTPS UDP
traffic through the firewall.

## Project Layout

| Path | Purpose |
| --- | --- |
| `exercise01/ProximityDatatype.idl` | DDS data type definition |
| `exercise01/ProximityDatatype_publisher.c` | Publisher and DataWriter logic |
| `exercise01/ProximityDatatype_subscriber.c` | Subscriber and DataReader logic |
| `exercise01/ProximityDatatypeApplication.c` | Participant, topic, UDP, and discovery setup |
| `exercise01/ProximityDatatype*.c/.h` | Generated type support |
| `exercise01/CMakeLists.txt` | CMake build and optional IDL regeneration rules |
| `exercise01/README.txt` | Generated example-specific reference |

## Troubleshooting

- If CMake cannot find Connext Micro, check `RTIMEHOME` and
	`RTIME_TARGET_NAME`.
- If the applications do not match, verify that both use the same domain ID,
	peer configuration, and network interface.
- The source defaults to `eth0` as its second allowed Linux interface. Use
	`-udp_intf` on systems that use names such as `ens160` or `wlan0`.
- Use `-count` to stop the publisher automatically; without it, publishing
	continues indefinitely.
- Run `./.../ProximityDatatype_publisher -h` or
	`./.../ProximityDatatype_subscriber -h` to display the built-in help.

## Change log

The following changes have been applied to Exercise 1:

- Disabled reliable writer/reader QoS by default; best-effort reliability is
	now used unless `USE_RELIABLE_QOS` is enabled.
- Added deadline QoS support with a one-second writer deadline and a
	two-second reader deadline.
- Added a subscriber callback that reports missed deadlines and enabled the
	`DDS_REQUESTED_DEADLINE_MISSED_STATUS` status on the DataReader.
- Reduced the writer and reader maximum samples per instance from 32 to 1,
	leaving the default `KEEP_LAST` history depth of 1 in use.
- Limited the shared `Application` object to participant, timing, and runtime
	configuration. It no longer stores a topic or type name.
- Removed the unused `local_participant_name` and `remote_participant_name`
	parameters from `Application_create` and updated both applications to use
	the simplified API.
- Moved `ProximityType` registration and `Example ProximityType` topic
	creation from the shared application code into the publisher and subscriber.
	This keeps type and topic ownership local to the applications that use
	them, which allows larger systems to define separate application-specific
	topics and endpoints.

For the full generated build notes and platform-specific commands, see
[`exercise01/README.txt`](exercise01/README.txt).

