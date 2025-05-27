#pragma once
#include "Option.h"

#include "Strike.h"

namespace infra::options {
    class Put: public domain::Option{
        entities::Strike mStrike;
    public:
        Put(entities::Strike strike);
        [[nodiscard]] double payoff(double S_t) const override;
    };
}


