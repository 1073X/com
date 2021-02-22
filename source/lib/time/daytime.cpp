
#include "time/daytime.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "com/fatal_error.hpp"

#include "var_casting.hpp"

namespace miu::time {

daytime::daytime(delta v)
    : details::daytime(v) {
}

daytime::daytime(rep hrs, rep min, rep sec, rep ms)
    : daytime((3600 * hrs + 60 * min + sec) * 1000 + ms) {
    if (hrs < 0 || min < 0 || sec < 0 || ms < 0) {
        FATAL_ERROR<std::underflow_error>(hrs, min, sec, ms);
    }
    if (hrs > 23 || min > 59 || sec > 59 || ms > 999) {
        FATAL_ERROR<std::overflow_error>(hrs, min, sec, ms);
    }
}

static daytime cast(std::string_view str) {
    auto c2i = [](char c) {
        if (!std::isdigit(c)) {
            FATAL_ERROR(c, "is not a digit");
        }
        return c - '0';
    };

    auto hrs = c2i(str[0]) * 10 + c2i(str[1]);
    auto min = c2i(str[3]) * 10 + c2i(str[4]);
    auto sec = c2i(str[6]) * 10 + c2i(str[7]);
    auto ms  = c2i(str[9]) * 100 + c2i(str[10]) * 10 + c2i(str[11]);

    return { hrs, min, sec, ms };
}

daytime::daytime(std::string_view v)
    : daytime(cast(v)) {
}

}    // namespace miu::time

namespace miu::com {
template<>
std::optional<time::daytime> variant::get() const {
    static time::var_casting<time::daytime> cast;

    switch (id()) {
    case type_id<time::daytime>::value:
        return *(time::daytime const*)this;
    case type_id<const char*>::value:
        return time::daytime { (const char*)*_value };
    case type_id<std::string>::value:
        return time::daytime { (const char*)_value };
    default:
        return cast(this);
    }
}

template<>
void variant::set<time::daytime>(time::daytime const& v) {
    new (_value)(time::daytime) { v };
}
}    // namespace miu::com

DEF_TO_STRING(miu::time::daytime) {
    auto epoch = v.time_since_epoch().count();
    auto hrs   = epoch / (3600 * 1000);
    auto min   = (epoch % (3600 * 1000)) / (60 * 1000);
    auto sec   = (epoch % (60 * 1000)) / 1000;
    auto ms    = epoch % 1000;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << hrs;
    ss << ':' << std::setw(2) << std::setfill('0') << min;
    ss << ':' << std::setw(2) << std::setfill('0') << sec;
    ss << '.' << std::setw(3) << std::setfill('0') << ms;
    return ss.str();
}
