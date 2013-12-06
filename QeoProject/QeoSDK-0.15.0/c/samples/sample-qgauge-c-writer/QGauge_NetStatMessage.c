/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#include "QGauge_NetStatMessage.h"

const DDS_TypeSupport_meta org_qeo_sample_gauge_NetStatMessage_type[] = {
    { .tc = CDR_TYPECODE_STRUCT, .name = "org.qeo.sample.gauge.NetStatMessage", .flags = TSMFLAG_DYNAMIC|TSMFLAG_GENID|TSMFLAG_KEY|TSMFLAG_MUTABLE, .nelem = 7, .size = sizeof(org_qeo_sample_gauge_NetStatMessage_t) },  
    { .tc = CDR_TYPECODE_TYPEREF, .name = "deviceId", .flags = TSMFLAG_KEY, .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, deviceId), .tsm = org_qeo_system_DeviceId_type },  
    { .tc = CDR_TYPECODE_CSTRING, .name = "ifName", .flags = TSMFLAG_DYNAMIC|TSMFLAG_KEY, .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, ifName), .size = 0 },  
    { .tc = CDR_TYPECODE_LONGLONG, .name = "bytesIn", .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, bytesIn) },  
    { .tc = CDR_TYPECODE_LONGLONG, .name = "packetsIn", .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, packetsIn) },  
    { .tc = CDR_TYPECODE_LONGLONG, .name = "bytesOut", .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, bytesOut) },  
    { .tc = CDR_TYPECODE_LONGLONG, .name = "packetsOut", .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, packetsOut) },  
    { .tc = CDR_TYPECODE_LONGLONG, .name = "timestamp", .offset = offsetof(org_qeo_sample_gauge_NetStatMessage_t, timestamp) },  
};
