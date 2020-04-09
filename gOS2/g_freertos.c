/*
 * g_freertos.c
 *
 *  Created on: Apr 7, 2020
 *      Author: Ericson Joseph
 */
#include <glib.h>
#include <stdlib.h>
#include "task.h"
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


void *pvPortMalloc( size_t xSize ) {
	return g_malloc((gsize)xSize);
}

void vPortFree( void *pv ) {
	g_free((gpointer)pv);
}

