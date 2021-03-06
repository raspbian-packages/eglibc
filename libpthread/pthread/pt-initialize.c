/* Initialize pthreads library.
   Copyright (C) 2000,02 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <assert.h>
#include <string.h>

#include <pt-internal.h>
#include <set-hooks.h>

#include <pthread.h>
#include <pthread-functions.h>

DEFINE_HOOK (__pthread_init, (void));

#ifdef IS_IN_libpthread
static const struct pthread_functions pthread_functions =
  {
    .ptr_pthread_attr_destroy = __pthread_attr_destroy,
    .ptr_pthread_attr_init = __pthread_attr_init,
    .ptr_pthread_attr_getdetachstate = __pthread_attr_getdetachstate,
    .ptr_pthread_attr_setdetachstate = __pthread_attr_setdetachstate,
    .ptr_pthread_attr_getinheritsched = __pthread_attr_getinheritsched,
    .ptr_pthread_attr_setinheritsched = __pthread_attr_setinheritsched,
    .ptr_pthread_attr_getschedparam = __pthread_attr_getschedparam,
    .ptr_pthread_attr_setschedparam = __pthread_attr_setschedparam,
    .ptr_pthread_attr_getschedpolicy = __pthread_attr_getschedpolicy,
    .ptr_pthread_attr_setschedpolicy = __pthread_attr_setschedpolicy,
    .ptr_pthread_attr_getscope = __pthread_attr_getscope,
    .ptr_pthread_attr_setscope = __pthread_attr_setscope,
    .ptr_pthread_condattr_destroy = __pthread_condattr_destroy,
    .ptr_pthread_condattr_init = __pthread_condattr_init,
    .ptr_pthread_cond_broadcast = __pthread_cond_broadcast,
    .ptr_pthread_cond_destroy = __pthread_cond_destroy,
    .ptr_pthread_cond_init = __pthread_cond_init,
    .ptr_pthread_cond_signal = __pthread_cond_signal,
    .ptr_pthread_cond_wait = __pthread_cond_wait,
    .ptr_pthread_cond_timedwait = __pthread_cond_timedwait,
    .ptr_pthread_equal = __pthread_equal,
    .ptr_pthread_exit = __pthread_exit,
    .ptr_pthread_getschedparam = __pthread_getschedparam,
    .ptr_pthread_setschedparam = __pthread_setschedparam,
    .ptr_pthread_mutex_destroy = _pthread_mutex_destroy,
    .ptr_pthread_mutex_init = _pthread_mutex_init,
    .ptr_pthread_mutex_lock = __pthread_mutex_lock,
    .ptr_pthread_mutex_trylock = __pthread_mutex_trylock,
    .ptr_pthread_mutex_unlock = __pthread_mutex_unlock,
    .ptr_pthread_self = __pthread_self,
    .ptr_pthread_setcancelstate = __pthread_setcancelstate,
    .ptr_pthread_setcanceltype = __pthread_setcanceltype,
    .ptr___pthread_get_cleanup_stack = __pthread_get_cleanup_stack,
  };
#endif /* IS_IN_libpthread */

/* Initialize the pthreads library.  */
void
__pthread_init (void)
{
#ifdef IS_IN_libpthread
  __libc_pthread_init(&pthread_functions);
#endif
  RUN_HOOK (__pthread_init, ());
}
