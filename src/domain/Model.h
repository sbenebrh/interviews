#pragma once

namespace domain {
struct Model {
    [[nodiscard]] virtual double execute(double S, double sigma, double T, double X) const = 0;
    virtual ~Model() = default;
};

}
