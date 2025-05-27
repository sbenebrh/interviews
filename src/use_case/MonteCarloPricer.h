#pragma once

#include "RandomGeneratorType.h"
#include <vector>
#include <numeric>

#include "Model.h"
#include "Option.h"
#include "SpotPrice.h"
#include "Volatility.h"
#include "TimeToMaturity.h"


namespace use_case {


class MonteCarloPricer {
public:
    template< infra::rand_generator::RandomGeneratorType Generator>
    static double execute(const domain::Model& model, const domain::Option& option, Generator& rng,
        const entities::SpotPrice& S, const entities::Volatility& sigma, const entities::TimeToMaturity& T, int N) {
        std::vector<double> payoffs(N);
        for (int i = 0; i < N; i++) {
            const double X = rng.next();
            const double ST = model.execute(S.value(), sigma.value(), T.value(), X);
            payoffs[i] = option.payoff(ST);
        }

        return std::accumulate( payoffs.begin(), payoffs.end(), 0.0) / static_cast<double>(N);
    }

};
}
