/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#ifndef QDM_QGAUGE_NETSTATMESSAGE_H_
#define QDM_QGAUGE_NETSTATMESSAGE_H_

#include <qeo/types.h>
#include "qeo_types.h"


/**
 * NetStatMessage represents different statistics of a network interface.
 */
typedef struct {
    /**
     * [Key] The DeviceId of the host of this network interface.
     */
    org_qeo_system_DeviceId_t deviceId;
    /**
     * [Key] The name of the network interface.
     */
    char * ifName;
    /**
     * The number of bytes received.
     */
    int64_t bytesIn;
    /**
     * The number of packets received.
     */
    int64_t packetsIn;
    /**
     * The number of bytes transmitted.
     */
    int64_t bytesOut;
    /**
     * The number of packets transmitted.
     */
    int64_t packetsOut;
    /**
     * The timestamp (in milliseconds) at which this NetStatMessage was updated.
     */
    int64_t timestamp;
} org_qeo_sample_gauge_NetStatMessage_t;
extern const DDS_TypeSupport_meta org_qeo_sample_gauge_NetStatMessage_type[];


#endif /* QDM_QGAUGE_NETSTATMESSAGE_H_ */

