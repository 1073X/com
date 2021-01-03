#pragma once

#include <tuple>

#include "days.hpp"

namespace miu::com {

using date_base = std::chrono::time_point<std::chrono::system_clock, days>;
class date : public date_base {
  public:
    date(rep val = 0);
    date(rep years, rep months, rep days);
    date(std::string_view yyyymmdd);

    static date today();

    std::tuple<rep, rep, rep> civil_from_days() const;
};

}    // namespace miu::com

namespace std {
std::string to_string(miu::com::date);
}
