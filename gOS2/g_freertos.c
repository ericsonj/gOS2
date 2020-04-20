/*
 * g_freertos.c
 *
 *  Created on: Apr 7, 2020
 *      Author: Ericson Joseph
 */
#include <glib.h>
#include <stdlib.h>
#include "task.h"
#include "queue.h"
#include "portable.h"

BaseType_t xTaskGenericCreate(
		osThreadFunc_t pvTaskCode,
		const char *pcName,
		const uint16_t usStackDepth,
		void *const pvParameters,
		UBaseType_t uxPriority,
		TaskHandle_t *const pxCreatedTask) {

	osThreadAttr_t attr;
	attr.name = pcName;
	attr.priority = uxPriority;
	attr.stack_size = usStackDepth;
	osThreadId_t t = osThreadNew(pvTaskCode,pvParameters, &attr);
	if (pxCreatedTask != NULL){
		(*pxCreatedTask) = t;
	}
	return pdPASS;
}

void vTaskDelete( TaskHandle_t xTaskToDelete ){
	if (xTaskToDelete == NULL) {
		osThreadExit();
	}
}

QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize) {
	return osMessageQueueNew(uxQueueLength, uxItemSize, NULL);
}

BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait){
	osMessageQueuePut(xQueue, pvItemToQueue, 0, 0);
	return pdPASS;
}

BaseType_t xQueueReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait ){
	if (osMessageQueueGet(xQueue, pvBuffer,0, xTicksToWait) == osErrorTimeout){
		return pdFALSE;
	}
	return pdTRUE;
}


void *pvPortMalloc( size_t xSize ) {
	return g_malloc((gsize)xSize);
}

void vPortFree( void *pv ) {
	g_free((gpointer)pv);
}

