#include "composer.h"

static ao_sample_format format = {
	FORMAT_BITS,
	FORMAT_RATE,
	FORMAT_CHANNELS,
	AO_FMT_NATIVE,
};

void
play_sampled (char *data, size_t len)
{
	ao_device *device = ao_open_live(DEVICE, &format, NULL);
	if (!device) {
		LOGE("%i (count not open audio device)", DEVICE);
		return;
	}
	if (!ao_play(device, data, len)) {
		LOGE("%p (device could not play samples)", (void *) (device));
	}
	if (!ao_close(device)) {
		LOGW("%p (cannot ao_close device)", (void *) (device));
	}
}
