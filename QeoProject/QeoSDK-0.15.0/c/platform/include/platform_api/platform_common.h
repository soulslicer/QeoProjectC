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
 * Qeo device API common (private).
 */

#ifndef QEO_PLATFORM_COMMON_H_
#define QEO_PLATFORM_COMMON_H_

#include <qeo/device.h>
#include <qeo/platform_security.h>


/**
 * This function prints the device info struct in a pretty manner.
 *
 * \param[in] qeo_dev_info a pointer to a qeo_platform_device_info struct
 */
void qeo_pprint_device_info(const qeo_platform_device_info* qeo_dev_info);

/**
 * Returns a human-readable version of the qeo_platform_security_state
 *
 */
const char *platform_security_state_to_string(qeo_platform_security_state state);

/**
 * Returns a human-readable version of the qeo_platform_security_state_reason
 *
 */
const char *platform_security_state_reason_to_string(qeo_platform_security_state_reason reason);

/**
 * Like strdup but will return NULL if NULL is passed as an argument (rather than crashing) 
 *
 */
char* qeo_strdup_ret(const char* ret_str);
#endif /* QEO_PLATFORM_COMMON_H_ */
