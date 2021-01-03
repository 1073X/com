
#include "com/fatal_error.hpp"

namespace miu::com {

fatal_error::fatal_error(std::string_view msg)
    : std::runtime_error(msg.data()) {}

}    // namespace miu::com

void
FATAL_ERROR(std::string_view msg) {    // NOLINT
    throw miu::com::fatal_error { msg };
}
