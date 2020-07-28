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

/**
 * @ingroup ipaddr
 * A union struct for both IP version's addresses.
 * ATTENTION: watch out for its size when adding IPv6 address scope!
 */
typedef struct ip_addr {
  union {
//    ip6_addr_t ip6;
    ip4_addr_t ip4;
  } u_addr;
  /** @ref lwip_ip_addr_type */
  uint8_t type;
} ip_addr_t;


//#define ipaddr_ntoa(ipaddr)  ip4addr_ntoa(ipaddr)

char* ip4addr_ntoa(const ip4_addr_t *addr);

#endif /* GOS2_LWIP_IP_ADDR_H_ */
