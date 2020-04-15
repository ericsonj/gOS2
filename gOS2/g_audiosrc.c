/*
 * g_audiosrc.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Ericson Joseph
 */
#include "g_audiosrc.h"

#define PCM_AUDIO_SRC "audiotestsrc"


static GstFlowReturn new_sample (GstElement *sink, gpointer *data) {
	GstSample *sample;
	GstMapInfo info;
	g_signal_emit_by_name (sink, "pull-sample", &sample);

	if (sample) {
		GstBuffer *buffer = gst_sample_get_buffer(sample);
		gst_buffer_map(buffer, &info, GST_MAP_READ);

		((audio_callback)data)(info.data, info.size);

	    gst_sample_unref (sample);
	    return GST_FLOW_OK;
	}

	return GST_FLOW_ERROR;
}

GMultimedia* g_pcmaudiosrc_init(const gchar* format, guint rate, gint channes, audio_callback callback){

	GstElement *source;
	GstElement *pipeline;
	GstElement *sink;
	GstCaps *caps;

	source = gst_element_factory_make(PCM_AUDIO_SRC, NULL);
	g_object_set(source, "is-live", TRUE, "samplesperbuffer", 160, NULL);

	sink = gst_element_factory_make ("appsink", "appsink");
	g_object_set(sink, "emit-signals",  TRUE, NULL);
	g_signal_connect(sink, "new-sample", G_CALLBACK (new_sample), callback);

	pipeline = gst_pipeline_new("pipeline");

	gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);

	caps = gst_caps_new_simple (
				"audio/x-raw",
				"format",   G_TYPE_STRING, format,
				"rate",     G_TYPE_INT, rate,
				"channels", G_TYPE_INT, channes, NULL);

	gst_element_link_filtered (source, sink, caps);
	gst_caps_unref (caps);

	GMultimedia *resp = g_malloc(sizeof(GMultimedia));
	resp->pipeline = pipeline;
	return resp;

}

void g_pcmaudiosrc_start(GMultimedia* media){
	g_multimedia_start("pcmaudiosrc", media);
}


