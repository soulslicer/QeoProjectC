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

#include <qeo/log.h>

#include <stdarg.h>
#include <stdio.h>
#ifdef ANDROID
#include <android/log.h>
static int _lvl2prio[] = { ANDROID_LOG_DEBUG, ANDROID_LOG_INFO, ANDROID_LOG_WARN, ANDROID_LOG_ERROR };
#else
static const char *_lvl2str[] = { "D", "I", "W", "E" };
#endif

static void default_logger(qeo_loglvl_t lvl, const char* fileName, const char* functionName, int lineNumber, const char *format, ...)
{
    va_list args;

    va_start(args, format);
#ifdef ANDROID
    char buf[512];
    int len = 0;
    len = snprintf(buf, sizeof(buf),"%s:%s:%d - ", fileName, functionName, lineNumber);
    vsnprintf(buf + len, sizeof(buf) - len,  format, args);
    __android_log_print(_lvl2prio[lvl], "QeoNative", "%s", buf);
#else
    printf("%s - %s:%s:%d - ", _lvl2str[lvl], fileName, functionName, lineNumber);
    vprintf(format, args);
    printf("\n");
#endif
    va_end(args);
}

qeo_logger_ptr qeo_logger = default_logger;

void qeo_log_set_logger(qeo_logger_ptr logger)
{
    qeo_logger = logger;
}
