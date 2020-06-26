#pragma once

#include <sys/resource.h>

rlim_t ink_max_out_rlimit(int which);
rlim_t ink_get_max_files();
