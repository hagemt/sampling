#include <assert.h>
#include <stdlib.h>

#include "fft.h"
#include "utilities.h"

static void
__fft (input, len, stride, output)
	fft_t * FFT_RESTRICT input;
	size_t len, stride;
	fft_t * FFT_RESTRICT output;
{
	size_t half, twice;
	register size_t index;
	fft_t * FFT_RESTRICT left, * FFT_RESTRICT right, x, y;
	assert(input && output && input != output);
	/* base case, length 1 */
	if (len < 2) {
		*output = *input;
		return;
	}
	/* "half" is len / 2, "twice" is 2 * stride */
	half = (len >> 1);
	twice = (stride << 1);
	/* allocate memory */
	left = malloc(half * sizeof(fft_t));
	right = malloc(half * sizeof(fft_t));
	assert(left && right);
	/* compute FFTs of each half  */
	__fft(input       , half, twice, left);
	__fft(input + half, half, twice, right);
	/* combine the left and right */
	for (index = 0; index < half; ++index) {
		/* add twiddle factors to l[i] */
		x = left[index];
		/* +/- e^(-2 pi i / len) * r[i] */
		y = cexp(FFT_NEG_TWO_PI_I * index / len);
		/* combine the halves */
		output[index]        = x + y * right[index];
		output[index + half] = x - y * right[index];
	}
	/* cleanup memory */
	free(left);
	free(right);
}

inline int
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
	LOGE("%lu (power of two required for FFT length)", (long unsigned) (len));
	return EXIT_FAILURE;
}
