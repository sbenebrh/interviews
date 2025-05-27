//
// Created by samuel benibgui on 26/05/2025.
//

#include "Straddle.h"

double infra::options::Straddle::payoff(const double S_t) const {
    return std::abs(S_t - mStrike.value());
}

infra::options::Straddle::Straddle(const entities::Strike strike) : mStrike(strike) {}
