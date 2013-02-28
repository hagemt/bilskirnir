#ifndef COMPOSER_H
#define COMPOSER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "audio.h"
#include "fft.h"
#include "log.h"
#include "utilities.h"

#include <ao/ao.h>
#include <sndfile.h>

extern ao_sample_format ao_format;
extern SF_INFO sf_format;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COMPOSER_H */
