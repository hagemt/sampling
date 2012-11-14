#include <assert.h>
#include <stdlib.h>

#include <ao/ao.h>

extern ao_sample_format format;

#include "composer.h"

int
main(void)
{
	char *sound_data = DATA(FORMAT_RATE);
	/* Setup device format */
	assert(format.bits     == FORMAT_BITS);
	assert(format.channels == FORMAT_CHANNELS);
	assert(format.rate     == FORMAT_RATE);
	/* Play random samples */
	if (sound_data) {
		ao_initialize();
		play_sampled(sound_data, FORMAT_RATE);
		/* FFT sound_data and play it */
		free(sound_data);
		ao_shutdown();
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
