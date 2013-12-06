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

/** \file
 * Qeo internal return and error codes.
 */

#ifndef QEO_UTIL_ERROR_H_
#define QEO_UTIL_ERROR_H_

/**
 * Qeo internal return codes.
 */
typedef enum {
    QEO_UTIL_OK,                    /**< success */
    QEO_UTIL_EFAIL,                 /**< failure */
    QEO_UTIL_ENOMEM,                /**< out of memory */
    QEO_UTIL_EINVAL,                /**< invalid arguments */
    QEO_UTIL_ENODATA,               /**< no more data */
    QEO_UTIL_EBADSTATE,             /**< invalid state for operation */
    QEO_UTIL_ENOTSUPPORTED,         /**< particular functionality is not (yet) supported */
    QEO_UTIL_ENOTIMPLEMENTED,       /**< function is not implemented */
} qeo_util_retcode_t;

#endif /* QEO_UTIL_ERROR_H_ */
