
#include "com/microseconds.hpp"

#include <cassert>
#include <cctype>    // std::isdigit
#include <iomanip>
#include <sstream>

#include "com/fatal_error.hpp"

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(microseconds));

static microseconds
cast(std::string_view str) {
    auto c2i = [](char c) {
        if (!std::isdigit(c)) {
            FATAL_ERROR(c, "is not a digit");
        }
        return c - '0';
    };

    auto hours = c2i(str[0]) * 10 + c2i(str[1]);
    auto minutes = c2i(str[3]) * 10 + c2i(str[4]);
    auto seconds = c2i(str[6]) * 10 + c2i(str[7]);
    auto microsec = c2i(str[9]) * 100000 + c2i(str[10]) * 10000 + c2i(str[11]) * 1000
                    + c2i(str[12]) * 100 + c2i(str[13]) * 10 + c2i(str[14]);

    auto total = (hours * 3600 + minutes * 60 + seconds) * 1000000LL + microsec;
    return { total };
}

microseconds::microseconds(std::string_view str)
    : microseconds(cast(str)) {}

}    // namespace miu::com

namespace std {

string
to_string(miu::com::microseconds val) {
    auto hrs = val.count() / (3600 * 1000000LL);
    auto min = (val.count() % (3600 * 1000000LL)) / (60 * 1000000);
    auto sec = (val.count() % (60 * 1000000LL)) / 1000000;
    auto microsec = val.count() % 1000000;

    ostringstream ss;
    ss << setw(2) << setfill('0') << hrs;
    ss << ':' << setw(2) << setfill('0') << min;
    ss << ':' << setw(2) << setfill('0') << sec;
    ss << '.' << setw(6) << setfill('0') << microsec;
    return ss.str();
}

}    // namespace std
