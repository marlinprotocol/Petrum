#pragma once

// The max number of levels in the stack trace
#define INK_STACK_TRACE_MAX_LEVELS 100

#ifdef __cplusplus
extern "C" {
#endif
/* dumps the current back trace to stderr */
void ink_stack_trace_dump();
#ifdef __cplusplus
}
#endif
