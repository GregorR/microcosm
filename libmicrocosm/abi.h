/* calling convention for GCC */

#ifndef ABI_H
#define ABI_H

#ifdef __GNUC__
#if (defined(__i386__) || defined(__i386) || defined(_M_IX86) || defined(_X86_)) && \
    !(defined(__x86_64__) || defined(_M_X64))
#define MC_ABI __attribute__((cdecl))
#elif defined(__x86_64__) || defined(_M_X64)
#define MC_ABI __attribute__((sysv_abi))
#else
#define MC_ABI
#endif

#else
#define MC_ABI

#endif

#endif
