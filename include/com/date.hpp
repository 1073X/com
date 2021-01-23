#pragma once

#include <tuple>

#include "days.hpp"

namespace miu::com {

using date_base = std::chrono::time_point<std::chrono::system_clock, days>;
class date : public date_base {
  public:
    date(duration = { 0 });
    date(rep yrs, rep mon, rep day);
    date(std::string_view yyyymmdd);

    static date today();
    static date min();
    static date zero();

    std::tuple<rep, rep, rep> civil_from_days() const;
};

template<>
std::string to_string<date>(date const&);

}    // namespace miu::com
