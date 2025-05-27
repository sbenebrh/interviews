#pragma once
#include <string>

#include "Option.h"
#include "Strike.h"

namespace infra::options {
    class Straddle: public domain::Option{
        entities::Strike mStrike;
    public:
        Straddle(entities::Strike strike);
        [[nodiscard]] double payoff(double S_t) const override;
    };
}


