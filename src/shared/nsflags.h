/* SPDX-License-Identifier: LGPL-2.1-or-later */
#pragma once

#include "missing_sched.h"

/* The combination of all namespace flags defined by the kernel. The right type for this isn't clear. setns() and
 * unshare() expect these flags to be passed as (signed) "int", while clone() wants them as "unsigned long". The latter
 * is definitely more appropriate for a flags parameter, and also the larger type of the two, hence let's stick to that
 * here. */
#define NAMESPACE_FLAGS_ALL                                             \
        ((unsigned long) (CLONE_NEWCGROUP|                              \
                          CLONE_NEWIPC|                                 \
                          CLONE_NEWNET|                                 \
                          CLONE_NEWNS|                                  \
                          CLONE_NEWPID|                                 \
                          CLONE_NEWUSER|                                \
                          CLONE_NEWUTS))

#define NAMESPACE_FLAGS_INITIAL  ULONG_MAX

#if 0 /// UNNEEDED by elogind
int namespace_flags_from_string(const char *name, unsigned long *ret);
#endif // 0
int namespace_flags_to_string(unsigned long flags, char **ret);
const char* namespace_single_flag_to_string(unsigned long flag);
