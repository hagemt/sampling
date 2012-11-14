#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include "composer.h"

static void
__fft (input, len, offset, output)
	fft_t * FFT_RESTRICT input;
	size_t len, offset;
	fft_t * FFT_RESTRICT output;
{
	size_t half, twice;
	register size_t index;
	fft_t * FFT_RESTRICT left, * __restrict__ right, x, y;
	assert(input && output && input != output);
	/* base case, length 1 */
	if (len < 2) {
		*output = *input;
		return;
	}
	/* "half" is len / 2, "twice" is 2 * offset */
	half = (len >> 1);
	twice = (offset << 1);
	/* produce left and right solutions */
	left = malloc(half * sizeof(fft_t));
	right = malloc(half * sizeof(fft_t));
	__fft(input, half, len, left);
	__fft(input + offset, half, offset, right);
	/* add twiddle factors */
	for (index = 0; index < half; ++index) {
		x = input[index];
		y = cexp(FFT_NEG_TWO_PI_I * index / len);
		/* l/r[i] = in[i] +/- e^(-2 pi i / len) * r[i] */
		left[index] = x + y * right[index];
		right[index] = x - y * right[index];
	}
	/* combine results */
	for (index = 0; index < half; ++index) {
		output[index] = left[index];
	}
	for (index = 0; index < half; ++index) {
		output[half + index] = right[index];
	}
	/* cleanup */
	free(left);
	free(right);
}

int
fft (input, len, output)
	fft_t * FFT_RESTRICT input;
	size_t len;
	fft_t * FFT_RESTRICT output;
{
	/* check that length is a power of two */
	if (len && (len & (~len + 1)) == len) {
		__fft(input, len, 1, output);
		return EXIT_SUCCESS;
	}
	LOGE("%lu (length for FFT must be power of two)", (long unsigned) (len));
	return EXIT_FAILURE;
}
