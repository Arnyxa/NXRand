#pragma once

#if defined __x86_64__ || defined _M_AMD64 || defined __IA64__ || defined _M_IA64 || __ppc64__ || _M_PPC
#define NX64
#elif defined _WIN32 || defined _M_IX86 || defined _X86_ || defined __MINGW32_MAJOR_VERSION || defined __MINGW32_MINOR_VERSION || defined __i386__
#define NX32
#else
#define NXUNKNOWN
#endif