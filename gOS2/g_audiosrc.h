/*
 * g_audiosrc.h
 *
 *  Created on: Apr 14, 2020
 *      Author: Ericson Joseph
 */

#ifndef GOS2_G_AUDIOSRC_H_
#define GOS2_G_AUDIOSRC_H_

#include "g_multimedia.h"

#define AUDIOSRC_FORMAT_S16LE   "S16LE"

#define AUDIORSC_RATE_8000 		8000
#define AUDIORSC_RATE_16000 	16000
#define AUDIORSC_RATE_32000 	32000
#define AUDIORSC_RATE_44100 	44100
#define AUDIORSC_RATE_48000 	48000
#define AUDIORSC_RATE_96000 	96000

#define AUDIOSRC_MONO_S16EL_8000(_callback_) g_pcmaudiosrc_init(AUDIOSRC_FORMAT_S16LE, AUDIORSC_RATE_8000, 1, _callback_)

typedef void (*audio_callback)(guint8* data, gsize size);

GMultimedia* g_pcmaudiosrc_init(const gchar* format, guint rate, gint channes, audio_callback callback);

void g_pcmaudiosrc_start(GMultimedia* media);

#endif /* GOS2_G_AUDIOSRC_H_ */
