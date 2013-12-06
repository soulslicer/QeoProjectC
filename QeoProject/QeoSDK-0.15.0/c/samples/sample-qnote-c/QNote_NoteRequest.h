/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#ifndef QDM_QNOTE_NOTEREQUEST_H_
#define QDM_QNOTE_NOTEREQUEST_H_

#include <qeo/types.h>
#include "qeo_types.h"


typedef struct {
    /**
     * Unique ID of the note request. This ID will be a randomly generated integer and should be unique for all running QNote applications. It is very important that the ID is chosen by the client application because it is necessary to indicate what kind of action the NoteRequest represents.
     */
    int32_t id;
    /**
     * Unique ID of the wall where this request is addressed to. Combined with the ID of the NoteRequest, it will be used to indicate what kind of action this request represents. If the Wall that receives the request has the same Wall ID as the NoteRequest it will either be a note creation (if the wall does not have a note with the given ID yet) or a modification (if the wall already has a note with the given ID). If the Wall ID of the request does not match the ID of the receiving wall the wall should delete it (if the wall has a note with the same note ID) or ignore it (if it doesn't have a note with a matching ID).
     */
    int32_t wallId;
    /**
     * The content of the note.
     */
    char * message;
} org_qeo_sample_note_NoteRequest_t;
extern const DDS_TypeSupport_meta org_qeo_sample_note_NoteRequest_type[];


#endif /* QDM_QNOTE_NOTEREQUEST_H_ */

