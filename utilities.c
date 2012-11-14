#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "composer.h"

void
__log_print (int code, const char *tag, const char *fmt, ...)
{
	va_list args;
	const char *str;
	switch (code) {
		case LOG_LEVEL_D: str = "debug";   break;
		case LOG_LEVEL_I: str = "info";    break;
		case LOG_LEVEL_W: str = "warning"; break;
		case LOG_LEVEL_E: str = "error";   break;
		case LOG_LEVEL_F: str = "fatal";   break;
		default:                str = "verbose";
	}
	fprintf(stderr, "[%s] %s: ", tag, str);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}


inline int
__fetch_driver (void)
{
	int id = ao_default_driver_id();
	if (id < 0) { id = 0; }
	LOGI("%i (sound driver initialized)", id);
	return id;
}

inline void *
__random_data (size_t len)
{
	int fd;
	size_t pos;
	ssize_t val;
	void *data = malloc(len);
	if (!data) {
		LOGE("malloc(%lu) (insufficient memory)", (long unsigned)(len));
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

