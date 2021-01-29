#pragma once

#include <string>

namespace miu::meta {
extern std::string_view category();
extern std::string_view type();

extern std::string_view name();

std::string info();
}    // namespace miu::meta
