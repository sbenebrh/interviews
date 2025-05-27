//
// Created by samuel benibgui on 26/05/2025.
//

#include "Put.h"

#include <algorithm>

double infra::options::Put::payoff(const double S_t) const {
    return std::max(mStrike.value() - S_t, 0.0);
}

infra::options::Put::Put(const entities::Strike strike) : mStrike(strike){}
