
#include "time/stamp.hpp"

#include "com/strcat.hpp"

#include "var_casting.hpp"

namespace miu::time {

stamp::stamp(details::milliseconds v)
    : clock::time_point(v) {
}

stamp::stamp(clock::time_point v)
    : clock::time_point(v) {
}

stamp::stamp(class date d, daytime t)
    : stamp(details::milliseconds(d.time_since_epoch())
            + details::milliseconds(t.time_since_epoch())) {
}

stamp::stamp(date::rep yrs,
             date::rep mon,
             date::rep day,
             daytime::rep hrs,
             daytime::rep min,
             daytime::rep sec,
             daytime::rep ms)
    : stamp({ yrs, mon, day }, { hrs, min, sec, ms }) {
}

static stamp cast(std::string_view str) {
    auto it = str.begin();
    std::string d { it, it + 8 };
    std::string t { it + 9, str.end() };
    return { { d }, { t } };
}

stamp::stamp(std::string_view v)
    : stamp(cast(v)) {
}

class date stamp::date() const {
    return { std::chrono::floor<details::days>(time_since_epoch()) };
}

daytime stamp::time() const {
    return { time_since_epoch() - date().time_since_epoch() };
}

}    // namespace miu::time

namespace miu::com {
template<>
std::optional<time::stamp> variant::get() const {
    static time::var_casting<time::stamp> cast;

    switch (id()) {
    case type_id<time::stamp>::value:
        return *(time::stamp const*)this;
    case type_id<const char*>::value:
        return time::stamp { (const char*)*_value };
    default:
        return cast(this);
    }
}

template<>
void variant::set<time::stamp>(time::stamp const& v) {
    new (_value)(time::stamp) { v };
}
}    // namespace miu::com

DEF_TO_STRING(miu::time::stamp) {
    return strcat { v.date(), v.time(), strcat::delimiter { " " } }.str();
}
