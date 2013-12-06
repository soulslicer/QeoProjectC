/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#include "QNote_Note.h"

const DDS_TypeSupport_meta org_qeo_sample_note_Note_type[] = {
    { .tc = CDR_TYPECODE_STRUCT, .name = "org.qeo.sample.note.Note", .flags = TSMFLAG_DYNAMIC|TSMFLAG_GENID|TSMFLAG_KEY|TSMFLAG_MUTABLE, .nelem = 3, .size = sizeof(org_qeo_sample_note_Note_t) },  
    { .tc = CDR_TYPECODE_LONG, .name = "id", .flags = TSMFLAG_KEY, .offset = offsetof(org_qeo_sample_note_Note_t, id) },  
    { .tc = CDR_TYPECODE_LONG, .name = "wallId", .flags = TSMFLAG_KEY, .offset = offsetof(org_qeo_sample_note_Note_t, wallId) },  
    { .tc = CDR_TYPECODE_CSTRING, .name = "message", .flags = TSMFLAG_DYNAMIC, .offset = offsetof(org_qeo_sample_note_Note_t, message), .size = 0 },  
};
