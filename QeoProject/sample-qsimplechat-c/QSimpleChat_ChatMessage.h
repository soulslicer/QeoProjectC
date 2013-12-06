/**************************************************************
 ********          THIS IS A GENERATED FILE         ***********
 **************************************************************/

#ifndef QDM_QSIMPLECHAT_CHATMESSAGE_H_
#define QDM_QSIMPLECHAT_CHATMESSAGE_H_

#include <qeo/types.h>


/**
 * A simple chat message.
 */
typedef struct {
    /**
     * The user sending the message.
     */
    char * from;
    /**
     * The message.
     */
    char * message;
} org_qeo_sample_simplechat_ChatMessage_t;
extern const DDS_TypeSupport_meta org_qeo_sample_simplechat_ChatMessage_type[];


#endif /* QDM_QSIMPLECHAT_CHATMESSAGE_H_ */

