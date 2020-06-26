#pragma once

#include <openssl/x509.h>

/*
 * Validate that the certificate is for the specified hostname/IP address
 * @param cert The X509 certificate we match against
 * @param hostname Null terminated string that we want to match
 * @param is_ip Is the specified hostname an IP string
 * @param peername If not NULL, the matching value from the certificate will allocated and the ptr adjusted.
 *                 In this case caller must free afterwards with ats_free
 */

bool validate_hostname(X509 *cert, const unsigned char *hostname, bool is_ip, char **peername);
