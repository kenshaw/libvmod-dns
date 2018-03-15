#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vdef.h"
#include "vrt.h"
#include "miniobj.h"
#include "vas.h"
#include "vsa.h"

#include "vcc_dns_if.h"

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

#define c4(sa) (&((const struct sockaddr_in *)sa)->sin_addr)
#define c6(sa) (&((const struct sockaddr_in6 *)sa)->sin6_addr)

static int
cmp_addr(const struct sockaddr *a, const struct sockaddr *b)
{
	AN(a);
	AN(b);
	assert(a->sa_family == b->sa_family);

	switch (a->sa_family) {
	case AF_INET:
		return (memcmp(c4(a), c4(b), sizeof (struct in_addr)));
	case AF_INET6:
		return (memcmp(c6(a), c6(b), sizeof (struct in6_addr)));
	default:
		INCOMPL();
	}
}

#undef c4
#undef c6


static VCL_STRING
valid_ip(VRT_CTX, const struct sockaddr *sa, const socklen_t sl)
{
	char node[NI_MAXHOST];
	struct addrinfo hints, *res0 = NULL;
	const struct addrinfo *res = NULL;
	const char *r = NULL;

	AN(sa);
	if (getnameinfo(sa, sl, node, sizeof(node), NULL, 0, NI_NAMEREQD))
		return (NULL);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = sa->sa_family;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(node, "80", &hints, &res0))
		return (NULL);

	for (res = res0; res != NULL; res = res->ai_next) {
		if (res->ai_family == sa->sa_family &&
		    res->ai_addrlen == sl &&
		    cmp_addr(res->ai_addr, sa) == 0) {
			r = VRT_CollectString(ctx, node, vrt_magic_string_end);
			break;
		}
	}
	freeaddrinfo(res0);
	return (r);
}

VCL_STRING
vmod_valid_ip(VRT_CTX, VCL_IP ip)
{
	const struct sockaddr *sa;
	socklen_t sl;

	AN(ip);
	assert(VSA_Sane(ip));

	sa = VSA_Get_Sockaddr(ip, &sl);
	return (valid_ip(ctx, sa, sl));
}

VCL_STRING
vmod_valid_host(VRT_CTX, VCL_STRING node, VCL_ENUM check)
{
	struct addrinfo hints, *res0 = NULL;
	const struct addrinfo *res = NULL;
	const char *r = NULL;
	const int all = (check == vmod_enum_all);

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(node, "80", &hints, &res0))
		return (NULL);

	for (res = res0; res != NULL; res = res->ai_next) {
		r = valid_ip(ctx, res->ai_addr, res->ai_addrlen);
		if (all && r == NULL)
			break;
	}
	freeaddrinfo(res0);
	return (r);
}
