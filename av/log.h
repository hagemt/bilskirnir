#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

/* tags help users identify context */
#ifdef NDEBUG
#define LOG_TAG "composer"
#else /* DEBUG */
#define LOG_TAG __PRETTY_FUNCTION__
#endif /* NDEBUG */

/* priorities allow logical filters */
#define LOG_LEVEL_0 0x00
#define LOG_LEVEL_1 0x01
#define LOG_LEVEL_4 0x04
#define LOG_LEVEL_7 0x07
#define LOG_LEVEL_E 0x0E
#define LOG_LEVEL_F 0x0F

typedef enum {
	LOG_LEVEL_VERBOSE = LOG_LEVEL_0,
	LOG_LEVEL_DEBUG   = LOG_LEVEL_1,
	LOG_LEVEL_INFO    = LOG_LEVEL_4,
	LOG_LEVEL_WARNING = LOG_LEVEL_7,
	LOG_LEVEL_ERROR   = LOG_LEVEL_E,
	LOG_LEVEL_FATAL   = LOG_LEVEL_F
} log_level_t;

#define LOG_LEVEL_QUIET  LOG_LEVEL_FATAL
#define LOG_LEVEL_NORMAL LOG_LEVEL_WARNING
#define LOG_LEVEL_LOUD   LOG_LEVEL_VERBOSE

typedef struct {
	log_level_t level;
} log_data_t;

/* We can manipulate how logging functions */
const char *get_log_label(log_level_t);
void set_log_level(log_level_t);
void set_log(log_data_t *);

/* but this is the real heavy lifter */
#include "utilities.h"
#define LOG(CODE,TAG,...) __println(get_log_label(CODE),TAG,__VA_ARGS__)

/* shortcuts for easy logging */
#define LOGV(...) LOG(LOG_LEVEL_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGD(...) LOG(LOG_LEVEL_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...) LOG(LOG_LEVEL_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...) LOG(LOG_LEVEL_WARNING,LOG_TAG,__VA_ARGS__)
#define LOGE(...) LOG(LOG_LEVEL_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...) LOG(LOG_LEVEL_FATAL,LOG_TAG,__VA_ARGS__)

#ifdef __cplusplus
} /* extern "C" */
#endif /* C++ */

#endif /* LOG_H */
