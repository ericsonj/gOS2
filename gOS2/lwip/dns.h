/*
 * dns.h
 *
 *  Created on: Jun 10, 2020
 *      Author: Ericson Joseph
 */

#ifndef GOS2_LWIP_DNS_H_
#define GOS2_LWIP_DNS_H_

#include "lwip/err.h"
#include "lwip/socket.h"

typedef in_addr_t ip_addr_t;

typedef void (*dns_found_callback)(const char *name, ip_addr_t *ipaddr,
                                   void *callback_arg);

err_t dns_gethostbyname(const char *hostname, ip_addr_t *addr,
                        dns_found_callback found, void *callback_arg);


#endif /* GOS2_LWIP_DNS_H_ */
