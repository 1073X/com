#pragma once

#include <stdexcept>

namespace miu::com {

class fatal_error : public std::runtime_error {
  public:
    explicit fatal_error(std::string_view);
};

}    // namespace miu::com

extern void FATAL_ERROR(std::string_view msg);    // NOLINT
