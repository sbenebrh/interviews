#pragma once
#include <stdexcept>

namespace entities {

class Volatility {
    mutable double mValue;

public:
    explicit constexpr Volatility(const double value) : mValue(value) {
        if (value < 0.0|| value > 1.0) {
            mValue = 0.0;
            throw std::invalid_argument("Volatility value out of range");
        }
    }
    double value() const { return mValue; }

};

}
constexpr entities::Volatility operator"" _vol(long double v) {
    return entities::Volatility(static_cast<double>(v));
}