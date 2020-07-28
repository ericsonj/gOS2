/*
 * dns.c
 *
 *  Created on: Jun 10, 2020
 *      Author: Ericson Joseph
 *
 */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "lwip/dns.h"
#include <stdio.h>

#include "gio/gio.h"

struct dnsTaskArgs {
	const char *hostname;
	ip_addr_t *addr;
	dns_found_callback found;
	void *callback_arg;
};



static void dns_gethostbynameTask(void *args) {
	struct dnsTaskArgs *a = (struct dnsTaskArgs*)args;
	GError *err = NULL;
	GResolver *ptrGResolver = g_resolver_get_default();
	GList *prtGList = g_resolver_lookup_by_name(ptrGResolver, a->hostname, NULL, &err);
	if (prtGList != NULL) {
		GList* first = g_list_first(prtGList);
		GInetAddress *ginetaddr = (GInetAddress *)first->data;
		const guint8 *ip = g_inet_address_to_bytes(ginetaddr);
		memcpy(a->addr, ip, 4);
	}
	g_resolver_free_addresses(prtGList);
	a->found(a->hostname, a->addr, a->callback_arg);
	vPortFree(args);
	vTaskDelete(NULL);
}

err_t dns_gethostbyname(const char *hostname, ip_addr_t *addr,
                        dns_found_callback found, void *callback_arg) {
	struct dnsTaskArgs *args = pvPortMalloc(sizeof(struct dnsTaskArgs));
	args->hostname = hostname;
	args->addr = addr;
	args->found = found;
	args->callback_arg = callback_arg;
	xTaskCreate(dns_gethostbynameTask, "dns_gethostbynameTask", configMINIMAL_STACK_SIZE * 3, args, tskIDLE_PRIORITY + 2, NULL);
	return ERR_OK;
}
