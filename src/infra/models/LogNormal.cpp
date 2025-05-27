//
// Created by samuel benibgui on 26/05/2025.
//

#include "LogNormal.h"

#include <valarray>

double infra::models::LogNormalModel::execute(const double S, const double sigma, const double T, const double X) const {
    return S * std::exp(-0.5 * std::pow(sigma,2) * T + sigma * X * std::sqrt(T));
}
