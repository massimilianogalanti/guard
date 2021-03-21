#ifndef __GUARD_H__
#define __GUARD_H__

#include <stdint.h>

#define GUARD_FAIL() while (1)

#define USE_STRUCT_GUARD 1

typedef uint32_t guard_t;
#define GUARD_VALUE_DEFAULT 0xaa55aa55

#if (1 == USE_STRUCT_GUARD)
#define STRUCT_START_GUARD const guard_t _guard_begin;
#define STRUCT_END_GUARD const guard_t _guard_end;
#define STRUCT_DECLARE_GUARDS ._guard_begin = GUARD_VALUE_DEFAULT, ._guard_end = GUARD_VALUE_DEFAULT
#define STRUCT_GUARDS_FAIL(s) if (s._guard_begin != GUARD_VALUE_DEFAULT || s._guard_end != GUARD_VALUE_DEFAULT) { GUARD_FAIL(); }
#else
#define STRUCT_START_GUARD
#define STRUCT_END_GUARD
#define STRUCT_DECLARE_GUARDS
#define STRUCT_GUARDS_FAIL(s)
#endif

typedef uint32_t csum_t;
#define CSUM_SEED 0xdeadbeef

#define USE_STRUCT_CSUM 1

#if (1 == USE_STRUCT_CSUM)
#define STRUCT_END_CSUM csum_t _csum;
#define STRUCT_COMPUTE_CSUM(s) ({ csum_t _c = CSUM_SEED; uint8_t *_p; for (_p = (uint8_t *) &s; _p < (uint8_t *) &s._csum; _p++) { _c += *_p; } _c; })
#define STRUCT_UPDATE_CSUM(s) s._csum = STRUCT_COMPUTE_CSUM(s)
#define STRUCT_CSUM_FAIL(s) if (s._csum != STRUCT_COMPUTE_CSUM(s)) { GUARD_FAIL(); }
#else
#define STRUCT_END_CSUM
#define STRUCT_UPDATE_CSUM(s)
#define STRUCT_CSUM_FAIL(s)
#endif

#define STRUCT_GUARD_START struct __attribute__((packed, aligned(4))) { STRUCT_START_GUARD
#define STRUCT_GUARD_END STRUCT_END_GUARD STRUCT_END_CSUM }
#endif /* __GUARD_H__ */