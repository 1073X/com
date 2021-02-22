
#include "meta/info.hpp"

#include <cstring>    // std::strncpy

#include "com/fatal_error.hpp"
#include "com/strcat.hpp"

namespace miu::meta {

static char g_cate[16] = "UKN_CATE";
static char g_type[16] = "UKN_TYPE";
static char g_name[16] = "UKN_NAME";
static char g_info[64] = "UKN_CATE.UKN_TYPE.UKN_NAME";

const char* info() {
    return g_info;
}
void set_info() {
    std::snprintf(g_info, sizeof(g_info), "%s.%s.%s", g_cate, g_type, g_name);
}

const char* category() {
    return g_cate;
}
void set_category(std::string_view v) {
    if (v.size() < sizeof(g_cate)) {
        std::strncpy(g_cate, v.data(), sizeof(g_cate));
        set_info();
    } else {
        FATAL_ERROR<std::overflow_error>("category overflow [", v, "]");
    }
}

const char* type() {
    return g_type;
}
void set_type(std::string_view v) {
    if (v.size() < sizeof(g_type)) {
        std::strncpy(g_type, v.data(), sizeof(g_type));
        set_info();
    } else {
        FATAL_ERROR<std::overflow_error>("type overflow [", v, "]");
    }
}

const char* name() {
    return g_name;
}
void set_name(std::string_view v) {
    if (v.size() < sizeof(g_name)) {
        std::strncpy(g_name, v.data(), sizeof(g_name));
        set_info();
    } else {
        FATAL_ERROR<std::overflow_error>("name overflow [", v, "]");
    }
}

}    // namespace miu::meta
