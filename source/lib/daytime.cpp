
#include "com/daytime.hpp"

#include <iomanip>
#include <sstream>

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(daytime));

daytime::daytime(duration v)
    : daytime_base(v.count()) {}

daytime::daytime(rep hours, rep minutes, rep seconds, rep microsec)
    : daytime((3600 * hours + 60 * minutes + seconds) * 1000000LL + microsec) {}

daytime::daytime(std::string_view v)
    : daytime(duration { v }) {}

daytime
daytime::now() {
    using namespace std::chrono_literals;
    auto time = std::chrono::system_clock::now();
    return { time.time_since_epoch() % 24h };
}

}    // namespace miu::com

namespace std {

string
to_string(miu::com::daytime time) {
    auto epoch = time.time_since_epoch().count();
    auto hrs = epoch / (3600 * 1000000LL);
    auto min = (epoch % (3600 * 1000000LL)) / (60 * 1000000);
    auto sec = (epoch % (60 * 1000000LL)) / 1000000;
    auto microsec = epoch % 1000000;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << hrs;
    ss << ':' << std::setw(2) << std::setfill('0') << min;
    ss << ':' << std::setw(2) << std::setfill('0') << sec;
    ss << '.' << std::setw(6) << std::setfill('0') << microsec;
    return ss.str();
}

}    // namespace std
