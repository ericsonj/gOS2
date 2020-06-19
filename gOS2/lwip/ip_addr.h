/*
 * ip_addr.h
 *
 *  Created on: Jun 19, 2020
 *      Author: ericson
 */

#ifndef GOS2_LWIP_IP_ADDR_H_
#define GOS2_LWIP_IP_ADDR_H_

#include <stdint.h>

struct ip4_addr {
  uint32_t addr;
};

typedef struct ip4_addr ip4_addr_t;

#define ipaddr_ntoa(ipaddr)  ip4addr_ntoa(ipaddr)

char * ip4addr_ntoa(const ip4_addr_t *addr);

#endif /* GOS2_LWIP_IP_ADDR_H_ */
