#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include "vdef.h"
#include "vrt.h"
#include "miniobj.h"
#include "vas.h"

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
    return (0);
}

VCL_STRING
vmod_resolve(VRT_CTX, VCL_STRING hostname)
{
	const struct sockaddr_in *si4;
	const struct sockaddr_in6 *si6;
	struct addrinfo *res;
	const void *addr;
	const char *r;
	int len;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

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

	/*
	 * copy twice to avoid dependency on WS_Alloc, which is not in $ABI VRT
	 * minor bonus: can use less workspace than allocing len
	 */

	char p[len];
	r = VRT_CollectString(ctx, inet_ntop(res->ai_family, addr, p, len),
	    vrt_magic_string_end);

	freeaddrinfo(res);
	return (r);
}

VCL_STRING
vmod_rresolve(VRT_CTX, VCL_STRING hostname)
{
	char node[NI_MAXHOST];
	struct addrinfo *res;
	const char *p = NULL;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

	if (getaddrinfo(hostname, NULL, NULL, &res))
		return (NULL);

	if (!getnameinfo(res->ai_addr, res->ai_addrlen, node,
	    sizeof(node), NULL, 0, 0))
		p = VRT_CollectString(ctx, node, vrt_magic_string_end);

	freeaddrinfo(res);
	return (p);
}
