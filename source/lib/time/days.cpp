
#include "time/days.hpp"

#include "var_casting.hpp"

namespace miu::com {

template<>
std::optional<time::days> variant::get() const {
    static time::var_casting<time::days> cast;

    switch (id()) {
    case type_id<time::days>::value:
        return *(time::days const*)this;
    default:
        return cast(this);
    }
}

template<>
void variant::set<time::days>(time::days const& v) {
    new (_value)(time::days) { v };
}

}    // namespace miu::com

DEF_TO_STRING(miu::time::days) {
    return std::to_string(v.count()) + "d";
}
