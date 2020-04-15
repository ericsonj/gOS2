/*
 * g_multimedia.h
 *
 *  Created on: Apr 14, 2020
 *      Author: Ericson Joseph
 */

#ifndef GOS2_G_MULTIMEDIA_H_
#define GOS2_G_MULTIMEDIA_H_

#include <gst/gst.h>
#include <stdarg.h>

struct _GMultimedia {
	GThread *thread;
	GstElement *pipeline;
	void (*callback)(guint8* data, gsize size);
};

typedef struct _GMultimedia GMultimedia;

void g_multimedia_gstinit(int argc, char *argv[]);

GMultimedia* g_multimedia_init(GstElement* element, ...);

GMultimedia* g_multimedia_initByPipeline(GstElement* pipeline);

void g_multimedia_start(const gchar* name, GMultimedia *media);

gpointer g_multimedia_thfunc(gpointer data);

#endif /* GOS2_G_MULTIMEDIA_H_ */
