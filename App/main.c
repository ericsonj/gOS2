#define _POSIX_C_SOURCE 200809L

#include <glib.h>
#include <gio/gio.h>
#include <unistd.h>
#include <cmsis_os2.h>

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <audio.h>
#include "g_multimedia.h"

static osMessageQueueId_t queue;
static osSemaphoreId_t sem;

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


#if 0
void timer2Thread(void *data) {
	int i = 0;
	for (; i < 10; i++) {
		osDelay(1000);
		osSemaphoreRelease(sem);
	}
	osThreadExit();
}

void timer1Thread(void *data) {

	osThreadAttr_t thattr;
	thattr.name = "time2";
	osThreadNew(timer2Thread, NULL, &thattr);
	uint32_t a = 0;

	for (;;) {
		osStatus_t res = osSemaphoreAcquire(sem, 2000);
		if (res == osErrorTimeout) {
			printf("%s\r\n", "Semaphore timeout");
		} else {
			printf("%s\r\n", "Release semaphore");
		}
	}
}
#endif

int main(int argc, char *argv[]) {

	g_multimedia_gstinit(argc, argv);
	osKernelInitialize();

	AUDIO_Init_t audioInit = {
			.SampleRate = 8000,
			.ChannelsNbr = 1,
			.Volume = 1
	};

	queue = osMessageQueueNew(10, sizeof(uint32_t), NULL);
	sem = osSemaphoreNew(1, 1, NULL);

	osThreadAttr_t thattr;
	thattr.name = "time1";
	osThreadNew(timer1Thread, NULL, &thattr);

	osKernelStart();

	return 0;
}

