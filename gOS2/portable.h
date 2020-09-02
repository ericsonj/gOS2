/*
 * portable.h
 *
 *  Created on: Apr 7, 2020
 *      Author: ericson
 */

#ifndef GOS2_PORTABLE_H_
#define GOS2_PORTABLE_H_

#include <stdint.h>
#include <stdlib.h>

typedef long BaseType_t;
typedef unsigned long UBaseType_t;
typedef uint32_t TickType_t;

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

#define portTicksFromMs(X)  	(X)

#define	portTICK_PERIOD_MS       1 /*1 MS*/

void *pvPortMalloc( size_t xSize );
void vPortFree( void *pv );

#endif /* GOS2_PORTABLE_H_ */
