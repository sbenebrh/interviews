#pragma once

#include "Option.h"

namespace infra::options {
    class Square: public domain::Option{
    public:
        [[nodiscard]] double payoff(double S_t) const override;
    };

}


