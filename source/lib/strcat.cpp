
#include "com/strcat.hpp"

#include <sstream>

namespace miu::com {

strcat::strcat(delimiter del)
    : _delimiter { std::move(del) } {
}

std::string strcat::str() const {
    std::ostringstream ss;
    for (auto i = _vec.size() - 1; i > 0; i--) {
        ss << _vec[i] << _delimiter.val;
    }
    ss << _vec[0];
    return ss.str();
}

}    // namespace miu::com

DEF_TO_STRING(miu::com::strcat) {
    return v.str();
}
