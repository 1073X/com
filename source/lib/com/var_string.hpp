#pragma once

#include "com/reg_var_str.hpp"
#include "time/stamp.hpp"

#include "var_casting.hpp"

namespace miu::com {

class var_string : public var_casting<std::string> {
  public:
    static auto instance() { return &_instance; }

    bool enroll(uint8_t type_id, var_str_func const&);

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
