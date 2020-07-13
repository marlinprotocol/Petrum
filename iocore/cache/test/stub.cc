#include "HttpSessionManager.h"
#include "HttpBodyFactory.h"
#include "DiagsConfig.h"
#include "ts/InkAPIPrivateIOCore.h"

void
initialize_thread_for_http_sessions(EThread *, int)
{
  ink_assert(false);
}

#include "InkAPIInternal.h"
void
APIHooks::append(INKContInternal *cont)
{
}

int
APIHook::invoke(int, void *)
{
  ink_assert(false);
  return 0;
}

APIHook *
APIHook::next() const
{
  ink_assert(false);
  return nullptr;
}

APIHook *
APIHooks::get() const
{
  return nullptr;
}

void
APIHooks::prepend(INKContInternal *cont)
{
}

void
APIHooks::clear()
{
}

void
ConfigUpdateCbTable::invoke(const char * /* name ATS_UNUSED */)
{
  ink_release_assert(false);
}

HttpAPIHooks *http_global_hooks        = nullptr;
SslAPIHooks *ssl_hooks                 = nullptr;
LifecycleAPIHooks *lifecycle_hooks     = nullptr;
ConfigUpdateCbTable *global_config_cbs = nullptr;

HttpBodyFactory *body_factory = nullptr;

intmax_t
ts::svtoi(TextView src, TextView *out, int base)
{
  intmax_t zret = 0;

  if (out) {
    out->clear();
  }
  if (!(0 <= base && base <= 36)) {
    return 0;
  }
  if (src.ltrim_if(&isspace) && src) {
    const char *start = src.data();
    int8_t v;
    bool neg = false;
    if ('-' == *src) {
      ++src;
      neg = true;
    }
    // If base is 0, it wasn't specified - check for standard base prefixes
    if (0 == base) {
      base = 10;
      if ('0' == *src) {
        ++src;
        base = 8;
        if (src && ('x' == *src || 'X' == *src)) {
          ++src;
          base = 16;
        }
      }
    }

    // For performance in common cases, use the templated conversion.
    switch (base) {
    case 8:
      zret = svto_radix<8>(src);
      break;
    case 10:
      zret = svto_radix<10>(src);
      break;
    case 16:
      zret = svto_radix<16>(src);
      break;
    default:
      while (src.size() && (0 <= (v = svtoi_convert[static_cast<unsigned char>(*src)])) && v < base) {
        auto n = zret * base + v;
        if (n < zret) {
          zret = std::numeric_limits<uintmax_t>::max();
          break; // overflow, stop parsing.
        }
        zret = n;
        ++src;
      }
      break;
    }

    if (out && (src.data() > (neg ? start + 1 : start))) {
      out->assign(start, src.data());
    }

    if (neg) {
      zret = -zret;
    }
  }
  return zret;
}

void
HostStatus::setHostStatus(const char *name, HostStatus_t status, const unsigned int down_time, const unsigned int reason)
{
}

HostStatRec *
HostStatus::getHostStatus(const char *name)
{
  return nullptr;
}

void
HostStatus::createHostStat(const char *name, const char *data)
{
}

HostStatus::HostStatus() {}

HostStatus::~HostStatus() {}

int auto_clear_hostdb_flag = 0;
bool ts_is_draining        = false;

void
INKVConnInternal::do_io_close(int error)
{
}

void
INKVConnInternal::do_io_shutdown(ShutdownHowTo_t howto)
{
}

VIO *
INKVConnInternal::do_io_write(Continuation *c, int64_t nbytes, IOBufferReader *buf, bool owner)
{
  return nullptr;
}

VIO *
INKVConnInternal::do_io_read(Continuation *c, int64_t nbytes, MIOBuffer *buf)
{
  return nullptr;
}

void
INKVConnInternal::destroy()
{
}

void
INKVConnInternal::free()
{
}

void
INKVConnInternal::clear()
{
}

void
INKVConnInternal::reenable(VIO * /* vio ATS_UNUSED */)
{
}

bool
INKVConnInternal::get_data(int id, void *data)
{
  return false;
}

bool
INKVConnInternal::set_data(int id, void *data)
{
  return false;
}

void
INKVConnInternal::do_io_transform(VConnection *vc)
{
}

void
INKContInternal::handle_event_count(int event)
{
}

void
INKVConnInternal::retry(unsigned int delay)
{
}

INKContInternal::INKContInternal(TSEventFunc funcp, TSMutex mutexp) : DummyVConnection((ProxyMutex *)mutexp) {}

INKContInternal::INKContInternal() : DummyVConnection(nullptr) {}

void
INKContInternal::destroy()
{
}

void
INKContInternal::clear()
{
}

void
INKContInternal::free()
{
}

INKVConnInternal::INKVConnInternal() : INKContInternal() {}

INKVConnInternal::INKVConnInternal(TSEventFunc funcp, TSMutex mutexp) : INKContInternal(funcp, mutexp) {}