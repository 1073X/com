#pragma once

#include "date.hpp"
#include "daytime.hpp"

namespace miu::time {

namespace details {
    struct milliseconds : public clock::duration {
        milliseconds(rep v)
            : clock::duration(v) {}

        template<typename R, typename P>
        milliseconds(std::chrono::duration<R, P> const& du)
            : milliseconds(std::chrono::duration_cast<clock::duration>(du).count()) {}
    };
}    // namespace details

class stamp : public clock::time_point {
  public:
    stamp(details::milliseconds = 0);
    stamp(clock::time_point);
    stamp(date, daytime);
    stamp(date::rep yrs,
          date::rep mon,
          date::rep day,
          daytime::rep hrs,
          daytime::rep min,
          daytime::rep sec,
          daytime::rep ms);
    stamp(std::string_view);

    class date date() const;
    daytime time() const;
};

}    // namespace miu::time

DEF_VARIANT(miu::time::stamp, 21);
