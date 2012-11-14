#include <ao/ao.h>

#include "audio.h"
#include "utilities.h"

ao_sample_format format = {
	FORMAT_BITS,
	FORMAT_RATE,
	FORMAT_CHANNELS,
	AO_FMT_NATIVE,
};

void
play_sampled (char *data, size_t len)
{
	ao_device *device = ao_open_live(DEFAULT, &format, NULL);
	if (!device) {
		LOGE("%p (could not open audio device)", (void *) (device));
		return;
	}
	if (!ao_play(device, data, len)) {
		LOGE("%p (device could not play sample)", (void *) (device));
	}
	if (!ao_close(device)) {
		LOGW("%p (could not close audio device)", (void *) (device));
	}
}
