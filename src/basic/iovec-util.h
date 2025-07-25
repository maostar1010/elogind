/* SPDX-License-Identifier: LGPL-2.1-or-later */
#pragma once

#include <stdbool.h>
#include <sys/types.h>
#include <sys/uio.h>

#include "alloc-util.h"
#include "iovec-util-fundamental.h"
#include "macro.h"

extern const struct iovec iovec_nul_byte; /* Points to a single NUL byte */
extern const struct iovec iovec_empty;    /* Points to an empty, but valid (i.e. non-NULL) pointer */

size_t iovec_total_size(const struct iovec *iovec, size_t n);

bool iovec_increment(struct iovec *iovec, size_t n, size_t k);

static inline struct iovec* iovec_make_string(struct iovec *iovec, const char *s) {
        assert(iovec);
        /* We don't use strlen_ptr() here, because we don't want to include string-util.h for now */
        *iovec = IOVEC_MAKE(s, s ? strlen(s) : 0);
        return iovec;
}

#define IOVEC_MAKE_STRING(s) \
        *iovec_make_string(&(struct iovec) {}, s)

#if 0 /// UNNEEDED by elogind
#define CONST_IOVEC_MAKE_STRING(s)              \
        (const struct iovec) {                  \
                .iov_base = (char*) s,          \
                .iov_len = STRLEN(s),           \
        }

static inline void iovec_done_erase(struct iovec *iovec) {
        assert(iovec);

        iovec->iov_base = erase_and_free(iovec->iov_base);
        iovec->iov_len = 0;
}
#endif // 0

#if 0 /// UNNEEDED by elogind

char* set_iovec_string_field(struct iovec *iovec, size_t *n_iovec, const char *field, const char *value);
char* set_iovec_string_field_free(struct iovec *iovec, size_t *n_iovec, const char *field, char *value);
#endif // 0

void iovec_array_free(struct iovec *iovec, size_t n_iovec);

#if 0 /// UNNEEDED by elogind
static inline int iovec_memcmp(const struct iovec *a, const struct iovec *b) {

        if (a == b)
                return 0;

        return memcmp_nn(a ? a->iov_base : NULL,
                         a ? a->iov_len : 0,
                         b ? b->iov_base : NULL,
                         b ? b->iov_len : 0);
}
#endif // 0

static inline struct iovec *iovec_memdup(const struct iovec *source, struct iovec *ret) {
        assert(ret);

        if (!iovec_is_set(source))
                *ret = (struct iovec) {};
        else {
                void *p = memdup(source->iov_base, source->iov_len);
                if (!p)
                        return NULL;

                *ret = IOVEC_MAKE(p, source->iov_len);
        }

        return ret;
}

struct iovec* iovec_append(struct iovec *iovec, const struct iovec *append);
