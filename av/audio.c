#include <assert.h>

#include <ao/ao.h>
#include <sndfile.h>

#include "audio.h"
#include "log.h"
#include "utilities.h"

ao_sample_format ao_format = {
	FORMAT_BITS,
	FORMAT_RATE,
	FORMAT_CHANNELS,
	AO_FMT_NATIVE,
};

SF_INFO sf_format = {
	FORMAT_BITS,
	FORMAT_RATE,
	FORMAT_CHANNELS,
	SF_FORMAT_WAV | SF_FORMAT_DOUBLE | SF_ENDIAN_CPU,
	1,
	0,
};

void
play_sampled (void *data, size_t len)
{
	ao_device *device = ao_open_live(DEFAULT, &ao_format, NULL);
	if (!device) {
		LOGE("%i (could not open audio device)", DEFAULT);
		return;
	}
	if (!ao_play(device, (char *) (data), len)) {
		LOGE("%p (device could not play sample)", (void *) (device));
	}
	if (!ao_close(device)) {
		LOGW("%p (could not close audio device)", (void *) (device));
	}
}

void
save_sampled (void *data, size_t len, const char *path)
{
	double *dp;
	SNDFILE *fp;
	size_t total;
	sf_count_t chunk;

	/* sanitize inputs */
	if (!path) {
		LOGE("%s (is not a valid path)", path);
		return;
	}
	if (!(dp = data)) {
		LOGW("%s (no sample data to save)", path);
		return;
	}

	/* write samples to file in chunks */
	if ((fp = sf_open(path, SFM_WRITE, &sf_format)) != NULL) {
		for (total = chunk = 0; total < len; total += chunk) {
			chunk = sf_writef_double(fp, dp++, sizeof(double));
			assert(chunk > 0);
		}
		LOGI("%s (wrote %lu bytes to file)", path, (long unsigned) (total));
		sf_write_sync(fp);
		/* try to cleanup */
		if (sf_close(fp)) {
			LOGW("%p (could not close sndfile)", (void *) (fp));
		}
	}
}
