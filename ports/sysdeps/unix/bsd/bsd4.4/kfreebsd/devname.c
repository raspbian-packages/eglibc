/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#include <stdio.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/sysctl.h>

char *
__devname_r(__dev_t dev, __mode_t type, char *buf, int len)
{
	int i;
	size_t j;
	const char *r;

	if ((type & S_IFMT) == S_IFCHR) {
		j = len;
		i = __sysctlbyname("kern.devname", buf, &j, &dev, sizeof (dev));
		if (i == 0)
		    return (buf);
	}

	/* Finally just format it */
	if (dev == NODEV)
		r = "#NODEV";
	else 
		r = "#%c:%d:0x%x";
	__snprintf(buf, len, r,
	    (type & S_IFMT) == S_IFCHR ? 'C' : 'B', major(dev), minor(dev));
	return (buf);
}


char *
__devname(__dev_t dev, __mode_t type)
{
	static char buf[SPECNAMELEN + 1];

	return(__devname_r(dev, type, buf, sizeof(buf)));
}
weak_alias (__devname_r, devname_r)
weak_alias (__devname, devname)
