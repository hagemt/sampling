#ifndef FFT_H
#define FFT_H

#include <complex.h>
#include <math.h>
#include <stddef.h>

#ifdef __GNUC__
#define FFT_RESTRICT __restrict__
#else /* ! __GNUC__ */
#define FFT_RESTRICT restrict
#endif /* __GNUC__ */
/* __attribute__ ((visibility ("hidden"))) */
/* #define FFT_EXPORT export */
/* #define FFT_INLINE __inline__ */

#ifndef FFT_TYPE
#define FFT_TYPE
typedef complex double fft_t;
#endif /* FFT_TYPE */

inline int fft(fft_t *, size_t, fft_t *);

#define FFT_NEG_TWO_PI_I (-2 * M_PI * _Complex_I)

#endif /* FFT_H */
