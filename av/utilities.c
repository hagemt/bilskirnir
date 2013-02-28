#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ao/ao.h>

#include "log.h"
#include "utilities.h"

extern log_data_t log_data;

inline void
__println (const char *type, const char *tag, const char *fmt, ...)
{
	va_list args;
	if (!type || !tag || !fmt) {
		#ifndef NDEBUG
		LOGW("%p (caught bad log attempt)", &log_data);
		#endif /* DEBUG */
		return;
	}
	fprintf(stderr, "[%s] %s: ", tag, type);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}

inline int
__default_driver (void)
{
	int id = ao_default_driver_id();
	if (id < 0) { id = 0; }
	LOGI("%i (sound driver initialized)", id);
	return id;
}

#define RANDOM_SOURCE "/dev/urandom"

inline void *
__random_data (size_t len)
{
	int fd;
	size_t pos;
	ssize_t val;
	void *data = malloc(len);
	if (!data) {
		LOGF("malloc(%lu) (insufficient memory)", (long unsigned)(len));
		return NULL;
	}
	/* Read in random bytes to play as sound */
	if ((fd = open(RANDOM_SOURCE, O_RDONLY)) < 0) {
		LOGE("%s (cannot open file)", RANDOM_SOURCE);
	} else if ((val = read(fd, data, len)) < 0) {
		LOGE("%s (cannot read file)", RANDOM_SOURCE);
	} else {
		pos = (size_t)(val);
		LOGI("%s (%lu byte(s) read)", RANDOM_SOURCE, (long unsigned)(pos));
		if (pos != len) {
			LOGW("%lu (byte(s) missing)", (long unsigned)(len - pos));
		}
		if (close(fd)) {
			LOGW("%s (cannot close file)", RANDOM_SOURCE);
		}
	}
	return data;
}

