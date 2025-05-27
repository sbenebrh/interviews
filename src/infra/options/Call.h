#pragma once

#include "Strike.h"
#include "Option.h"

namespace infra::options {
class Call: public domain::Option{
    entities::Strike mStrike;
public:
    explicit Call(entities::Strike strike);
    [[nodiscard]] double payoff(double S_t) const override;
};
}


