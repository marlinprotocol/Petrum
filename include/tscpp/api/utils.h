#pragma once

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>

#ifndef ATSCPPAPI_UNUSED
#ifdef __GNUC__
#define ATSCPPAPI_UNUSED __attribute__((unused))
#else
#define ATSCPPAPI_UNUSED
#endif
#endif

namespace atscppapi
{
namespace utils
{
  /**
   * @brief Returns a pretty printed string of a sockaddr *
   *
   * @param sockaddr* A pointer to a sockaddr *
   * @return a string which is the pretty printed address
   */
  std::string getIpString(const sockaddr *);

  /**
   * @brief Returns just the port portion of the sockaddr *
   *
   * @param sockaddr* A pointer to a sockaddr *
   * @return a uint16_t which is the port from the sockaddr *
   */
  uint16_t getPort(const sockaddr *);

  /**
   * @brief Returns a pretty printed string of a sockaddr * including port
   *
   * @param sockaddr* A pointer to a sockaddr *
   * @return a string which is the pretty printed address including port
   */
  std::string getIpPortString(const sockaddr *);
} // namespace utils
} // namespace atscppapi
