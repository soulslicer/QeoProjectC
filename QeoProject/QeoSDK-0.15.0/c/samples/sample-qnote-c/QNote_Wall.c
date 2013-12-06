/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#include "QNote_Wall.h"

const DDS_TypeSupport_meta org_qeo_sample_note_Wall_type[] = {
    { .tc = CDR_TYPECODE_STRUCT, .name = "org.qeo.sample.note.Wall", .flags = TSMFLAG_DYNAMIC|TSMFLAG_GENID|TSMFLAG_KEY|TSMFLAG_MUTABLE, .nelem = 2, .size = sizeof(org_qeo_sample_note_Wall_t) },  
    { .tc = CDR_TYPECODE_LONG, .name = "id", .flags = TSMFLAG_KEY, .offset = offsetof(org_qeo_sample_note_Wall_t, id) },  
    { .tc = CDR_TYPECODE_CSTRING, .name = "description", .flags = TSMFLAG_DYNAMIC, .offset = offsetof(org_qeo_sample_note_Wall_t, description), .size = 0 },  
};
