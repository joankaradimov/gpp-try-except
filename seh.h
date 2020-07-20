#include <Windows.h>

// TODO: implement for x86 32 bit

bool exception_occured;

#if defined(__x86_64)

#define __try                                                         \
{                                                                     \
    __label__ l_start, l_end, l_handler, l_block, l_skip_block;       \
    __asm__ __volatile__ goto(                                        \
        ".seh_handler __C_specific_handler, @except\n\t"              \
        ".seh_handlerdata\n\t"                                        \
        ".long 1\n\t"                                                 \
        ".rva %l[l_start], %l[l_end], %l[l_handler], %l[l_block]\n\t" \
        ".text" :::: l_start, l_end, l_handler, l_block);             \
    l_start:

#define __except(filter)                                                  \
    l_end:                                                                \
    __leave;                                                              \
    l_handler:                                                            \
    {                                                                     \
        EXCEPTION_POINTERS *ep;                                           \
        __asm__ __volatile__("push %%rdi" : "=c"(ep) ::);                 \
        auto er = ep->ExceptionRecord;                                    \
        auto _exception_code = [er] { return er->ExceptionCode; };        \
        auto _exception_info = [er] { return er->ExceptionInformation; }; \
        __asm__ __volatile__(                                             \
            "pop %%rdi\n\t"                                               \
            "ret" :: "a"(filter));                      \
    }                                                                     \
    l_block:                                                              \
    exception_occured = true;                                             \
    l_skip_block:;                                                        \
}                                                                         \
if (exception_occured)

#else

#define __try       \
{                   \
    goto l_seh_end:

#define __except(filter)

#endif

#define __leave exception_occured = false; goto l_skip_block;

#define _try __try
#define _except __except
#define _leave __leave
