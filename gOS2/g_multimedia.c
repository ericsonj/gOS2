/*
 * g_multimedia.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Ericson Joseph
 */

#include "g_multimedia.h"

//static gpointer g_multimedia_thfunc(gpointer data);

void g_multimedia_gstinit(int argc, char *argv[]) {
	gst_init(&argc, &argv);
}

GMultimedia* g_multimedia_init(GstElement* element, ...) {

	va_list valist;
	va_start(valist, element);

	GstElement *pipeline;

	pipeline = gst_pipeline_new("pipeline");

	gst_bin_add(GST_BIN(pipeline), element);

	GstElement *obj = NULL;
	while ((obj = va_arg(valist, GstElement*)) != NULL) {
		gst_bin_add(GST_BIN(pipeline), obj);
	}

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

	va_end(valist);

	return g_multimedia_initByPipeline(pipeline);
}

GMultimedia* g_multimedia_initByPipeline(GstElement* pipeline){
	GMultimedia *resp = g_malloc(sizeof(GMultimedia));
	resp->pipeline = pipeline;
	return resp;
}

void g_multimedia_start(const gchar* name, GMultimedia *media) {
	media->thread = g_thread_new(name, g_multimedia_thfunc, media);
}

gpointer g_multimedia_thfunc(gpointer data) {
	GMultimedia *media = (GMultimedia*) data;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;
	GstElement *pipeline = media->pipeline;

	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(pipeline);
		return NULL;
	}

	/* Wait until error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
			(GstMessageType) (GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

	/* Parse message */
	if (msg != NULL) {
		GError *err;
		gchar *debug_info;

		switch (GST_MESSAGE_TYPE(msg)) {
		case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg, &err, &debug_info);
			g_printerr("Error received from element %s: %s\n",
					GST_OBJECT_NAME(msg->src), err->message);
			g_printerr("Debugging information: %s\n",
					debug_info ? debug_info : "none");
			g_clear_error(&err);
			g_free(debug_info);
			break;
		case GST_MESSAGE_EOS:
			g_print("TX End-Of-Stream reached.\n");
			break;
		default:
			/* We should not reach here because we only asked for ERRORs and EOS */
			g_printerr("Unexpected message received.\n");
			break;
		}
		gst_message_unref(msg);
	}

	/* Free resources */
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);

	return NULL;
}

