/*
 * g_ip_addr.c
 *
 *  Created on: Jun 19, 2020
 *      Author: ericson
 */
#include <arpa/inet.h>
#include "lwip/ip_addr.h"

char * ip4addr_ntoa(const ip4_addr_t *addr) {
	struct in_addr aux;
	aux.s_addr = addr->addr;
	return inet_ntoa(aux);
}
