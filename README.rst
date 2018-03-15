..
.. NB:  This file is machine generated, DO NOT EDIT!
..
.. Edit vmod.vcc and run make instead
..

.. role:: ref(emphasis)

.. _vmod_dns(3):

========
vmod_dns
========

------------------
Varnish dns Module
------------------

:Manual section: 3

SYNOPSIS
========


::

   import dns [from "path"] ;
   
   STRING resolve(STRING s)
  
   STRING rresolve(STRING s)
  
   STRING valid_ip(IP ip)
  
   STRING valid_host(STRING name, ENUM check)
  


DESCRIPTION
===========

This vmod provides functions to query the system's name resolution
service (which, in most cases, will be using the Domain Name System
(DNS), hence the name).

In particular, utility functions for name service based validations
are being provided, for example to identify legit search engine
crawlers based on the domain name.

  **WARNING**

  *name resolution queries can be slow as in dead slow, slow as can
  be, totally unacceptably slow for a high performance delivery
  software like Varnish. Typical DNS timeouts in the order of seconds
  are at least tens of thousands of times longer than typical
  processing times in varnish. Thus* **extreme care** *should be taken
  when using this vmod*, for example by narrowing calls to dns vmod
  functions to rare cases or heavily rate-limiting them (as with
  ``vmod_vsstrottle``, see
  https://github.com/varnish/varnish-modules). Also, using a name
  service cache (like ``nscd``) with tight timeouts is recommended.

  You've been warned.

Example
    ::

	import dns;

	sub SLOW_recv_functions {
	    set req.http.potentially-fake-client-hostname =
	      dns.rresolve(client.ip);

	    # simplified example! See
	    # https://support.google.com/webmasters/answer/1061943
	    # for the full list of google crawlers
	    #
	    if (req.http.User-Agent ~ "Googlebot" &&
		dns.valid_ip(client.ip) !~ "\.google(bot)?\.com$") {
		    set req.http.User-Agent = "fake";
		}
	    }
	}

BUILDING
========

This vmod is being build like any other modern vmod. The basic steps
are::

  ./bootstrap
  make
  make check
  make install

For building against a varnish installation at a custom prefix
``${PREFIX}``, set these environment variables before running the
above::

  export PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
  export ACLOCAL_PATH=${PREFIX}/share/aclocal


CONTENTS
========

* :ref:`func_resolve`
* :ref:`func_rresolve`
* :ref:`func_valid_host`
* :ref:`func_valid_ip`


.. _func_resolve:

STRING resolve(STRING s)
------------------------

Converts the string *s* to the first IP number returned by the system
library function getaddrinfo(3) and returns the result as a string.

This function has been obsoleted by ``std.ip()`` from varnish-cache
and is only provided for backwards compatibility. Other than that, it
is slightly more efficient if both a string result is required.


.. _func_rresolve:

STRING rresolve(STRING s)
-------------------------

Converts the string *s* to the first IP number returned by the system
library function getaddrinfo(3), issues a reverse lookup using the
library function getnameinfo(3) and returns the result.


.. _func_valid_ip:

STRING valid_ip(IP ip)
----------------------

Issues a reverse lookup of the address *ip* using the library function
getnameinfo(3), gets all addresses of the same address family as *ip*
for this *name* using getaddrinfo(3) and returns *name* if at least
one of the addresses *name* resolves to matches *ip*.

By using both a forward and a reverse lookup, this method provides a
high level of confidence that the returned *name* is in fact the
canonical name for *ip*.

Compared to combining `func_rresolve`_ with `func_resolve`_, this
function has the advantage of properly handling *name*\ s which
resolve to more than one address.


.. _func_valid_host:

STRING valid_host(STRING name, ENUM {any, all} check=any)
---------------------------------------------------------

Retrieves all addresses for *name* using getaddrinfo(3) and returns
the canonical name as `func_valid_ip` would. For *check*\ =\ ``all``,
all addresses must be determined as valid, with the default *check*\
=\ ``any``, one successful check is sufficient.

The advantage of this seemingly overly complicated method over just
comparing *name* with the result of `func_rresolve`_\ (*name*) is that
it also works if *name* is not the canonical hostname (as with CNAME
DNS records).

The advantage over using `func_valid_ip`_\ (std.ip(*name*)) is that
all or any of the addresses for *name* can be checked.

SEE ALSO
========

* vcl\(7),
* varnishd\(1)


COPYRIGHT
=========

::

  Copyright (c) 2013-2015 Kenneth Shaw
  Copyright 2018 UPLEX - Nils Goroll Systemoptimierung
  
  Authors: Kenneth Shaw
           Nils Goroll
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
  
  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
