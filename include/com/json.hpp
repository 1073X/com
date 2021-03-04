#pragma once

#include <nlohmann/fifo_map.hpp>
#include <nlohmann/json.hpp>

namespace miu::com {

using ordered_json = nlohmann::json;

// https://github.com/nlohmann/json/issues/485#issuecomment-333652309
template<class K, class V, class dummy_compare, class A>
using fifo_map = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
using json     = nlohmann::basic_json<fifo_map>;

}    // namespace miu::com
