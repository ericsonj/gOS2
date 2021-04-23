/*
 * g_g711rtp.h
 *
 *  Created on: Apr 20, 2020
 *      Author: Ericson Joseph
 */

#ifndef RTPMOCK_G_G711RTP_H_
#define RTPMOCK_G_G711RTP_H_

#include <stdint.h>
#include "g_multimedia.h"


typedef void (*audio_callback)(uint8_t* data, uint32_t size, void *arg);

GMultimedia* g_g711rtp_init(audio_callback callback);

void g_g711rtp_start(GMultimedia* media);

#endif /* RTPMOCK_G_G711RTP_H_ */
