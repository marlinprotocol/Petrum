#pragma once

#include "P_DNS.h"
#include "I_SplitDNS.h"
#include "I_Lock.h"
#include "ControlBase.h"
#include "ControlMatcher.h"
#include "P_SplitDNSProcessor.h"

#undef SPLITDNS_MODULE_VERSION
#define SPLITDNS_MODULE_VERSION \
  makeModuleVersion(SPLITDNS_MODULE_MAJOR_VERSION, SPLITDNS_MODULE_MINOR_VERSION, PRIVATE_MODULE_HEADER)
