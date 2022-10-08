# libupnp_example
An simple application example that use libupnp to list discovered devices (Linux only)

## Prerequisites

Install dependencies with
```bash
% sudo apt install libupnp-dev
```

## Building

Make a build dir and compile with linking of libupnp library:

```bash
% mkdir build
% gcc main.c -o build/libupnp_example -lupnp`
```

## Usage

Usage: `libupnp <interface_name> <timeout_s>`  
For example: `libupnp enp4s0 3` gives with sample libupnp tvdevices server the following output:

```
Event: UPNP_DISCOVERY_SEARCH_RESULT
The cookie value is "I am a cookie."
ErrCode     =  0
Expires     =  100
DeviceId    =  uuid:Upnp-TVEmulator-1_0-1234567890001
DeviceType  =  
ServiceType =  
ServiceVer  =  
Location    =  http://172.25.213.1:49152/tvdevicedesc.xml
OS          =  Linux/4.15.0-193-generic, UPnP/1.0, Portable SDK for UPnP devices/1.14.14
Date        =  Sat, 08 Oct 2022 07:41:35 GMT
Ext         =  
Event: UPNP_DISCOVERY_SEARCH_RESULT
The cookie value is "I am a cookie."
ErrCode     =  0
Expires     =  100
DeviceId    =  uuid:Upnp-TVEmulator-1_0-1234567890001
DeviceType  =  
ServiceType =  
ServiceVer  =  
Location    =  http://172.25.213.1:49152/tvdevicedesc.xml
OS          =  Linux/4.15.0-193-generic, UPnP/1.0, Portable SDK for UPnP devices/1.14.14
Date        =  Sat, 08 Oct 2022 07:41:35 GMT
Ext         =  
Event: UPNP_DISCOVERY_SEARCH_TIMEOUT
```
It contains three events: 2 DISCOVERY events and one TIMEOUT event. Expect only TIMEOUT event in case no SSDP server is running.
