
#include "com/strcat.hpp"

#include <sstream>

namespace miu::com {

strcat::strcat(delimiter del)
    : _delimiter { std::move(del) } {
}

uint32_t strcat::size() const {
    return _items.size();
}

std::string strcat::str() const {
    std::ostringstream ss;
    if (!_items.empty()) {
        auto it = _items.begin();
        for (auto i = 0U; i < _items.size() - 1; i++) {
            ss << *it++ << _delimiter.val;
        }
        ss << *it;
    }
    return ss.str();
}

}    // namespace miu::com

DEF_TO_STRING(miu::com::strcat) {
    return v.str();
}
