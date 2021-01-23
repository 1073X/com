
#include "com/datetime.hpp"

#include "com/time_offset.hpp"

namespace miu::com {

static datetime cast(std::string_view str) {
    auto it = str.begin();
    std::string d { it, it + 8 };
    std::string t { it + 9, str.end() };
    return { { d }, { t } };
}

datetime::datetime(duration v)
    : datetime_base(v) {
}

datetime::datetime(class date d, daytime t)
    : datetime(d.time_since_epoch() + t.time_since_epoch()) {
}

datetime::datetime(date::rep year,
                   date::rep month,
                   date::rep day,
                   daytime::rep hour,
                   daytime::rep minute,
                   daytime::rep second,
                   daytime::rep microsec)
    : datetime({ year, month, day }, { hour, minute, second, microsec }) {
}

datetime::datetime(std::string_view v)
    : datetime(cast(v)) {
}

datetime datetime::now() {
    auto time = clock::now() + time_offset::get();
    return { time.time_since_epoch() };
}

datetime datetime::zero() {
    return datetime();
}
datetime datetime::min() {
    return zero();
}

class date datetime::date() const {
    return { time_since_epoch() / days_base(1) };
}

daytime datetime::time() const {
    return { time_since_epoch() - date().time_since_epoch() };
}

}    // namespace miu::com

namespace std {
string to_string(miu::com::datetime v) {
    return to_string(v.date()) + ' ' + to_string(v.time());
}
}    // namespace std
