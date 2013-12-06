/************* COPYRIGHT AND CONFIDENTIALITY INFORMATION *********************
 **                                                                          **
 ** Copyright (c) 2012 Technicolor                                           **
 ** All Rights Reserved                                                      **
 **                                                                          **
 ** This program contains proprietary information which is a trade           **
 ** secret of TECHNICOLOR and/or its affiliates and also is protected as     **
 ** an unpublished work under applicable Copyright laws. Recipient is        **
 ** to retain this program in confidence and is not permitted to use or      **
 ** make copies thereof other than as permitted in a written agreement       **
 ** with TECHNICOLOR, UNLESS OTHERWISE EXPRESSLY ALLOWED BY APPLICABLE LAWS. **
 **                                                                          **
 ******************************************************************************/

/*#######################################################################
 #  HEADER (INCLUDE) SECTION                                             #
 ########################################################################*/
#include <qeo/api.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include "QNote_Note.h"
#include "QNote_NoteRequest.h"
#include "QNote_Wall.h"


/*#######################################################################
 #                           TYPES SECTION                               #
 ########################################################################*/

/* The data structure */
typedef enum
{
    WALL_TOPIC_COOKIE, NOTE_TOPIC_COOKIE, NOTE_REQUEST_TOPIC_COOKIE
} topic_cookie_t;

typedef struct
{
    int32_t id;
    bool found;
} note_found_t;


/*#######################################################################
 #  STATIC FUNCTION DECLARATION                                          #
 ########################################################################*/

static qeo_iterate_action_t find_note_cb(const void *data, uintptr_t userdata); /* \see ::qeo_iterate_callback */
static void on_note_request(const qeo_event_reader_t *reader, const void *data, uintptr_t userdata); /* \see ::qeo_on_data_callback */
static qeo_iterate_action_t on_iterate_notes(const void *data, uintptr_t userdata); /* \see ::qeo_iterate_callback */
static void on_note_update(const qeo_state_reader_t *reader, uintptr_t userdata); /* \see ::qeo_on_update_callback */
static qeo_iterate_action_t on_iterate_walls(const void *data, uintptr_t userdata); /* \see ::qeo_iterate_callback */
static void on_wall_update(const qeo_state_reader_t *reader, uintptr_t userdata); /* \see ::qeo_on_update_callback */

static qeo_retcode_t init_all();
static void interrupt_handler(int dummy);
static void cleanup(void);

/*#######################################################################
 #  STATIC VARIABLE SECTION                                              #
 ########################################################################*/

static bool _keep_running = true;

static qeo_factory_t *_qeo_fac = NULL;
static qeo_state_writer_t *_wallwriter = NULL;
static qeo_state_reader_t *_wallreader = NULL;

static qeo_state_reader_t *_notereader = NULL;
static qeo_state_writer_t *_notewriter = NULL;

static qeo_event_reader_t *_noterequestreader = NULL;
static qeo_event_writer_t *_noterequestwriter = NULL; /* Unused for the moment */

static org_qeo_sample_note_Wall_t _wall;

static qeo_state_reader_listener_t _note_topic_cbs = { .on_update = on_note_update };

static qeo_state_reader_listener_t _wall_topic_cbs = { .on_update = on_wall_update };

static qeo_event_reader_listener_t _note_request_cbs = { .on_data = on_note_request };

/*#######################################################################
 #  STATIC FUNCTION IMPLEMENTATION                                       #
 ########################################################################*/

static qeo_iterate_action_t find_note_cb(const void *data, uintptr_t userdata)
{
    org_qeo_sample_note_Note_t *note = (org_qeo_sample_note_Note_t *)data;
    note_found_t *found = (note_found_t *)userdata;

    if ((found->id == note->id) && (_wall.id == note->wallId)) {
        found->found = true;
        return QEO_ITERATE_ABORT;
    }

    return QEO_ITERATE_CONTINUE;
}

static void on_note_request(const qeo_event_reader_t *reader, const void *data, uintptr_t userdata)
{
    org_qeo_sample_note_NoteRequest_t *nr = (org_qeo_sample_note_NoteRequest_t *)data;
    org_qeo_sample_note_Note_t *note = calloc(1, sizeof(org_qeo_sample_note_Note_t));

    note_found_t nf = { .id = nr->id, .found = false };

    if (nr->wallId != _wall.id) {

        qeo_state_reader_foreach(_notereader, &find_note_cb, (uintptr_t)(&nf));

        if (nf.found) {
            /*
             * We are the owners of this note.
             * Type = Deletion
             */
            note->id = nr->id;
            note->wallId = _wall.id;

            qeo_state_writer_remove(_notewriter, note);
        }

        /* Type = Ignore */
        free(note->message);
        free(note);
        return;
    }
    else {
        /*This note request is addressed to our wall.*/

        qeo_state_reader_foreach(_notereader, &find_note_cb, (uintptr_t)(&nf));

        if (nf.found == false) {
            /*
             * The note was not found on our own wall.
             * Type = Creation
             */

            note->id = nr->id;
            note->wallId = _wall.id;
            note->message = strdup(nr->message);

            qeo_state_writer_write(_notewriter, note);
        }
        else {
            /*
             * The note already exists on our own wall.
             * Type = Modification
             */

            note->id = nr->id;
            note->wallId = _wall.id;
            note->message = strdup(nr->message);

            qeo_state_writer_write(_notewriter, note);
        }
    }

    free(note->message);
    free(note);
}

static qeo_iterate_action_t on_iterate_notes(const void *data, uintptr_t userdata)
{
    org_qeo_sample_note_Note_t *note = (org_qeo_sample_note_Note_t *)data;

    fprintf(stdout, "\nNote ID: %" PRId32 " Wall ID: %" PRId32 " Content: %s\r\n", note->id, note->wallId, note->message);

    return QEO_ITERATE_CONTINUE;
}

static void on_note_update(const qeo_state_reader_t *reader, uintptr_t userdata)
{
    fprintf(stdout, "\nA note topic was created or updated !\r\n");

    qeo_state_reader_foreach(reader, &on_iterate_notes, (uintptr_t)_wall.id);
}

static qeo_iterate_action_t on_iterate_walls(const void *data, uintptr_t userdata)
{
    org_qeo_sample_note_Wall_t *wall = (org_qeo_sample_note_Wall_t *)data;

    fprintf(stdout, "\nWall ID: %" PRId32 " Desc: %s\r\n", wall->id, wall->description);

    return QEO_ITERATE_CONTINUE;
}

static void on_wall_update(const qeo_state_reader_t *reader, uintptr_t userdata)
{
    fprintf(stdout, "\nA wall was created or updated !\r\n");

    fprintf(stdout, "Walls are:\r\n");

    qeo_state_reader_foreach(reader, &on_iterate_walls, userdata);
}

static qeo_retcode_t init_all()
{
    int rc = EXIT_SUCCESS;

    do {
        _qeo_fac = qeo_factory_create();

        if (_qeo_fac == NULL) {
            fprintf(stderr, "\nFactory construction has failed\n");
            rc = EXIT_FAILURE;
            break;
        }

        _wallreader = qeo_factory_create_state_reader(_qeo_fac, org_qeo_sample_note_Wall_type, &_wall_topic_cbs,
                                                      (uintptr_t)WALL_TOPIC_COOKIE);
        _wallwriter = qeo_factory_create_state_writer(_qeo_fac, org_qeo_sample_note_Wall_type, NULL, 0);

        if (_wallreader == NULL || _wallwriter == NULL) {
            fprintf(stderr, "\nCould not create wall reader or writer\n");
            rc = EXIT_FAILURE;
            break;
        }

        _notereader = qeo_factory_create_state_reader(_qeo_fac, org_qeo_sample_note_Note_type, &_note_topic_cbs,
                                                      (uintptr_t)NOTE_TOPIC_COOKIE);
        _notewriter = qeo_factory_create_state_writer(_qeo_fac, org_qeo_sample_note_Note_type, NULL, 0);

        if (_notereader == NULL || _notewriter == NULL) {
            fprintf(stderr, "\nCould not create note reader or writer\n");
            rc = EXIT_FAILURE;
            break;
        }

        _noterequestreader = qeo_factory_create_event_reader(_qeo_fac, org_qeo_sample_note_NoteRequest_type, &_note_request_cbs,
                                                             (uintptr_t)NOTE_REQUEST_TOPIC_COOKIE);
        _noterequestwriter = qeo_factory_create_event_writer(_qeo_fac, org_qeo_sample_note_NoteRequest_type, NULL, 0);

        if (_noterequestreader == NULL || _noterequestwriter == NULL) {
            fprintf(stderr, "\nCould not create note request reader or writer\n");
            rc = EXIT_FAILURE;
        }

    } while (0);

    if (rc == EXIT_FAILURE) {
        cleanup();
    }

    return rc;

}

static void interrupt_handler(int dummy)
{
    _keep_running = false;
}

static void cleanup(void)
{

    fprintf(stdout, "\nCleaning up...\r\n");
    qeo_event_reader_close(_noterequestreader);
    qeo_event_writer_close(_noterequestwriter);
    _noterequestreader = NULL;
    _noterequestwriter = NULL;

    qeo_state_reader_close(_notereader);
    qeo_state_writer_close(_notewriter);
    _notereader = NULL;
    _notewriter = NULL;

    qeo_state_reader_close(_wallreader);
    qeo_state_writer_close(_wallwriter);
    _wallreader = NULL;
    _wallwriter = NULL;

    if (_qeo_fac != NULL) {
        qeo_factory_close(_qeo_fac);
        _qeo_fac = NULL;
    }

}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    int32_t rc = EXIT_SUCCESS;

    int32_t arg1check;
    int32_t arg2check;

    char id[11];
    char desc[30];

    do {

        if (argc != 3) {
            fprintf(stderr, "\nUsage: %s <wall id> <wall description>\n", argv[0]);
            rc = EXIT_FAILURE;
            break;
        }

        arg1check = snprintf(desc, 30, "%s", argv[2]);
        arg2check = snprintf(id, 11, "%s", argv[1]);

        if (arg1check < 0 || arg2check < 0) {
            fprintf(stderr, "\nCould not create your wall\n");
            rc = EXIT_FAILURE;
            break;
        }
        else {
            _wall.id = (int32_t)atoi(id);
            _wall.description = desc;
        }

        if (init_all() == EXIT_FAILURE) {
            fprintf(stderr, "\nInitialization has failed !\n");
            rc = EXIT_FAILURE;
            break;
        }

        signal(SIGINT, interrupt_handler);

        if (QEO_OK == qeo_state_writer_write(_wallwriter, &_wall)) {
            fprintf(stdout, "\nOur wall (%s) was created !\r\n", _wall.description);
        }
        else {
            fprintf(stderr, "\nOur wall (%s) was not created !\n", _wall.description);
        }

        while (_keep_running) {
            sleep(60); /* ctrl-c will interrupt sleep anyway */
        }

    } while (0);

    cleanup();

    return rc;
}
