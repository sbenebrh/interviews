//
// Created by samuel benibgui on 26/05/2025.
//

#include "Call.h"
#include <algorithm>

infra::options::Call::Call(const entities::Strike strike) :
mStrike(strike){}

double infra::options::Call::payoff(const double S_t) const {
    return std::max(S_t - mStrike.value(), 0.0);

}
