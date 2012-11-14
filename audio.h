#ifndef AUDIO_H
#define AUDIO_H

#include <stddef.h>

void play_sampled(char *, size_t);

#define FORMAT_BITS    16
#define FORMAT_CHANNELS 1
#define FORMAT_RATE 44100

#endif /* AUDIO_H */
