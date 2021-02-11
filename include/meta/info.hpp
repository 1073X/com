#pragma once

#include <string_view>

namespace miu::meta {
extern std::string_view category();
extern void set_category(std::string_view);

extern std::string_view type();
extern void set_type(std::string_view);

extern std::string_view name();
extern void set_name(std::string_view);

std::string_view info();
}    // namespace miu::meta
