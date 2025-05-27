#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Volatility.h"
#include "Strike.h"

#include "Option.h"
#include "Call.h"
#include "Put.h"
#include "Straddle.h"
#include "Square.h"

#include "Model.h"
#include "LogNormal.h"
#include "Normal.h"

using ::testing::Return;

using domain::Option;

struct PayoffTestCase {
    std::shared_ptr<Option> option;
    double ST;
    double expected;
};

class OptionPayoffTest : public ::testing::TestWithParam<PayoffTestCase> {};



TEST_P(OptionPayoffTest, ComputesCorrectPayoff) {
    const auto& param = GetParam();
    EXPECT_DOUBLE_EQ(param.option->payoff(param.ST), param.expected);
}

INSTANTIATE_TEST_SUITE_P(
    AllOptions,                   // suite name visible dans le filtre
    OptionPayoffTest,
    ::testing::Values(
    PayoffTestCase{std::make_unique<infra::options::Call>(100.0_strike), 120.0, 20.0},
    PayoffTestCase{std::make_unique<infra::options::Call>(100.0_strike), 80.0, 0.0},
    PayoffTestCase{std::make_shared<infra::options::Put>(100.0_strike), 80.0, 20.0},
    PayoffTestCase{std::make_unique<infra::options::Put>(100.0_strike), 120.0, 0.0},
    PayoffTestCase{std::make_unique<infra::options::Straddle>(100.0_strike), 80.0, 20.0},
    PayoffTestCase{std::make_unique<infra::options::Straddle>(100.0_strike), 120.0, 20.0},
    PayoffTestCase{std::make_unique<infra::options::Square>(), 55.5, 3080.25},
    PayoffTestCase{std::make_unique<infra::options::Square>(), 0.0, 0.0}
        ));


struct ModelTestCase {
    std::shared_ptr<domain::Model> model;
    double S;
    double sigma;
    double T;
    double X;
    double expected;
    double tolerance;
};

class ModelSimulationTest : public ::testing::TestWithParam<ModelTestCase> {};

TEST_P(ModelSimulationTest, SimulateGivesExpectedResult) {
    const auto& param = GetParam();
    double ST = param.model->execute(param.S, param.sigma, param.T, param.X);
    EXPECT_NEAR(ST, param.expected, param.tolerance);
}

INSTANTIATE_TEST_SUITE_P(LogNormalAndNormalModels, ModelSimulationTest,
    ::testing::Values(
        ModelTestCase{std::make_unique<infra::models::LogNormalModel>(), 100.0, 0.2, 1.0, 0.0, 100.0 * std::exp(-0.5 * 0.2 * 0.2 * 1.0), 1e-6},
        ModelTestCase{std::make_unique<infra::models::LogNormalModel>(), 100.0, 0.2, 1.0, 1.0, 100.0 * std::exp(-0.5 * 0.2 * 0.2 * 1.0 + 0.2 * std::sqrt(1.0)), 1e-6},
        ModelTestCase{std::make_unique<infra::models::NormalModel>(), 100.0, 0.2, 1.0, 0.0, 100.0, 1e-6},
        ModelTestCase{std::make_unique<infra::models::NormalModel>(), 100.0, 0.2, 1.0, 1.0, 100.0 + 0.2 * std::sqrt(1.0), 1e-6}
    )
);
