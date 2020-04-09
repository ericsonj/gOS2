#define _POSIX_C_SOURCE 200809L

#include <glib.h>
#include <gio/gio.h>
#include <unistd.h>
#include <cmsis_os2.h>

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>


static osMessageQueueId_t queue;

void print_current_time_with_ms(void) {
	long ms; // Milliseconds
	time_t s;  // Seconds
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);

	s = spec.tv_sec;
	ms = (spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
	if (ms > 999) {
		s++;
		ms = 0;
	}

	printf("Current time: %"PRIdMAX".%03ld\n", (intmax_t) s, ms);

}

void timer2Thread(void *data) {
	int i = 0;
	for (;;) {
		uint32_t a;
		if (osMessageQueueGet(queue, &a, 0, 10000) == osOK) {
			print_current_time_with_ms();
		}
	}
}

void timer1Thread(void *data) {
	int i = 0;

	osThreadAttr_t thattr;
	thattr.name = "time2";
	osThreadNew(timer2Thread, NULL, &thattr);
	uint32_t a = 0;

	for (;;) {
		osDelay(1000);
		osMessageQueuePut(queue, &a, 0, 0);
		a++;
	}
}

static void my_callback(GObject *source_object, GAsyncResult *res,
			gpointer user_data)
{
	printf("%p: %s\n", g_thread_self(), __func__);

}

static void my_thread(GTask *task, gpointer source_object,
			     gpointer task_data, GCancellable *cancellable)
{
	printf("%p: %s\n", g_thread_self(), __func__);
	g_task_return_pointer(task, g_object_new(G_TYPE_OBJECT, NULL), g_object_unref);
}

int main() {

	osKernelInitialize();

	GCancellable* cancellable = g_cancellable_new();

	GObject *obj = g_object_new(G_TYPE_OBJECT, NULL);
	GTask*  task = g_task_new(obj, cancellable, my_callback, obj);
	g_object_unref(cancellable);
	g_task_run_in_thread(task, my_thread);
	g_object_unref(task);

	queue = osMessageQueueNew(10, sizeof(uint32_t), NULL);

	osThreadAttr_t thattr;
	thattr.name = "time1";
	osThreadNew(timer1Thread, NULL, &thattr);

	osKernelStart();

	return 0;
}

