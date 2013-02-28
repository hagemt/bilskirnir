#include <assert.h>
#include <stdlib.h>

#include "main.h"

#define SAMPLES (FORMAT_RATE << 3)
#define N 8192

#define SOUND_FILE "composer.sound.wav"
#define TRANS_FILE "composer.trans.wav"

int
main(void)
{
	void *sound_data;
	fft_t trans_data[N];

	/* Check our parameters */
	#ifndef NDEBUG
	LOGV("sizeof(fft_t) = %lu", (long unsigned) sizeof(fft_t));
	assert(ao_format.bits     == FORMAT_BITS);
	assert(ao_format.channels == FORMAT_CHANNELS);
	assert(ao_format.rate     == FORMAT_RATE);
	assert(sf_format.frames     == FORMAT_BITS);
	assert(sf_format.samplerate == FORMAT_RATE);
	assert(sf_format.channels   == FORMAT_CHANNELS);
	#else /* DEBUG */
	set_log_level(LOG_LEVEL_QUIET);
	#endif /* !DEBUG */

	/* Process available data */
       	if ((sound_data = DATA(SAMPLES))) {
		/* Compute the FFT of the first N bytes */
		fft((fft_t *) (sound_data), N, trans_data);
		save_sampled(sound_data, N, SOUND_FILE);
		save_sampled(trans_data, sizeof(trans_data), TRANS_FILE);
		/* Use the sound system to play samples */
		ao_initialize();
		play_sampled(sound_data, SAMPLES);
		play_sampled((char *) (trans_data), sizeof(trans_data));
		ao_shutdown();
		/* Cleanup memory */
		free(sound_data);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
