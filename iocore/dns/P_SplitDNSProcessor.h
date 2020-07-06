#pragma once

#include "ProxyConfig.h"

/* ---------------------------
   forward declarations ...
   --------------------------- */
void ink_split_dns_init(ModuleVersion version);

struct RequestData;

struct matcher_line;

class SplitDNSRecord;
struct SplitDNSResult;

struct DNSServer;

enum DNSResultType {
  DNS_SRVR_UNDEFINED = 0,
  DNS_SRVR_SPECIFIED,
  DNS_SRVR_FAIL,
};

typedef ControlMatcher<SplitDNSRecord, SplitDNSResult> DNS_table;

/* --------------------------------------------------------------
   **                struct SplitDNSResult
   -------------------------------------------------------------- */
struct SplitDNSResult {
  SplitDNSResult();

  /* ------------
     public
     ------------ */
  DNSResultType r;

  DNSServer *get_dns_record();
  int get_dns_srvr_count();

  /* ------------
     private
     ------------ */
  int m_line_number;

  SplitDNSRecord *m_rec;
  bool m_wrap_around;
};

/* --------------------------------------------------------------
   **                struct SplitDNS
   -------------------------------------------------------------- */
struct SplitDNS : public ConfigInfo {
  SplitDNS();
  ~SplitDNS() override;

  void *getDNSRecord(const char *hostname);
  void findServer(RequestData *rdata, SplitDNSResult *result);

  DNS_table *m_DNSSrvrTable;

  int32_t m_SplitDNSlEnable;

  /* ----------------------------
     required by the alleged fast
     path
     ---------------------------- */
  bool m_bEnableFastPath;
  void *m_pxLeafArray;
  int m_numEle;
};

/* --------------------------------------------------------------
   SplitDNSConfig::isSplitDNSEnabled()
   -------------------------------------------------------------- */
TS_INLINE bool
SplitDNSConfig::isSplitDNSEnabled()
{
  return (gsplit_dns_enabled ? true : false);
}

//
// End API to outside world
//

/* --------------------------------------------------------------
   **                class DNSRequestData

   A record for an single server
   -------------------------------------------------------------- */
class DNSRequestData : public RequestData
{
public:
  DNSRequestData();

  char *get_string();

  const char *get_host();

  sockaddr const *get_ip();        // unused required virtual method.
  sockaddr const *get_client_ip(); // unused required virtual method.

  const char *m_pHost;
};

/* --------------------------------------------------------------
   DNSRequestData::get_string()
   -------------------------------------------------------------- */
TS_INLINE
DNSRequestData::DNSRequestData() : m_pHost(nullptr) {}

/* --------------------------------------------------------------
   DNSRequestData::get_string()
   -------------------------------------------------------------- */
TS_INLINE char *
DNSRequestData::get_string()
{
  return ats_strdup((char *)m_pHost);
}

/* --------------------------------------------------------------
   DNSRequestData::get_host()
   -------------------------------------------------------------- */
TS_INLINE const char *
DNSRequestData::get_host()
{
  return m_pHost;
}

/* --------------------------------------------------------------
   DNSRequestData::get_ip()
   -------------------------------------------------------------- */
TS_INLINE sockaddr const *
DNSRequestData::get_ip()
{
  return nullptr;
}

/* --------------------------------------------------------------
   DNSRequestData::get_client_ip()
   -------------------------------------------------------------- */
TS_INLINE sockaddr const *
DNSRequestData::get_client_ip()
{
  return nullptr;
}

/* --------------------------------------------------------------
   *                 class SplitDNSRecord

   A record for a configuration line in the splitdns.config file
   -------------------------------------------------------------- */
class SplitDNSRecord : public ControlBase
{
public:
  SplitDNSRecord();
  ~SplitDNSRecord();

  Result Init(matcher_line *line_info);

  const char *ProcessDNSHosts(char *val);
  const char *ProcessDomainSrchList(char *val);
  const char *ProcessDefDomain(char *val);

  void UpdateMatch(SplitDNSResult *result, RequestData *rdata);
  void Print();

  DNSServer m_servers;
  int m_dnsSrvr_cnt;
  int m_domain_srch_list;
};

/* --------------------------------------------------------------
   SplitDNSRecord::SplitDNSRecord()
   -------------------------------------------------------------- */
TS_INLINE
SplitDNSRecord::SplitDNSRecord() : m_dnsSrvr_cnt(0), m_domain_srch_list(0) {}

/* --------------------------------------------------------------
   SplitDNSRecord::~SplitDNSRecord()
   -------------------------------------------------------------- */
TS_INLINE SplitDNSRecord::~SplitDNSRecord() {}

/* ------------------
   Helper Functions
   ------------------ */

SplitDNSRecord *createDefaultServer();
void reloadDefaultParent(char *val);
void reloadParentFile();
