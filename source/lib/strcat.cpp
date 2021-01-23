
#include "com/strcat.hpp"

namespace miu::com {

strcat::strcat(delimiter del)
    : _delimiter { std::move(del) } {
}

std::string strcat::str() const {
    auto it = _str.begin();
    return { it, it + _str.size() - _delimiter.val.size() };
}

void strcat::push(std::string_view v) {
    _str = v.data() + _delimiter.val + _str;
}

}    // namespace miu::com
