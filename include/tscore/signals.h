#pragma once

typedef void (*signal_handler_t)(int signo, siginfo_t *info, void *ctx);

// Default crash signal handler that dumps a stack trace and exits.
void signal_crash_handler(int, siginfo_t *, void *);

// Attach a signal handler to fatal crash signals.
void signal_register_crash_handler(signal_handler_t);
// Attach a signal handler to the default et of signals we care about.
void signal_register_default_handler(signal_handler_t);

// Format a siginfo_t into an informative(?) message on stderr.
void signal_format_siginfo(int signo, siginfo_t *, const char *);

// Test whether a signal indicates a process crashing.
bool signal_is_crash(int signo);

// Test whether the signal is masked.
bool signal_is_masked(int signo);

// Test whether the signal is being handled by the given handler.
bool signal_check_handler(int signo, signal_handler_t handler);

// Start a thread to test whether signals have the expected handler. Apparantly useful for
// finding pthread bugs in some version of DEC Unix.
void signal_start_check_thread(signal_handler_t handler);
