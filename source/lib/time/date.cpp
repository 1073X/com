
#include "time/date.hpp"

#include <iomanip>
#include <sstream>

#include "com/fatal_error.hpp"

#include "civil_time.hpp"
#include "var_casting.hpp"

namespace miu::time {

date::date(days val)
    : details::date(val) {
}

date::date(rep yrs, rep mon, rep day)
    : date(details::days_from_civil(yrs, mon, day)) {
    if (yrs < 1970 || !mon || !day) {
        FATAL_ERROR<std::underflow_error>("illegal date components", yrs, mon, day);
    } else if (yrs > 9999 || mon > 12 || day > 31) {
        FATAL_ERROR<std::overflow_error>("illegal date components", yrs, mon, day);
    }
}

static date cast(std::string_view str) {
    auto c2i = [](char c) {
        if (!std::isdigit(c)) {
            FATAL_ERROR(c, "is not a digit in date string");
        }
        return c - '0';
    };

    auto yrs = c2i(str[0]) * 1000 + c2i(str[1]) * 100 + c2i(str[2]) * 10 + c2i(str[3]);
    auto mon = c2i(str[4]) * 10 + c2i(str[5]);
    auto day = c2i(str[6]) * 10 + c2i(str[7]);
    return { yrs, mon, day };
}

date::date(std::string_view yyyymmdd)
    : date(cast(yyyymmdd)) {
}

std::tuple<date::rep, date::rep, date::rep> date::ytd() const {
    return details::civil_from_days(time_since_epoch().count());
}

}    // namespace miu::time

namespace miu::com {
template<>
std::optional<time::date> variant::get() const {
    static time::var_casting<time::date> cast;

    switch (id()) {
    case type_id<time::date>::value:
        return *(time::date const*)this;
    case type_id<const char*>::value:
        return time::date { (const char*)*_value };
    case type_id<std::string>::value:
        return time::date { (const char*)_value };
    default:
        return cast(this);
    }
}

template<>
void variant::set<time::date>(time::date const& v) {
    new (_value)(time::date) { v };
}
}    // namespace miu::com

DEF_TO_STRING(miu::time::date) {
    std::ostringstream ss;
    auto [yrs, mon, day] = v.ytd();
    ss << yrs;
    ss << std::setw(2) << std::setfill('0') << mon;
    ss << std::setw(2) << std::setfill('0') << day;
    return ss.str();
}
