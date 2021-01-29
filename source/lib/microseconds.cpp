
#include "com/microseconds.hpp"

#include <cassert>
#include <cctype>    // std::isdigit
#include <iomanip>

#include "com/fatal_error.hpp"

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(microseconds));

static microseconds cast(std::string_view str) {
    auto c2i = [](char c) {
        if (!std::isdigit(c)) {
            FATAL_ERROR(c, "is not a digit");
        }
        return c - '0';
    };

    auto hrs = c2i(str[0]) * 10 + c2i(str[1]);

    auto min = c2i(str[3]) * 10 + c2i(str[4]);
    if (min >= 60) {
        FATAL_ERROR<std::overflow_error>("illegal minute value", min);
    }

    auto sec = c2i(str[6]) * 10 + c2i(str[7]);
    if (sec >= 60) {
        FATAL_ERROR<std::overflow_error>("illegal second value", sec);
    }

    auto us = c2i(str[9]) * 100000 + c2i(str[10]) * 10000 + c2i(str[11]) * 1000 + c2i(str[12]) * 100
            + c2i(str[13]) * 10 + c2i(str[14]);

    auto total = (hrs * 3600 + min * 60 + sec) * 1000000LL + us;
    return { total };
}

microseconds::microseconds(std::string_view str)
    : microseconds(cast(str)) {
}

}    // namespace miu::com

DEF_TO_STRING(miu::com::microseconds) {
    std::ostringstream ss;
    ss << v.count() << "us";
    return ss.str();
}
