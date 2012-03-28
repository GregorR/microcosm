/* calling convention for GCC */

#ifndef MICROCOSMABI_H
#define MICROCOSMABI_H

#ifdef __GNUC__

#if (defined(__i386__) || defined(__i386) || defined(_M_IX86) || defined(_X86_)) && \
    !(defined(__x86_64__) || defined(_M_X64))
#define MC_ABI __attribute__((cdecl))
#define MC_STRUCT(x) x __attribute__((aligned(4), packed))

#elif defined(__x86_64__) || defined(_M_X64)
#define MC_ABI __attribute__((sysv_abi))
#define MC_STRUCT(x) x

#else
#define MC_ABI
#define MC_STRUCT(x) x

#endif

#define VISIBLE __attribute__((visibility("default")))
#define INTERNAL __attribute__((visibility("internal")))

#else
#define MC_ABI
#define VISIBLE
#define INTERNAL

#endif

#endif
