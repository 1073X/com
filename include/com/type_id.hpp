#pragma once

#include <string>
#include <tuple>

namespace miu::com {

/// define type_id
static const uint8_t CUSTOM_TYPE_ID = 32;

template<typename>
struct type_id;

/// prevent duplicated type_id definition
class variant;

template<uint8_t ID>
struct type_id_guard;

/// type list
template<uint32_t>
struct managed_type;

}    // namespace miu::com

#define DEF_TYPE_ID(TYPE, ID)                               \
    template<>                                              \
    struct miu::com::type_id<TYPE> {                        \
        static uint8_t constexpr value { ID };              \
        static const char* name() { return #ID ":" #TYPE; } \
    };                                                      \
    template<>                                              \
    struct miu::com::managed_type<ID> {                     \
        using type = TYPE;                                  \
    };                                                      \
    template<>                                              \
    struct miu::com::type_id_guard<ID> {}

DEF_TYPE_ID(void, 255);
