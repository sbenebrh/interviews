#pragma once
#include <stdexcept>

namespace entities {

    class TimeToMaturity {
        mutable double mValue;

    public:
        explicit constexpr TimeToMaturity(const double value) : mValue(value) {
            if (value < 0.0) {
                mValue = 0.0;
                throw std::invalid_argument("TimeToMaturity value out of range");
            }
        }
        double value() const { return mValue; }

    };

}
constexpr entities::TimeToMaturity operator"" _maturity(long double v) {
    return entities::TimeToMaturity(static_cast<double>(v));
}