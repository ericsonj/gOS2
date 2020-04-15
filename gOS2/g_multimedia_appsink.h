/*
 * g_multimedia_appsink.h
 *
 *  Created on: Apr 14, 2020
 *      Author: Ericson Joseph
 */

#ifndef GOS2_G_MULTIMEDIA_APPSINK_H_
#define GOS2_G_MULTIMEDIA_APPSINK_H_

#include <gst/gst.h>
#include "g_multimedia.h"

typedef void (*multimedia_callback)(guint8* data, gsize size);

GMultimedia* g_appsink_init(multimedia_callback callback, GstElement* element, ...);

void g_appsink_start(const gchar* name, GMultimedia *media);

#endif /* GOS2_G_MULTIMEDIA_APPSINK_H_ */
