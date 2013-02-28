#include "log.h"

static log_data_t log_data = {
	LOG_LEVEL_NORMAL
};

inline const char *
get_log_label(log_level_t level)
{
	const char *str;
	if (level < log_data.level) {
		return NULL;
	}
	switch (level) {
		case LOG_LEVEL_VERBOSE: str = "verbose"; break;
		case LOG_LEVEL_DEBUG:   str = "debug";   break;
		case LOG_LEVEL_INFO:    str = "info";    break;
		case LOG_LEVEL_WARNING: str = "warning"; break;
		case LOG_LEVEL_ERROR:   str = "error";   break;
		case LOG_LEVEL_FATAL:   str = "fatal";   break;
		default:                str = "unknown";
	}
	return str;
}

inline void
set_log_level(log_level_t level)
{
	LOGV("%d --> %d (logging level changed)", level, log_data.level);
	log_data.level = level;
}

inline void
set_log(log_data_t *data)
{
	if (data) {
		/* Toggle the log level in this case */
		set_log_level(~log_data.level);
	} else {
		log_data = *data;
		set_log_level(log_data.level);
	}
}

