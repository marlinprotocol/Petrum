#pragma once

#include <stdarg.h>
#include <stdio.h>
#include "tscore/ink_platform.h"
#include "tscore/ink_apidefs.h"

// throw isn't available in every libc (musl, ..)
#ifndef __THROW
#define __THROW
#endif

// This magic exit code is used to signal that the crashing process cannot
// be recovered from a restart of said process
//
// Originally, this was intended to be used as a backchannel mechanism whereby
// traffic_server can tell traffic_manager via an exit code to stop trying to restart
// traffic_server b/c (for example) traffic_server has a bad config file
#define UNRECOVERABLE_EXIT 33

void ink_emergency_va(const char *fmt, va_list ap) TS_NORETURN;
void ink_emergency(const char *message_format, ...) TS_PRINTFLIKE(1, 2) TS_NORETURN;
void ink_fatal_va(const char *message_format, va_list ap) TS_NORETURN;
void ink_fatal(const char *message_format, ...) TS_PRINTFLIKE(1, 2) TS_NORETURN;
void ink_abort(const char *message_format, ...) TS_PRINTFLIKE(1, 2) TS_NORETURN;
void ink_warning(const char *message_format, ...) TS_PRINTFLIKE(1, 2);
void ink_pwarning(const char *message_format, ...) TS_PRINTFLIKE(1, 2);
void ink_notice(const char *message_format, ...) TS_PRINTFLIKE(1, 2);
void ink_eprintf(const char *message_format, ...) TS_PRINTFLIKE(1, 2);
void ink_error(const char *message_format, ...) TS_PRINTFLIKE(1, 2);

int ink_set_dprintf_level(int debug_level);
