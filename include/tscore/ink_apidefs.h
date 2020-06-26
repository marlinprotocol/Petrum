#pragma once

#define inkliapi
#define inkcoreapi
#define ink_undoc_liapi
#define ink_undoc_coreapi inkcoreapi

#if defined(__GNUC__) || defined(__clang__)
#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif
#else
#ifndef likely
#define likely(x) (x)
#endif
#ifndef unlikely
#define unlikely(x) (x)
#endif
#endif

#if !defined(TS_NORETURN)
#if defined(__GNUC__) || defined(__clang__)
#define TS_NORETURN __attribute__((noreturn))
#else
#define TS_NORETURN
#endif
#endif

/*  Enable this to get printf() style warnings on the Inktomi functions. */
/* #define PRINTFLIKE(IDX, FIRST)  __attribute__((format (printf, IDX, FIRST))) */
#if !defined(TS_PRINTFLIKE)
#if defined(__GNUC__) || defined(__clang__)
#define TS_PRINTFLIKE(fmt, arg) __attribute__((format(printf, fmt, arg)))
#else
#define TS_PRINTFLIKE(fmt, arg)
#endif
#endif

#if !defined(TS_NONNULL)
#if defined(__GNUC__) || defined(__clang__)
#define TS_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
#define TS_NONNULL(...)
#endif
#endif

#if !defined(TS_INLINE)
#define TS_INLINE inline
#endif
