#pragma once

#include <string_view>

namespace miu::meta {
extern const char* category();
extern void set_category(std::string_view);

extern const char* type();
extern void set_type(std::string_view);

extern const char* name();
extern void set_name(std::string_view);

extern const char* info();
}    // namespace miu::meta
