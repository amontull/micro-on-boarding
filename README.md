# Connext Micro Exercise - Sensor/Controller/Brake Application

This project is a small RTI Connext Micro application that publishes and
subscribes to a keyed `ProximityType` data type over UDP. The project is built
from the root directory; generated type-support files are kept at the root and
application-specific sources are kept in [`src`](src/).

The IDL defines one key field and one value field:

```idl
struct ProximityType {
		@key string<16> name;
		float proximity;
};
```

The CMake project builds two executables:

- `ProximitySensor` publishes proximity samples.
- `Controller` subscribes to proximity samples.

They communicate on the DDS topic `ProximityTopic` using Connext
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

### Generate Type Support

The type-support files at the repository root can be generated or updated from
the IDL with `rtiddsgen`:

```bash
cd /path/to/micro-on-boarding
"$RTIMEHOME/rtiddsgen/scripts/rtiddsgen" \
	-micro -language C -update typefiles -d . DatatypeDefinitions.idl
```

This generates or updates:

- `DatatypeDefinitions.c`, `.h`
- `DatatypeDefinitionsPlugin.c`, `.h`
- `DatatypeDefinitionsSupport.c`, `.h`

The application and shared infrastructure sources in `src/` are maintained
separately from the generated type support. Do not edit generated files
manually unless you intend to maintain those changes when the IDL is
regenerated.

## Build

From the repository root:

```bash
cmake -S . -B build \
	-DRTIMEHOME="$RTIMEHOME" \
	-DRTIME_TARGET_NAME="$RTIME_TARGET_NAME" \
	-DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

The executables are written to:

```text
objs/x86_64leElfgcc13.3.0-Linux6/
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
./objs/x86_64leElfgcc13.3.0-Linux6/Controller \
	-domain 0 -udp_intf lo -peer 127.0.0.1

# Terminal 2
./objs/x86_64leElfgcc13.3.0-Linux6/ProximitySensor \
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
the repository root:

```bash
"$RTIMEHOME/rtiddsgen/scripts/rtiddsgen" \
	-convertToXml DatatypeDefinitions.idl
```

This creates or updates [`DatatypeDefinitions.xml`](DatatypeDefinitions.xml),
which describes `ProximityType`. It does not create the DDS topic; the running
publisher creates `ProximityTopic`.

In Admin Console:

1. Start the publisher on DDS domain `0`:

	```bash
	./objs/x86_64leElfgcc13.3.0-Linux6/ProximitySensor \
		-domain 0 -udp_intf lo -peer 127.0.0.1 -count 10 -sensorName "MySensor"
	```

2. Join or add DDS domain `0` in the DDS Logical View.
3. Locate `ProximityTopic` and choose **Subscribe**.
4. Load `DatatypeDefinitions.xml`, select `ProximityType`, and create
	the subscription.
5. Open **Topic Data** or **Sample Inspector** to view `name` and `proximity`.

Use best-effort reliability in Admin Console, with a requested deadline of one
second or longer. For a different host, replace `lo` with the publisher's real
interface and `127.0.0.1` with a reachable discovery peer; allow DDS/RTPS UDP
traffic through the firewall.

## Project Layout

| Path | Purpose |
| --- | --- |
| `DatatypeDefinitions.idl` | DDS data type and topic constant definition |
| `DatatypeDefinitions*.c/.h` | Generated type support |
| `src/ProximitySensor.c` | Publisher and DataWriter logic |
| `src/Controller.c` | Subscriber and DataReader logic |
| `src/ApplicationCommon.c/.h` | Participant, UDP, discovery, and shared QoS setup |
| `CMakeLists.txt` | CMake build and optional IDL regeneration rules |
| `DatatypeDefinitions.xml` | XML type description for Admin Console |

## Troubleshooting

- If CMake cannot find Connext Micro, check `RTIMEHOME` and
	`RTIME_TARGET_NAME`.
- If the applications do not match, verify that both use the same domain ID,
	peer configuration, and network interface.
- The source defaults to `eth0` as its second allowed Linux interface. Use
	`-udp_intf` on systems that use names such as `ens160` or `wlan0`.
- Use `-count` to stop the publisher automatically; without it, publishing
	continues indefinitely.
- Run `./.../ProximitySensor -h` or `./.../Controller -h` to display the
	built-in help.


## Questions

- Can I re-use a single generic data writer, and simply narrow any specific data writer with it?
