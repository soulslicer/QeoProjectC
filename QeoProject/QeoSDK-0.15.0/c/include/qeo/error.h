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
 * Qeo return and error codes.
 */

#ifndef QEO_ERROR_H_
#define QEO_ERROR_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Qeo return codes.
 */
typedef enum {
    QEO_OK,                    /**< success */
    QEO_EFAIL,                 /**< failure */
    QEO_ENOMEM,                /**< out of memory */
    QEO_EINVAL,                /**< invalid arguments */
    QEO_ENODATA,               /**< no more data */
    QEO_EBADSTATE,             /**< invalid state for operation */
} qeo_retcode_t;

#ifdef __cplusplus
}
#endif

#endif /* QEO_ERROR_H_ */
