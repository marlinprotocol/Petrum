#pragma once

struct SplitDNS;

/* --------------------------------------------------------------
   **                struct SplitDNSConfig
   -------------------------------------------------------------- */

struct SplitDNSConfig {
  static void startup();

  static bool isSplitDNSEnabled();

  static void reconfigure();
  static SplitDNS *acquire();
  static void release(SplitDNS *params);
  static void print();

  static int m_id;
  static Ptr<ProxyMutex> dnsHandler_mutex;
  static ConfigUpdateHandler<SplitDNSConfig> *splitDNSUpdate;

  static int gsplit_dns_enabled;
};
