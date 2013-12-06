/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#include "QSimpleChat_ChatMessage.h"

const DDS_TypeSupport_meta org_qeo_sample_simplechat_ChatMessage_type[] = {
    { .tc = CDR_TYPECODE_STRUCT, .name = "org.qeo.sample.simplechat.ChatMessage", .flags = TSMFLAG_DYNAMIC|TSMFLAG_GENID|TSMFLAG_MUTABLE, .nelem = 2, .size = sizeof(org_qeo_sample_simplechat_ChatMessage_t) },  
    { .tc = CDR_TYPECODE_CSTRING, .name = "from", .flags = TSMFLAG_DYNAMIC, .offset = offsetof(org_qeo_sample_simplechat_ChatMessage_t, from), .size = 0 },  
    { .tc = CDR_TYPECODE_CSTRING, .name = "message", .flags = TSMFLAG_DYNAMIC, .offset = offsetof(org_qeo_sample_simplechat_ChatMessage_t, message), .size = 0 },  
};
