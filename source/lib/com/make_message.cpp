
#include <sstream>

#include "meta/info.hpp"
#include "time/time.hpp"

namespace miu::com {

std::string make_message(std::string_view type) {
    auto time = miu::time::now();

    std::ostringstream ss;
    ss << '[' << to_string(time) << ' ' << type << ' ' << meta::info() << ']';
    return ss.str();
}

}    // namespace miu::com

