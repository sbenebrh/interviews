//
// Created by samuel benibgui on 26/05/2025.
//

#include "Square.h"

#include <algorithm>


double infra::options::Square::payoff(const double S_t) const {
    return std::pow(S_t,2);
}
