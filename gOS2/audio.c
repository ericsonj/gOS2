/*
 * audio.c
 *
 *  Created on: Apr 13, 2020
 *      Author: Ericson Joseph
 */

#include <gst/gst.h>
#include <stdio.h>
#include "audio.h"
#include "g_audiosrc.h"

static GMultimedia* media;
static AUDIO_Init_t _init;

void AUDIO_IN_Init(AUDIO_Init_t init){
	_init.BitsPerSample = init.BitsPerSample;
	_init.ChannelsNbr = init.ChannelsNbr;
	_init.SampleRate = init.SampleRate;
	_init.Volume = init.Volume;
}

void AUDIO_IN_DeInit(){
	/*g_multimedia_stop*/
}

void AUDIO_IN_Record(audio_record_callback func) {
	media = g_pcmaudiosrc_init(AUDIOSRC_FORMAT_S16LE, _init.SampleRate, _init.ChannelsNbr, (audio_callback)func);
	g_multimedia_start("AUDIO_IN", media);
}
