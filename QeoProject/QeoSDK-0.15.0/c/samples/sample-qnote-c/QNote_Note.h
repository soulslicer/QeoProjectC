/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#ifndef QDM_QNOTE_NOTE_H_
#define QDM_QNOTE_NOTE_H_

#include <qeo/types.h>
#include "qeo_types.h"


typedef struct {
    /**
     * [Key] Unique ID of every note. This ID is a random generated number by the client.
     */
    int32_t id;
    /**
     * [Key] Unique ID of the wall to which this note belongs
     */
    int32_t wallId;
    /**
     * The content of the note
     */
    char * message;
} org_qeo_sample_note_Note_t;
extern const DDS_TypeSupport_meta org_qeo_sample_note_Note_type[];


#endif /* QDM_QNOTE_NOTE_H_ */

