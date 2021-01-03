#include "com/date.hpp"

#include <iomanip>
#include <sstream>

#include "civil_time.hpp"

namespace miu::com {

static_assert(sizeof(int32_t) == sizeof(date));

static date
cast(std::string_view str) {
    auto c2i = [](char c) {
        assert(std::isdigit(c));
        return c - '0';
    };

    auto year = c2i(str[0]) * 1000 + c2i(str[1]) * 100 + c2i(str[2]) * 10 + c2i(str[3]);
    auto month = c2i(str[4]) * 10 + c2i(str[5]);
    auto day = c2i(str[6]) * 10 + c2i(str[7]);
    return date { year, month, day };
}

date::date(duration val)
    : date_base(val) {}

date::date(rep years, rep months, rep days)
    : date(miu::com::days_from_civil(years, months, days)) {}

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
