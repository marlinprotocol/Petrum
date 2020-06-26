#pragma once

#include "tscore/ink_platform.h"
#include "tscore/ink_defs.h"

#include "tscore/ink_apidefs.h"

int safe_setsockopt(int s, int level, int optname, char *optval, int optlevel);
int safe_getsockopt(int s, int level, int optname, char *optval, int *optlevel);
int safe_bind(int s, struct sockaddr const *name, int namelen);
int safe_listen(int s, int backlog);
int safe_getsockname(int s, struct sockaddr *name, int *namelen);
int safe_getpeername(int s, struct sockaddr *name, int *namelen);

int safe_fcntl(int fd, int cmd, int arg);
int safe_ioctl(int fd, int request, char *arg);

int safe_set_fl(int fd, int arg);
int safe_clr_fl(int fd, int arg);

int safe_blocking(int fd);
int safe_nonblocking(int fd);

int write_ready(int fd, int timeout_msec = 0);
int read_ready(int fd, int timeout_msec = 0);

char fd_read_char(int fd);
int fd_read_line(int fd, char *s, int len);

int close_socket(int s);
int write_socket(int s, const char *buffer, int length);
int read_socket(int s, char *buffer, int length);

inkcoreapi uint32_t ink_inet_addr(const char *s);

int bind_unix_domain_socket(const char *path, mode_t mode);
