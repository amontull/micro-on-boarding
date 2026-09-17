# Connext Micro C Publish/Subscribe Exercises

## Exercise 1. "Proximity Data" topic

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

### Requirements

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
	-domain 0 -udp_intf lo -peer 127.0.0.1 -count 10 -sleep 1000
```

The command-line options are:

| Option | Meaning | Default |
| --- | --- | --- |
| `-domain <id>` | DDS domain ID | `0` |
| `-udp_intf <interface>` | UDP network interface | platform fallback |
| `-peer <address>` | Initial discovery peer | loopback |
| `-count <count>` | Number of samples to publish | `0`, forever |
| `-sleep <ms>` | Delay between published samples | `1000` |
| `-h` | Show help | |

For communication between two hosts, replace `lo` with the actual interface,
such as `eth0` or `ens160`, and replace `127.0.0.1` with a reachable peer
address. Both processes must use the same domain ID and compatible discovery
settings. Confirm that UDP traffic and, where applicable, multicast traffic
are allowed by the host and network firewall.

### Project Layout

| Path | Purpose |
| --- | --- |
| `exercise01/ProximityDatatype.idl` | DDS data type definition |
| `exercise01/ProximityDatatype_publisher.c` | Publisher and DataWriter logic |
| `exercise01/ProximityDatatype_subscriber.c` | Subscriber and DataReader logic |
| `exercise01/ProximityDatatypeApplication.c` | Participant, topic, UDP, and discovery setup |
| `exercise01/ProximityDatatype*.c/.h` | Generated type support |
| `exercise01/CMakeLists.txt` | CMake build and optional IDL regeneration rules |
| `exercise01/README.txt` | Generated example-specific reference |

### Troubleshooting

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

For the full generated build notes and platform-specific commands, see
[`exercise01/README.txt`](exercise01/README.txt).
