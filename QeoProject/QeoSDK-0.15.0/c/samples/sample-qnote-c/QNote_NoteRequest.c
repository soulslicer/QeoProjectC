/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#include "QNote_NoteRequest.h"

const DDS_TypeSupport_meta org_qeo_sample_note_NoteRequest_type[] = {
    { .tc = CDR_TYPECODE_STRUCT, .name = "org.qeo.sample.note.NoteRequest", .flags = TSMFLAG_DYNAMIC|TSMFLAG_GENID|TSMFLAG_MUTABLE, .nelem = 3, .size = sizeof(org_qeo_sample_note_NoteRequest_t) },  
    { .tc = CDR_TYPECODE_LONG, .name = "id", .offset = offsetof(org_qeo_sample_note_NoteRequest_t, id) },  
    { .tc = CDR_TYPECODE_LONG, .name = "wallId", .offset = offsetof(org_qeo_sample_note_NoteRequest_t, wallId) },  
    { .tc = CDR_TYPECODE_CSTRING, .name = "message", .flags = TSMFLAG_DYNAMIC, .offset = offsetof(org_qeo_sample_note_NoteRequest_t, message), .size = 0 },  
};
