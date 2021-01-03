#pragma once

#include "date.hpp"
#include "daytime.hpp"

namespace miu::com {

using datetime_base = std::chrono::time_point<std::chrono::system_clock, microseconds>;
class datetime : public datetime_base {
  public:
    datetime(duration = { 0 });
    datetime(date, daytime);
    datetime(date::rep year,
             date::rep month,
             date::rep day,
             daytime::rep hour,
             daytime::rep minute,
             daytime::rep second,
             daytime::rep microsec);
    datetime(std::string_view);

    class date date() const;
    daytime time() const;
};

}    // namespace miu::com

namespace std {
string to_string(miu::com::datetime);
}
