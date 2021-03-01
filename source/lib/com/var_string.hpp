#pragma once

#include "time/stamp.hpp"

#include "var_casting.hpp"

namespace miu::com {

class var_string : public var_casting<std::string> {
  public:
    static auto instance() { return &_instance; }

    auto cast(variant const* var) const { return operator()(var); }

    void accept(uint8_t type_id, std::function<std::string(variant const*)> const& func) {
        support(type_id, [func](auto var) -> std::optional<std::string> { return func(var); });
    }

  private:
    var_string();

    template<typename source_type>
    void accept() {
        auto id = type_id<source_type>::value;
        support(id, [](auto var) { return to_string(*(source_type const*)var); });
    }

  private:
    static var_string _instance;
};

}    // namespace miu::com
