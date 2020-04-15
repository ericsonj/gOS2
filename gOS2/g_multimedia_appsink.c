/*
 * g_multimedia_appsink.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Ericson Joseph
 */
#include "g_multimedia_appsink.h"

static GstFlowReturn new_sample (GstElement *sink, gpointer *data) {
	GstSample *sample;
	GstMapInfo info;
	g_signal_emit_by_name (sink, "pull-sample", &sample);

	if (sample) {
		GstBuffer *buffer = gst_sample_get_buffer(sample);
		gst_buffer_map(buffer, &info, GST_MAP_READ);

		((multimedia_callback)data)(info.data, info.size);

	    gst_sample_unref (sample);
	    return GST_FLOW_OK;
	}

	return GST_FLOW_ERROR;
}


GMultimedia* g_appsink_init(multimedia_callback callback, GstElement* element, ...) {

	GstElement* sink;

	va_list valist;
	va_start(valist, element);

	GstElement *pipeline;

	pipeline = gst_pipeline_new("pipeline");

	gst_bin_add(GST_BIN(pipeline), element);

	GstElement *obj = NULL;
	while ((obj = va_arg(valist, GstElement*)) != NULL) {
		gst_bin_add(GST_BIN(pipeline), obj);
	}

	sink = gst_element_factory_make ("appsink", "sink");
	g_object_set(sink, "emit-signals",  TRUE, NULL);
	g_signal_connect(sink, "new-sample", G_CALLBACK (new_sample), callback);
	gst_bin_add(GST_BIN(pipeline), sink);

	va_end(valist);

	va_start(valist, element);

	obj = NULL;
	GstElement *src = element;
	GstElement *dst = NULL;
	while ((obj = va_arg(valist, GstElement*)) != NULL) {
		if (src == NULL) {
			src = obj;
			continue;
		}
		if (dst == NULL) {
			dst = obj;
			gst_element_link(src, dst);
			src = dst;
			dst = NULL;
		}
	}

	GstCaps *caps;
	caps = gst_caps_new_simple (
			"audio/x-raw",
			"format",   G_TYPE_STRING, "S16LE",
			"rate",     G_TYPE_INT, 8000,
			"channels", G_TYPE_INT, 1, NULL);

	gst_element_link_filtered (src, sink, caps);
	gst_caps_unref (caps);

	va_end(valist);

	GMultimedia *resp = g_malloc(sizeof(GMultimedia));
	resp->pipeline = pipeline;
	return resp;
}

void g_appsink_start(const gchar* name, GMultimedia *media) {
	media->thread = g_thread_new(name, g_multimedia_thfunc, media);
}



