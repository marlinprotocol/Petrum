#pragma once

#include "tscore/ink_apidefs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* don't use assert, no really DON'T use assert */
#undef assert
#define assert __DONT_USE_BARE_assert_USE_ink_assert__
#undef _ASSERT_H
#define _ASSERT_H
#undef __ASSERT_H__
#define __ASSERT_H__

inkcoreapi void _ink_assert(const char *a, const char *f, int l) TS_NORETURN;

#if defined(DEBUG) || defined(__clang_analyzer__) || defined(__COVERITY__)
#define ink_assert(EX) ((void)(__builtin_expect(!!(EX), 1) ? (void)0 : _ink_assert(#EX, __FILE__, __LINE__)))
#else
#define ink_assert(EX) (void)(EX)
#endif

#define ink_release_assert(EX) ((void)(__builtin_expect(!!(EX), 0) ? (void)0 : _ink_assert(#EX, __FILE__, __LINE__)))

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* workaround a bug in the  stupid Sun preprocessor

#undef assert
#define assert __DONT_USE_BARE_assert_USE_ink_assert__
#define _ASSERT_H
#undef __ASSERT_H__
#define __ASSERT_H__
*/
