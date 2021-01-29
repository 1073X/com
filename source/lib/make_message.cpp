
#include <sstream>

#include "com/datetime.hpp"
#include "com/to_string.hpp"
#include "meta/info.hpp"

namespace miu::com {

std::string make_message(std::string_view type) {
    auto time = miu::com::datetime::now();

    std::ostringstream ss;
    ss << '[' << to_string(time) << ' ' << type << ' ' << meta::info() << ']';
    return ss.str();
}

}    // namespace miu::com

