/*
 * g_g711rtp.c
 *
 *  Created on: Apr 20, 2020
 *      Author: Ericson Joseph
 */

#include "g_g711rtp.h"


struct g_g711rtp_callback {
	audio_callback func;
	void *arg;
};

struct g_g711rtp_callback callb;

static GstFlowReturn new_sample (GstElement *sink, gpointer *data) {
	GstSample *sample;
	GstMapInfo info;
	g_signal_emit_by_name (sink, "pull-sample", &sample);

	if (sample) {
		GstBuffer *buffer = gst_sample_get_buffer(sample);
		gst_buffer_map(buffer, &info, GST_MAP_READ);

		((audio_callback)data)(info.data, info.size, NULL);

	    gst_sample_unref (sample);
	    return GST_FLOW_OK;
	}

	return GST_FLOW_ERROR;
}


GMultimedia* g_g711rtp_init(audio_callback callback) {

	GstElement *pipeline, *source, *audioenc, *rtppay, *sink;
//	GstCaps *caps;
//	GstBus *bus;
//	GstMessage *msg;
//	GstCaps *audio_caps;
//	GstStateChangeReturn ret;

	source = gst_element_factory_make("audiotestsrc", "audiotestsrc");
	audioenc = gst_element_factory_make("alawenc", NULL);
	rtppay = gst_element_factory_make("rtppcmapay", NULL);
	sink = gst_element_factory_make ("appsink", "sink");

	pipeline = gst_pipeline_new("audio-pipeline");

	if (!source || !audioenc || !rtppay || !sink) {
		g_printerr("Not all elements could be created.\n");
		return 0;
	}

	g_object_set(rtppay, "min-ptime", 20000000, NULL);
	g_object_set(rtppay, "max-ptime", 20000000, NULL);


	g_object_set(sink, "emit-signals",  TRUE, NULL);
	g_signal_connect(sink, "new-sample", G_CALLBACK (new_sample), callback);
//	gst_caps_unref(audio_caps);

    gst_bin_add_many(GST_BIN(pipeline), source, audioenc, rtppay, sink, NULL);

	if (gst_element_link_many(source, audioenc, rtppay, sink, NULL) != TRUE) {
		g_printerr("Elements could not be linked.\n");
		gst_object_unref(pipeline);
		return 0;
	}

	GMultimedia *resp = g_malloc(sizeof(GMultimedia));
	resp->pipeline = pipeline;
	return resp;

}


void g_g711rtp_start(GMultimedia* media) {
	g_multimedia_start("g711rtp", media);
}
