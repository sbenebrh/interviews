#pragma once

namespace domain {
struct Option {
    [[nodiscard]] virtual double payoff(double S_t) const = 0;
    virtual ~Option() = default;
};

}