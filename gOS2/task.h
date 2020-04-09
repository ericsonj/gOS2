/*
 * task.h
 *
 *  Created on: Apr 7, 2020
 *      Author: ericson
 */

#ifndef GOS2_TASK_H_
#define GOS2_TASK_H_

#include "cmsis_os2.h"


typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

typedef osThreadId_t TaskHandle_t;

#define xTaskCreate( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask ) xTaskGenericCreate( ( pvTaskCode ), ( pcName ), ( usStackDepth ), ( pvParameters ), ( uxPriority ), ( pxCreatedTask ))

#define tskIDLE_PRIORITY			( ( UBaseType_t ) 0U )

BaseType_t xTaskGenericCreate(
		osThreadFunc_t pvTaskCode,
		const char *pcName,
		const uint16_t usStackDepth,
		void *const pvParameters,
		UBaseType_t uxPriority,
		TaskHandle_t *const pxCreatedTask);


#endif /* GOS2_TASK_H_ */
