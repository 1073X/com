
#include "com/date.hpp"

#include <iomanip>
#include <sstream>

#include "com/fatal_error.hpp"

#include "civil_time.hpp"

namespace miu::com {

static_assert(sizeof(int32_t) == sizeof(date));

static date
cast(std::string_view str) {
    auto c2i = [](char c) {
        if (!std::isdigit(c)) {
            FATAL_ERROR(c, "is not a digit in date string");
        }
        return c - '0';
    };

    auto yrs = c2i(str[0]) * 1000 + c2i(str[1]) * 100 + c2i(str[2]) * 10 + c2i(str[3]);
    auto mon = c2i(str[4]) * 10 + c2i(str[5]);
    auto day = c2i(str[6]) * 10 + c2i(str[7]);
    return date { yrs, mon, day };
}

date::date(duration val)
    : date_base(val) {}

date::date(rep yrs, rep mon, rep day)
    : date(miu::com::days_from_civil(yrs, mon, day)) {
    if (yrs < 1970 || !mon || !day) {
        FATAL_ERROR<std::underflow_error>("illegal date components", yrs, mon, day);
    } else if (yrs > 9999 || mon > 12 || day > 31) {
        FATAL_ERROR<std::overflow_error>("illegal date components", yrs, mon, day);
    }
}

date::date(std::string_view yyyymmdd)
    : date(cast(yyyymmdd)) {}

date
date::today() {
    using namespace std::chrono;

    constexpr rep day = 3600 * 24;

    std::time_t tm;
    rep sec = std::time(&tm);

    return date { sec / day };
}

date
date::zero() {
    return date();
}

date
date::min() {
    return zero();
}

std::tuple<date::rep, date::rep, date::rep>
date::civil_from_days() const {
    return miu::com::civil_from_days(time_since_epoch().count());
}

}    // namespace miu::com

namespace std {

std::string
to_string(miu::com::date date) {
    std::ostringstream ss;
    auto [years, months, days] = date.civil_from_days();
    ss << years << std::setw(2) << std::setfill('0') << months << std::setw(2) << std::setfill('0')
       << days;
    return ss.str();
}

}    // namespace std
