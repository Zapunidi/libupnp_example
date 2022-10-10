#include <stdio.h>

// Cross-platform sleep
#ifdef _WINDOWS
#define _WINSOCKAPI_ // Fix Winsock2 according to https://stackoverflow.com/questions/3059141/winsock-compile-error
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

// Cross platform upnp
#ifdef _WINDOWS
#include "upnp.h"
#else
#include <upnp/upnp.h>
#endif


int callback_event_handler(Upnp_EventType event_type, const void* event, void* cookie)
{
    switch (event_type) {
        case UPNP_DISCOVERY_SEARCH_RESULT:
            printf("Event: UPNP_DISCOVERY_SEARCH_RESULT\n");
            const UpnpDiscovery *d_event = (UpnpDiscovery *)event;
            
            int errCode = UpnpDiscovery_get_ErrCode(d_event);

    		if (errCode != UPNP_E_SUCCESS)
            {
	    		printf("Error in Discovery Callback -- %d\n", errCode);
                break;
            }
            
            // Information from the parent thread
            printf("The cookie value is \"%s\"\n", (char*)cookie);

            printf( "ErrCode     =  %d\n"
		            "Expires     =  %d\n"
		            "DeviceId    =  %s\n"
		            "DeviceType  =  %s\n"
		            "ServiceType =  %s\n"
		            "ServiceVer  =  %s\n"
		            "Location    =  %s\n"
		            "OS          =  %s\n"
		            "Date        =  %s\n"
		            "Ext         =  %s\n",
		            UpnpDiscovery_get_ErrCode(d_event),
		            UpnpDiscovery_get_Expires(d_event),
		            UpnpString_get_String(UpnpDiscovery_get_DeviceID(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_DeviceType(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_ServiceType(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_ServiceVer(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_Location(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_Os(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_Date(d_event)),
		            UpnpString_get_String(UpnpDiscovery_get_Ext(d_event)));          
            break;
        case UPNP_DISCOVERY_SEARCH_TIMEOUT:
            printf("Event: UPNP_DISCOVERY_SEARCH_TIMEOUT\n");
            break;
        case UPNP_DISCOVERY_ADVERTISEMENT_ALIVE:
            printf("Event: UPNP_DISCOVERY_ADVERTISEMENT_ALIVE\n");
            break;
        case UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE:
            printf("Event: UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE\n");
            break;
	    
        /* SOAP Stuff */
	    case UPNP_CONTROL_ACTION_COMPLETE:
	    case UPNP_CONTROL_GET_VAR_COMPLETE:
            printf("Event: SOAP type\n");
            break;

	    /* GENA Stuff */
	    case UPNP_EVENT_RECEIVED:
	    case UPNP_EVENT_SUBSCRIBE_COMPLETE:
	    case UPNP_EVENT_UNSUBSCRIBE_COMPLETE:
	    case UPNP_EVENT_RENEWAL_COMPLETE: 
	    case UPNP_EVENT_AUTORENEWAL_FAILED:
	    case UPNP_EVENT_SUBSCRIPTION_EXPIRED:
            printf("Event: GENA type\n");
            break;

	    /* ignore these cases, since this is not a device */
	    case UPNP_EVENT_SUBSCRIPTION_REQUEST:
	    case UPNP_CONTROL_GET_VAR_REQUEST:
	    case UPNP_CONTROL_ACTION_REQUEST:
        default:
            printf("Event: Unexpected!\n");
    }
    return 0;
}


int main(int argc, char** argv) {
    if (argc > 3 || argc < 2) {
        printf("Usage: %s [interface_name] <timeout_s>\n", argv[0]);
        return 1;
    }
    char if_name[100];
    unsigned int timeout;
    const char cookie[] = "I am a cookie.";
    UpnpClient_Handle client_handle = -1;
    int ret;

    sscanf(argv[argc - 1], "%d", &timeout);
    if (argc == 3) {
        sscanf(argv[1], "%s", if_name);
        ret = UpnpInit2(if_name, 0);
    }
    else {
        printf("Using first suitable network interface.\n");
        ret = UpnpInit2(NULL, 0);
    }
    if (ret != UPNP_E_SUCCESS) {
        printf("Init failed: code %i\n", ret);
        if (ret == UPNP_E_INVALID_INTERFACE) {
            printf("Bad interface name.");
        }
        return 2;
    }
    UpnpRegisterClient(callback_event_handler, &cookie, &client_handle);
    UpnpSearchAsync(client_handle, timeout, "upnp:rootdevice", cookie);
    Sleep(timeout * 1000);
    UpnpFinish();
    return 0;
}
