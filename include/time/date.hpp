#pragma once

#include <tuple>

#include "clock.hpp"
#include "delta.hpp"

namespace miu::time {

namespace details {
    using date = std::chrono::time_point<clock, days>;
}

class date : public details::date {
  public:
    date(days = 0);
    date(rep yrs, rep mon, rep day);
    date(std::string_view yyyymmdd);

    std::tuple<rep, rep, rep> ytd() const;
};
static_assert(sizeof(int32_t) == sizeof(date));

}    // namespace miu::time

DEF_VARIANT(miu::time::date, 19);
