#pragma once

#include <cstdio>
#include <cstdarg>
#include "tscore/ink_apidefs.h"
#include "tscore/ink_defs.h"

int ink_bsprintf(char *buffer, const char *format, ...) TS_PRINTFLIKE(2, 3);
int ink_bvsprintf(char *buffer, const char *format, va_list ap);
