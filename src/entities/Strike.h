#pragma once
#include <stdexcept>

namespace entities {

class Strike {
    mutable double mValue;

public:
    explicit constexpr Strike(const double value) : mValue(value) {
        if (value <= 0.0) {
            mValue = 1.0; //TODO:: maybe not a good choice to set a default strike. the purpose of that is the invariant issue
            throw std::invalid_argument("Strike must be > 0");
        }
    }
    double value() const { return mValue; }

};

}

constexpr entities::Strike operator"" _strike(long double v) {
    return entities::Strike(static_cast<double>(v));
}