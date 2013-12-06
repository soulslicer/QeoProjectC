/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#ifndef QDM_QNOTE_WALL_H_
#define QDM_QNOTE_WALL_H_

#include <qeo/types.h>
#include "qeo_types.h"


typedef struct {
    /**
     * [Key] Unique ID of the wall. This is a randomly generated number by the Wall.
     */
    int32_t id;
    /**
     * Description of the wall (e.g kitchen wall)
     */
    char * description;
} org_qeo_sample_note_Wall_t;
extern const DDS_TypeSupport_meta org_qeo_sample_note_Wall_type[];


#endif /* QDM_QNOTE_WALL_H_ */

