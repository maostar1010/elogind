/* SPDX-License-Identifier: LGPL-2.1-or-later */
#pragma once

#include <stdbool.h>

#include "sd-json.h"

int parse_boolean_argument(const char *optname, const char *s, bool *ret);
int parse_json_argument(const char *s, sd_json_format_flags_t *ret);
#if 0 /// UNNEEDED by elogind
int parse_path_argument(const char *path, bool suppress_root, char **arg);
#endif // 0
int parse_signal_argument(const char *s, int *ret);
