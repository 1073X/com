
#include "time/delta.hpp"

#include <iomanip>

#include "var_casting.hpp"

namespace miu::com {

template<>
std::optional<time::delta> variant::get() const {
    static time::var_casting<time::delta> cast;

    switch (id()) {
    case type_id<time::delta>::value:
        return *(time::delta const*)this;
    default:
        return cast(this);
    }
}

template<>
void variant::set<time::delta>(time::delta const& v) {
    new (_value)(time::delta) { v };
}

}    // namespace miu::com

DEF_TO_STRING(miu::time::delta) {
    std::ostringstream ss;
    ss << v.count() << "ms";
    return ss.str();
}
