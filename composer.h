#ifndef COMPOSER_H
#define COMPOSER_H

/**
 * for FFT
 */

#ifdef __GNUC__
#define FFT_RESTRICT __restrict__
#else /* ! __GNUC__ */
#define FFT_RESTRICT restrict
#endif /* __GNUC__ */
/* __attribute__ ((visibility ("hidden"))) */
/* #define FFT_EXPORT export */
/* #define FFT_INLINE __inline__ */

#include <complex.h>
#include <math.h>

#ifndef FFT_TYPE
#define FFT_TYPE
typedef complex double fft_t;
#endif /* FFT_TYPE */

inline int fft(fft_t *, size_t, fft_t *);

#define FFT_NEG_TWO_PI_I (-2 * M_PI * _Complex_I)

/**
 * for audio
 */

#include <ao/ao.h>

/* TODO: extern ao_sample_format format; */

void play_sampled(char *, size_t);

#define FORMAT_BITS    16
#define FORMAT_CHANNELS 1
#define FORMAT_RATE 44100

/**
 * for plumbing utilities
 */

inline int __get_device(void);
inline void *__random_data(size_t);
void __log_print(int, const char *, const char *, ...);

#define DATA(x) __random_data(x)
#define DEVICE __get_device()
#define LOG(LEVEL,TAG,...) __log_print(LEVEL,TAG,__VA_ARGS__)

#ifdef NDEBUG
#define LOG_TAG "composer"
#else /* DEBUG */
#define LOG_TAG __PRETTY_FUNCTION__
#endif /* NDEBUG */
#define LOG_LEVEL_V 0x0000
#define LOG_LEVEL_D 0x0001
#define LOG_LEVEL_I 0x0002
#define LOG_LEVEL_W 0x0004
#define LOG_LEVEL_E 0x0008
#define LOG_LEVEL_F 0xFFFF

#define LOGV(...) LOG(LOG_LEVEL_V,LOG_TAG,__VA_ARGS__)
#define LOGD(...) LOG(LOG_LEVEL_D,LOG_TAG,__VA_ARGS__)
#define LOGI(...) LOG(LOG_LEVEL_I,LOG_TAG,__VA_ARGS__)
#define LOGW(...) LOG(LOG_LEVEL_W,LOG_TAG,__VA_ARGS__)
#define LOGE(...) LOG(LOG_LEVEL_E,LOG_TAG,__VA_ARGS__)
#define LOGF(...) LOG(LOG_LEVEL_F,LOG_TAG,__VA_ARGS__)

#define RANDOM_SOURCE "/dev/urandom"

#endif /* COMPOSER_H */
