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
#include "semphr.h"

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

void vTaskDelay( const TickType_t xTicksToDelay ) {
	osDelay(xTicksToDelay);
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

QueueHandle_t xSemaphoreCreateCounting(const UBaseType_t max, const UBaseType_t init) {
	QueueHandle_t res = xQueueGenericCreate(( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH);
	for (UBaseType_t i = 0; i < init; i++) {
		xSemaphoreGive(res);
	}
	return res;
}

void *pvPortMalloc( size_t xSize ) {
	return g_malloc((gsize)xSize);
}

void vPortFree( void *pv ) {
	g_free((gpointer)pv);
}

