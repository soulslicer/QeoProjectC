/************** COPYRIGHT AND CONFIDENTIALITY INFORMATION *********************
 **                                                                          **
 ** Copyright (c) 2013 Technicolor                                           **
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

#ifndef FACTORY_H_
#define FACTORY_H_

#include <qeo/types.h>

/* ===[ Qeo factory ]======================================================== */

/// \name Qeo Factory
/// \{

/**
 * Returns a Qeo factory instance for the default realm that can be used for
 * creating Qeo readers and writers.  The factory instance should be properly
 * closed if none of the readers and/or writers that have been created, are
 * needed anymore.  This will free any allocated resources associated with that
 * factory.
 *
 * \return The factory or \c NULL on failure.
 *
 * \see ::qeo_factory_close
 */
qeo_factory_t *qeo_factory_create();

/**
 * Returns a Qeo factory instance that can be used for creating Qeo readers and
 * writers.  The factory instance should be properly closed if none of the
 * readers and/or writers that have been created, are needed anymore.  This will
 * free any allocated resources associated with that factory.
 *
 * \param[in] id  The identity for which you want to create the factory.
 *                Use QEO_IDENTITY_DEFAULT for the default identity.
 *
 * \return The factory or \c NULL on failure.
 *
 * \see ::qeo_factory_close
 */
qeo_factory_t *qeo_factory_create_by_id(const qeo_identity_t *id);

/**
 * Close the factory and release any resources associated with it.
 *
 * \warning Make sure that any readers and/or writers created with this factory
 *          have been closed before calling this function.
 *
 * \param[in] factory  The factory to be closed.
 */
void qeo_factory_close(qeo_factory_t *factory);

/// \}


#endif /* FACTORY_H_ */
