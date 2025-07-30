# RBUS Plugin for Broadband TR181

## Overview

This project implements a plugin for integrating RBUS (Remote Bus) with a broadband TR181 data model. The plugin communicates with the blizzard-rdk server using Protocol Buffers (protobuf) over a Unix socket. It provides methods for getting/setting properties and invoking methods via RBUS, wrapped in a protobuf-based interface.

Key features:
- Supports getting multiple property values (`get` method).
- Supports setting property values (`set` method).
- Supports invoking arbitrary methods (`invoke` method).
- Uses protobuf for schema definition and message serialization.
- Connects to a Unix socket at `/tmp/blizzard.sock`.

The plugin is designed for embedded systems or environments where RBUS is used for device management, such as in broadband gateways.

## Requirements

- CMake >= 3.13
- RBUS library (for remote bus communication).
- Protobuf-C library (for protobuf serialization).
- Standard C development tools (gcc, make).
- Unix-like system (for Unix socket support).

On macOS, install RBUS via Homebrew:  
```
brew tap stepherg/tap
brew install rbus
```

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/stepherg/blizzard-plugin-rbus
   cd blizzard-plugin-rbus
   ```

2. Build using CMake:
   ```
   mkdir build && cd build
   cmake ..
   make
   ```

   This will generate the executable `rbus_plugin` in the build directory.

3. Install dependencies if missing:
   - On Ubuntu/Debian: `sudo apt install libprotobuf-c-dev cmake` (and RBUS if available via package).
   - On MacOS: `brew install protobuf protobuf-c`

## Usage

1. Run the plugin:
   ```
   ./rbus_plugin
   ```

   The plugin will connect to the Unix socket at `/tmp/blizzard.sock`, initialize RBUS, register itself with the manager, and listen for messages (e.g., invoke requests for `get`, `set`, `invoke`).

2. Interaction:
   - The plugin registers methods: `get`, `set`, `invoke`.
   - Example: To get properties, send an invoke request with method="get" and parameters={"path": ["prop1", "prop2"]}.
   - Responses are sent back via protobuf messages.

   Ensure the blizzard-rdk server is running and listening on the socket.

### Example Interaction via JSON-RPC

Assuming blizzard-rdk is exposed via a JSON-RPC server on port 8821, you can interact using curl:

#### Get Example
```
curl -s -X POST http://127.0.0.1:8821 \
     -H "Content-Type: application/json" \
     -d '{
   "jsonrpc": "2.0",
   "method": "org.rdk.broadband.TR181.1.get",
   "id": 1,
   "params": {"path":["Device.DeviceInfo.ModelName","Device.DeviceInfo.SerialNumber"]}
}'
```

Expected response:

```
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "key": "Device.DeviceInfo.ModelName",
      "value": "VCPE"
    },
    {
      "key": "Device.DeviceInfo.SerialNumber",
      "value": "G3Q5W9TG09"
    }
  ]
}
```

#### Set Example
```
curl -s -X POST http://127.0.0.1:8821 \
     -H "Content-Type: application/json" \
     -d '{
   "jsonrpc": "2.0",
   "method": "org.rdk.broadband.TR181.1.set",
   "id": 1,
   "params": {"key":"Device.Test.Property","value":"testvalue"}
}'
```

Expected response:

```
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Success"
}
```

#### Invoke Example (Reboot with Delay)
```
curl -s -X POST http://127.0.0.1:8821 \
     -H "Content-Type: application/json" \
     -d '{
   "jsonrpc": "2.0",
   "method": "org.rdk.broadband.TR181.1.invoke",
   "id": 1,
   "params": {"method": "Device.Reboot()","params": [{"key": "Delay","value": 10}]}
}'
```

Expected response:

```
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "key": "Status",
      "value": "Reboot scheduled"
    }
  ]
}
```

#### Invoke Example (GetSystemInfo with empty params)
```
curl -s -X POST http://127.0.0.1:8821 \
     -H "Content-Type: application/json" \
     -d '{
   "jsonrpc": "2.0",
   "method": "org.rdk.broadband.TR181.1.invoke",
   "id": 1,
   "params": {"method": "Device.GetSystemInfo()","params": []}
}'
```

Expected response:

```
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "key": "SerialNumber",
      "value": "G3Q5W9TG09"
    },
    {
      "key": "SystemTime",
      "value": "1753901014.330479"
    },
    {
      "key": "UpTime",
      "value": "455778"
    }
  ]
}
```
