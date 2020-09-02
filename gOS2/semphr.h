/*
 * semphr.h
 *
 *  Created on: Jun 19, 2020
 *      Author: ericson
 */

#ifndef GOS2_SEMPHR_H_
#define GOS2_SEMPHR_H_

#include "queue.h"

typedef QueueHandle_t SemaphoreHandle_t;

#define semBINARY_SEMAPHORE_QUEUE_LENGTH	( ( uint8_t ) 1U )
#define semSEMAPHORE_QUEUE_ITEM_LENGTH		( ( uint8_t ) 1U )
#define semGIVE_BLOCK_TIME					( ( TickType_t ) 0U )


#define xSemaphoreCreateBinary() xQueueGenericCreate( ( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH )

#define xSemaphoreTake( xSemaphore, xBlockTime )	xQueueReceive( ( xSemaphore ), NULL, ( xBlockTime ) )

#define xSemaphoreGive( xSemaphore )	xQueueGenericSend( ( QueueHandle_t ) ( xSemaphore ), NULL, semGIVE_BLOCK_TIME)

QueueHandle_t xSemaphoreCreateCounting(const UBaseType_t max, const UBaseType_t init);

#endif /* GOS2_SEMPHR_H_ */
