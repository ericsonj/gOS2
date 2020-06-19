/*
 * dns.c
 *
 *  Created on: Jun 10, 2020
 *      Author: Ericson Joseph
 *
 */

#include "lwip/dns.h"
#include <stdio.h>

#include "gio/gio.h"

err_t dns_gethostbyname(const char *hostname, ip_addr_t *addr,
                        dns_found_callback found, void *callback_arg) {


	GError *err = NULL;
	GResolver *ptrGResolver = g_resolver_get_default();
	GList *prtGList = g_resolver_lookup_by_name(ptrGResolver, hostname, NULL, &err);
	if (prtGList != NULL) {
		GList* first = g_list_first(prtGList);
		GInetAddress *ginetaddr = (GInetAddress *)first->data;
		const guint8 *ip = g_inet_address_to_bytes(ginetaddr);
		memcpy(addr, ip, 4);
	}
	g_resolver_free_addresses(prtGList);
	found(hostname, addr, callback_arg);
}
