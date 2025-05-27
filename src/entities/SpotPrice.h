#pragma once
#include <stdexcept>

namespace entities {

    class SpotPrice {
        mutable double mValue;

    public:
        explicit constexpr SpotPrice(const double value) : mValue(value) {
            if (value < 0.0) {
                mValue = 0.0;
                throw std::invalid_argument("SpotPrice value out of range");
            }
        }
        double value() const { return mValue; }

    };

}
constexpr entities::SpotPrice operator"" _price(long double v) {
    return entities::SpotPrice(static_cast<double>(v));
}