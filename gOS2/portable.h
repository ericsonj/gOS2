/*
 * portable.h
 *
 *  Created on: Apr 7, 2020
 *      Author: ericson
 */

#ifndef GOS2_PORTABLE_H_
#define GOS2_PORTABLE_H_

#include <stdlib.h>

void *pvPortMalloc( size_t xSize );
void vPortFree( void *pv );

#endif /* GOS2_PORTABLE_H_ */
