#pragma once

#include <optional>

#include "predict.hpp"
#include "system_warn.hpp"
#include "type_id.hpp"

namespace miu::com {

class variant {
  public:
    variant()
        : _id { type_id<void>::value } {}

    variant(std::string_view const&);
    variant(std::string const&);

    template<typename T>
    variant(T const& v)
        : _id { type_id<T>::value } {
        set(v);
    }

    template<typename T>
    std::optional<T> get() const {
        if (UNLIKELY(type_id<T>::value != _id)) {
            SYSTEM_WARN("UNSUPPORTED", _id, ":some_type cannot be", type_id<T>::name);
            return std::nullopt;
        }
        return *(T const*)_value;
    }

    auto id() const { return _id; }

  private:
    template<typename T>
    void set(T const& v) {
        new (_value) T { v };
    }

    auto extra() const { return _extra; }

  private:
    uint64_t _value[1] {};
    uint8_t _extra[7] {};
    uint8_t _id { 0 };
};
static_assert(sizeof(variant) == 16);

template<>
std::optional<bool> variant::get<bool>() const;

template<>
std::optional<int64_t> variant::get<int64_t>() const;
template<>
std::optional<int32_t> variant::get<int32_t>() const;
template<>
std::optional<int16_t> variant::get<int16_t>() const;
template<>
std::optional<int8_t> variant::get<int8_t>() const;

template<>
std::optional<uint64_t> variant::get<uint64_t>() const;
template<>
std::optional<uint32_t> variant::get<uint32_t>() const;
template<>
std::optional<uint16_t> variant::get<uint16_t>() const;
template<>
std::optional<uint8_t> variant::get<uint8_t>() const;

template<>
std::optional<float> variant::get<float>() const;
template<>
std::optional<double> variant::get<double>() const;

template<>
std::optional<const char*> variant::get<const char*>() const;
template<>
std::optional<std::string> variant::get<std::string>() const;

}    // namespace miu::com
