#pragma once

#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define KB(X) (u64)((X) * 1024)
#define MB(X) (u64)(KB(X) * 1024)
#define GB(X) (u64)(MB(X) * 1024)
#define TB(X) (u64)(GB(X) * 1024)

#ifdef DEBUG
#define ASSERT(X) if(!(X)) { *(int*)0 = 0; }
#else
#define ASSERT(X)
#endif
