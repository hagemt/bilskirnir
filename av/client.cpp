#include <cassert>
#include <cstdlib>
#include <string>

#include "main.h"
#include "settings.h"

static Settings options;

#define SAMPLES (FORMAT_RATE << 3)
#define N 8192

#define SOUND_FILE "composer.sound.wav"
#define TRANS_FILE "composer.trans.wav"

int
main(int argc, char *argv[])
{
	void *sound_data;
	fft_t trans_data[N];

	#ifdef NDEBUG
	set_log_level(LOG_LEVEL_QUIET);
	#else /* DEBUG */
	// Step 0: Check our parameters
	LOGV("sizeof(fft_t) = %lu", (long unsigned) sizeof(fft_t));
	assert(ao_format.bits     == FORMAT_BITS);
	assert(ao_format.channels == FORMAT_CHANNELS);
	assert(ao_format.rate     == FORMAT_RATE);
	assert(sf_format.frames     == FORMAT_BITS);
	assert(sf_format.samplerate == FORMAT_RATE);
	assert(sf_format.channels   == FORMAT_CHANNELS);
	#endif /* DEBUG */

	// Step 1: Load options from the command-line
	options.add_switch("quiet", "Disable most console output");
	options.add_switch("verbose", "Enable full console output");
	options.parse(argc, argv);
	if (options.value<bool>("verbose")) {
		set_log_level(LOG_LEVEL_LOUD);
	}
	if (options.value<bool>("quiet")) {
		set_log(false);
	}

	// Step 2: Process available data
	if ((sound_data = DATA(SAMPLES))) {
		// Compute the FFT of the first N bytes
		fft((fft_t *) (sound_data), N, trans_data);
		save_sampled(sound_data, N, SOUND_FILE);
		save_sampled(trans_data, sizeof(trans_data), TRANS_FILE);
		// Use the sound system to play samples
		ao_initialize();
		play_sampled(sound_data, SAMPLES);
		play_sampled((char *) (trans_data), sizeof(trans_data));
		ao_shutdown();
		free(sound_data);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
