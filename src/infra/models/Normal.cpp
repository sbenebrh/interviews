#include "Normal.h"
#include <algorithm>

double infra::models::NormalModel::execute(const double S, const double sigma, const double T, const double X) const {
    return S + sigma * X * std::sqrt(T);
}
