#pragma once

#include <cstring>

size_t ats_hugepage_size(void);
bool ats_hugepage_enabled(void);
void ats_hugepage_init(int);
void *ats_alloc_hugepage(size_t);
bool ats_free_hugepage(void *, size_t);
