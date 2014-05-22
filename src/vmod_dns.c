#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"


const char *
vmod_resolve(struct sess *sp, const char *hostname)
{
	const struct sockaddr_in *si4;
	const struct sockaddr_in6 *si6;
	struct addrinfo *res;
	const void *addr;
	char *p;
	int len;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);

	if (getaddrinfo(hostname, NULL, NULL, &res))
		return (NULL);

	switch (res->ai_family) {
	case AF_INET:
		len = INET_ADDRSTRLEN;
		si4 = (const void *)res->ai_addr;
		addr = &(si4->sin_addr);
		break;
	case AF_INET6:
		len = INET6_ADDRSTRLEN;
		si6 = (const void *)res->ai_addr;
		addr = &(si6->sin6_addr);
		break;
	default:
		INCOMPL();
	}

	XXXAN(len);
	AN(p = WS_Alloc(sp->wrk->ws, len));
	AN(inet_ntop(res->ai_family, addr, p, len));

	freeaddrinfo(res);
	return (p);
}

const char *
vmod_rresolve(struct sess *sp, const char *hostname)
{
	char node[NI_MAXHOST];
	struct addrinfo *res;
	char *p = NULL;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);

	if (getaddrinfo(hostname, NULL, NULL, &res))
		return (NULL);

	if (!getnameinfo(res->ai_addr, res->ai_addrlen, node,
	    sizeof(node), NULL, 0, 0))
		p = WS_Dup(sp->wrk->ws, node);

	freeaddrinfo(res);
	return (p);
}
