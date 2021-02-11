
#include "meta/info.hpp"

#include <cstring>    // std::strncpy

#include "com/strcat.hpp"

namespace miu::meta {

static char g_category[64] = "UKN_CATE";
static char g_type[64]     = "UKN_TYPE";
static char g_name[64]     = "UKN_NAME";
static char g_info[256]    = "UKN_CATE.UKN_TYPE.UKN_NAME";

const char* info() {
    return g_info;
}
void set_info() {
    std::snprintf(g_info, sizeof(g_info), "%s.%s.%s", g_category, g_type, g_name);
}

const char* category() {
    return g_category;
}
void set_category(std::string_view v) {
    std::strncpy(g_category, v.data(), sizeof(g_category));
    set_info();
}

const char* type() {
    return g_type;
}
void set_type(std::string_view v) {
    std::strncpy(g_type, v.data(), sizeof(g_type));
    set_info();
}

const char* name() {
    return g_name;
}
void set_name(std::string_view v) {
    std::strncpy(g_name, v.data(), sizeof(g_name));
    set_info();
}

}    // namespace miu::meta
