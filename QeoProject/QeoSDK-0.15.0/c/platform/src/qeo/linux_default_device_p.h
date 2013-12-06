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

#ifndef LINUX_DEFAULT_DEVICE_P_H_
#define LINUX_DEFAULT_DEVICE_P_H_
/*#######################################################################
# HEADER (INCLUDE) SECTION                                               #
########################################################################*/
#include <qeo/device.h>

/*#######################################################################
 # TYPES SECTION                                                         #
 ########################################################################*/
/*########################################################################
#                       API FUNCTION SECTION                             #
########################################################################*/
const qeo_platform_device_info *get_default_device_info(void);
void free_default_device_info(void);
const char *get_default_device_storage_path(void);
void free_default_device_storage_path(void);
#endif
