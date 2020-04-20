/*
 * queue.h
 *
 *  Created on: Apr 16, 2020
 *      Author: Ericson Joseph
 */

#ifndef GOS2_QUEUE_H_
#define GOS2_QUEUE_H_

#include "FreeRTOS.h"
#include "cmsis_os2.h"

typedef struct osMessageQueueId_t* QueueHandle_t;

#define xQueueCreate( uxQueueLength, uxItemSize ) xQueueGenericCreate( ( uxQueueLength ), ( uxItemSize ))

#define xQueueSend( xQueue, pvItemToQueue, xTicksToWait ) xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ))

QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize);

BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait);

BaseType_t xQueueReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait );

#endif /* GOS2_QUEUE_H_ */
