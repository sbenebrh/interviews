#pragma once
#include "Model.h"

namespace infra::models {
    class NormalModel: public domain::Model {
    public:
        [[nodiscard]] double execute(double S, double sigma, double T, double X) const override;
    };
}
