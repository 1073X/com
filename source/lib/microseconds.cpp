
#include "com/microseconds.hpp"

#include <cassert>
#include <cctype>    // std::isdigit

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(microseconds));

static microseconds
cast(std::string_view str) {
    auto c2i = [](char c) {
        assert(std::isdigit(c));
        return c - '0';
    };

    auto hours = c2i(str[0]) * 10 + c2i(str[1]);
    auto minutes = c2i(str[3]) * 10 + c2i(str[4]);
    auto seconds = c2i(str[6]) * 10 + c2i(str[7]);
    auto microsec = c2i(str[9]) * 100000 + c2i(str[10]) * 10000 + c2i(str[11]) * 1000
                    + c2i(str[12]) * 100 + c2i(str[13]) * 10 + c2i(str[14]);

    return { hours, minutes, seconds, microsec };
}

microseconds::microseconds(rep hours, rep minutes, rep seconds, rep microsec)
    : microseconds { (hours * 3600 + minutes * 60 + seconds) * 1000000 + microsec } {}

microseconds::microseconds(std::string_view str)
    : microseconds(cast(str)) {}

}    // namespace miu::com
