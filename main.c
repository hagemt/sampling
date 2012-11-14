#include <assert.h>
#include <stdlib.h>

#include "main.h"

#define SAMPLES (FORMAT_RATE << 3)
#define N 8192

int
main(void)
{
	fft_t trans_data[N];
	char *sound_data = DATA(SAMPLES);
	assert(format.bits     == FORMAT_BITS);
	assert(format.channels == FORMAT_CHANNELS);
	assert(format.rate     == FORMAT_RATE);
	if (sound_data) {
		/* Setup sound system */
		ao_initialize();
		/* Play random samples */
		play_sampled(sound_data, SAMPLES);
		/* Compute the FFT */
		fft((fft_t *) (sound_data), N, trans_data);
		play_sampled((char *) (trans_data), sizeof(trans_data));
		/* Cleanup */
		free(sound_data);
		ao_shutdown();
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
