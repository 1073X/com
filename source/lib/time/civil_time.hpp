#pragma once

#include <cassert>
#include <chrono>
#include <tuple>

namespace miu::time::details {

//////////////////////////////////////////////////////////////
// https://stackoverflow.com/questions/16773285/how-to-convert-stdbasetime-point-to-stdtm-without-using-time-t
//

// Returns number of days since civil 1970-01-01.  Negative values
// indicate
//    days prior to 1970-01-01.
// Preconditions:
//     y-m-d represents a date in the civil (Gregorian) calendar
//     m is in [1, 12]
//     d is in [1, last_day_of_month(y, m)]
//     y is "approximately" in
//     [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
//     Exact range of validity is:
//     [civil_from_days(numeric_limits<Int>::min()),
//     civil_from_days(numeric_limits<Int>::max()-719468)]
template<class Int>
constexpr Int days_from_civil(Int y, unsigned m, unsigned d) noexcept {
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
                  "This algorithm has not been ported to a 16 bit "
                  "unsigned integer");
    static_assert(std::numeric_limits<Int>::digits >= 20,
                  "This algorithm has not been ported to a 16 bit "
                  "signed integer");
    y -= m <= 2;
    const Int ERA      = (y >= 0 ? y : y - 399) / 400;
    const unsigned YOE = static_cast<unsigned>(y - ERA * 400);              // [0, 399]
    const unsigned DOY = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;    // [0, 365]
    const unsigned DOE = YOE * 365 + YOE / 4 - YOE / 100 + DOY;             // [0, 146096]
    return ERA * 146097 + static_cast<Int>(DOE) - 719468;
}

// Returns year/month/day triple in civil calendar
// Preconditions:  z is number of days since 1970-01-01 and is in the
// range:
//                   [numeric_limits<Int>::min(),
//                   numeric_limits<Int>::max()-719468].
template<class Int>
constexpr std::tuple<Int, unsigned, unsigned> civil_from_days(Int z) noexcept {
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
                  "This algorithm has not been ported to a 16 bit "
                  "unsigned integer");
    static_assert(std::numeric_limits<Int>::digits >= 20,
                  "This algorithm has not been ported to a 16 bit "
                  "signed integer");
    z += 719468;
    const Int ERA      = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned DOE = static_cast<unsigned>(z - ERA * 146097);                  // [0, 146096]
    const unsigned YOE = (DOE - DOE / 1460 + DOE / 36524 - DOE / 146096) / 365;    // [0, 399]
    const Int Y        = static_cast<Int>(YOE) + ERA * 400;
    const unsigned DOY = DOE - (365 * YOE + YOE / 4 - YOE / 100);    // [0, 365]
    const unsigned MP  = (5 * DOY + 2) / 153;                        // [0, 11]
    const unsigned D   = DOY - (153 * MP + 2) / 5 + 1;               // [1, 31]
    const unsigned M   = MP + (MP < 10 ? 3 : -9);                    // [1, 12]
    return std::tuple<Int, unsigned, unsigned>(Y + (M <= 2), M, D);
}

template<class Int>
constexpr unsigned weekday_from_days(Int z) noexcept {
    return static_cast<unsigned>(z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6);
}

template<class To, class Rep, class Period>
To round_down(const std::chrono::duration<Rep, Period>& d) {
    To t = std::chrono::duration_cast<To>(d);
    if (t > d) {
        --t;
    }
    return t;
}

}    // namespace miu::time::details
