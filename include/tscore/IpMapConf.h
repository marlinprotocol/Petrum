#pragma once

class IpMap; // declare in name only.

// Returns 0 if successful, error string otherwise
int read_addr(char *line, int n, int *i, sockaddr *addr, char *err);
// Returns 0 if successful, error string otherwise
char *Load_IpMap_From_File(IpMap *map, int fd, char const *key_str);
// Returns 0 if successful, error string otherwise
char *Load_IpMap_From_File(IpMap *map, FILE *f, char const *key_str);
