#include <string_view>
#include <unordered_map>

#include "tscore/HashFNV.h"

/// Hash functor for @c string_view
inline size_t
TsLuaConfigSVHash(std::string_view const &sv)
{
  ATSHash64FNV1a h;
  h.update(sv.data(), sv.size());
  return h.get();
}

class TsEnumDescriptor
{
public:
  struct Pair {
    std::string_view key;
    int value;
  };
  TsEnumDescriptor(std::initializer_list<Pair> pairs) : values{pairs.size(), &TsLuaConfigSVHash}, keys{pairs.size()}
  {
    for (auto &p : pairs) {
      values[p.key] = p.value;
      keys[p.value] = p.key;
    }
  }
  std::unordered_map<std::string_view, int, size_t (*)(std::string_view const &)> values;
  std::unordered_map<int, std::string_view> keys;
  int
  get(std::string_view key)
  {
    auto it = values.find(key);
    if (it != values.end()) {
      return it->second;
    }
    return -1;
  }
};
