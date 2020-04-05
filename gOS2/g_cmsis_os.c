/*
 * g_cmsis_os.c
 *
 *  Created on: Apr 3, 2020
 *      Author: Ericson Joseph
 */
#include <stdio.h>
#include <cmsis_os2.h>
#include <glib.h>

struct _GOSThread {
	osThreadFunc_t func;
	void *args;
	GThread *thread;
	GCond *startCond;
	GMutex startMux;
};

typedef struct _GOSThread GOSThread;

struct _GOSQueue {
	GAsyncQueue *queue;
	gsize itemSize;
};

typedef struct _GOSQueue GOSQueue;

struct _OSDelay {
	GMutex endDelayMux;
	GCond  endDelay;
	gint32 ticks;
};

typedef struct _OSDelay GOSDelay;


static GMainLoop *gLoop = NULL;
static GMainContext *gContext = NULL;
static GCond gStartThread;

static GMutex gTicksMutex;
static guint32 ticksCount = 0;

static GAsyncQueue* gDelayQueue;

uint32_t osKernelGetTickCount(void) {
	guint ticks = 0;
	g_mutex_lock(&gTicksMutex);
	ticks = ticksCount;
	g_mutex_unlock(&gTicksMutex);
	return ticks;
}

osStatus_t osDelay(uint32_t ticks) {

	GOSDelay* delay = g_malloc(sizeof(GOSDelay));
	g_mutex_init(&(delay->endDelayMux));
	g_cond_init(&(delay->endDelay));
	delay->ticks = ticks;

	g_async_queue_push(gDelayQueue, delay);

	g_mutex_lock(&(delay->endDelayMux));
	g_cond_wait(&(delay->endDelay), &(delay->endDelayMux));
	g_mutex_unlock(&(delay->endDelayMux));

	g_mutex_clear(&(delay->endDelayMux));
	g_cond_clear(&(delay->endDelay));
	g_free(delay);

	return osOK;
}

gpointer wrapper_gThreadFuc(gpointer data) {
	GOSThread *osth = (GOSThread*) data;
	g_mutex_lock(&(osth->startMux));
	g_cond_wait(osth->startCond, &(osth->startMux));
	g_mutex_unlock(&(osth->startMux));

	osth->func(osth->args);

	g_thread_exit(NULL);
	return NULL;
}

GOSThread* g_osThread_new(const gchar *name, osThreadFunc_t func, void *data) {

	GOSThread *t = g_malloc((gsize) sizeof(GOSThread));

	if (t == NULL) {
		return NULL;
	}

	t->startCond = &gStartThread;
	g_mutex_init(&(t->startMux));
	t->func = func;
	t->args = data;
	t->thread = g_thread_new(name, wrapper_gThreadFuc, (gpointer) t);

	return t;
}

osThreadId_t osThreadNew(osThreadFunc_t func, void *argument,
		const osThreadAttr_t *attr) {
	return g_osThread_new(attr->name, func, argument);
}

osMessageQueueId_t osMessageQueueNew(uint32_t msg_count, uint32_t msg_size,
		const osMessageQueueAttr_t *attr) {
	GOSQueue *q = g_malloc((gsize) sizeof(GOSQueue));
	q->itemSize = msg_size;
	q->queue = g_async_queue_new();
	return (void*)q;
}

osStatus_t osMessageQueuePut(osMessageQueueId_t mq_id, const void *msg_ptr,
		uint8_t msg_prio, uint32_t timeout) {
	GOSQueue *q = (GOSQueue*) mq_id;
	gpointer item = g_malloc(q->itemSize);
	memcpy(item, msg_ptr, q->itemSize);
	g_async_queue_push(q->queue, (gpointer)item);
	return osOK;
}


osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout) {
	GOSQueue *q = (GOSQueue*) mq_id;
	uint32_t now = osKernelGetTickCount();
	uint32_t current;
	gpointer item = NULL;
	do {
		item = g_async_queue_timeout_pop(q->queue, timeout*1000);
		if (item != NULL){
			break;
		}
		current = osKernelGetTickCount();
	} while((current - now) < timeout);

	if (item == NULL){
		return osErrorTimeout;
	}

	memcpy(msg_ptr, item, q->itemSize);
	g_free(item);
	return osOK;
}

gboolean esystick_callback(gpointer data) {
	g_mutex_lock(&gTicksMutex);
	ticksCount++;
	g_mutex_unlock(&gTicksMutex);

	gint len = g_async_queue_length(gDelayQueue);
	int i = 0;
	for (i = 0; i < len; i++) {
		GOSDelay* d = (GOSDelay*)g_async_queue_pop(gDelayQueue);
		(d->ticks)--;
		if (d->ticks == 0){
			g_cond_signal(&(d->endDelay));
		} else {
			g_async_queue_push(gDelayQueue, d);
		}
	}

	/*Start new threads*/
	g_cond_broadcast(&gStartThread);

	return TRUE;
}

osStatus_t osKernelInitialize(void) {

	GSource *source;
	int id;

	source = g_timeout_source_new(1);
	gContext = g_main_context_new();
	gDelayQueue = g_async_queue_new();

	g_cond_init(&gStartThread);

	id = g_source_attach(source, gContext);
	gLoop = g_main_loop_new(gContext, FALSE);
	g_source_set_callback(source, esystick_callback, gLoop, NULL);

	return osOK;
}

osStatus_t osKernelStart(void) {
	g_main_loop_run(gLoop);
	g_main_loop_unref(gLoop);
	return osOK;
}
