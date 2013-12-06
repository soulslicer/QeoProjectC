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
 * Qeo Platform API.
 */

#ifndef QEO_PLATFORM_H_
#define QEO_PLATFORM_H_
#include <qeo/util_error.h>

/**
* Get the full storage path given a file name to store your file.
* It is the responsibility of the caller to free full_storage_path.
*
* \param[in]  file_name a pointer to a file name string
* \param[out] full_storage_path a pointer to a full storage path pointer
*
* \retval ::QEO_OK on success
* \retval ::QEO_EINVAL in case of invalid arguments
* \retval ::QEO_ENOMEM in case it failed to allocate memory for the output
* */
qeo_util_retcode_t qeo_platform_get_device_storage_path(const char* file_name, char** full_storage_path);

/**
 * This function will set a key with it's value in the persistent storage framework
 *
 * \param[in] key the unique identifier of the data
 * \param[in] value The value beloning to the key
 *
 */
qeo_util_retcode_t qeo_platform_set_key_value(const char *key, char *value); 

/**
 * This function will get the value belonging to a key from the persistent storage framework
 *
 * \param[in] key the unique identifier of the data
 * \param[in] value The value beloning to the key
 *
 */
qeo_util_retcode_t qeo_platform_get_key_value(const char *key, char **value); 

#endif 
