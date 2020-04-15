/*
 * audio.h
 *
 *  Created on: Apr 13, 2020
 *      Author: ericson
 */

#ifndef GOS2_AUDIO_H_
#define GOS2_AUDIO_H_

#include <stdint.h>

typedef struct {
	uint32_t Device;
	uint32_t SampleRate;
	uint32_t BitsPerSample;
	uint32_t ChannelsNbr;
	uint32_t Volume;
} AUDIO_Init_t ;


typedef void (*audio_record_callback)(uint8_t* pBuf, uint32_t NbrOfBytes);

void AUDIO_IN_Init(AUDIO_Init_t init);
void AUDIO_IN_DeInit();

void AUDIO_IN_Record(audio_record_callback func);

#endif /* GOS2_AUDIO_H_ */
