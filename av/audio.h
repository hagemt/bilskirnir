#ifndef AUDIO_H
#define AUDIO_H

#include <stddef.h>

void play_sampled(void *, size_t);
void save_sampled(void *, size_t, const char *);

#define FORMAT_BITS    16
#define FORMAT_CHANNELS 1
#define FORMAT_RATE 44100

#endif /* AUDIO_H */
