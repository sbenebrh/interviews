#include <gtest/gtest.h>

#include "RandomGeneratorType.h"
#include <vector>
#include <stdexcept>

#include "LogNormal.h"
#include "MonteCarloPricer.h"

#include "SpotPrice.h"
#include "Volatility.h"
#include "TimeToMaturity.h"
#include "Model.h"
#include "Option.h"

#include "Call.h"
#include "Put.h"
#include "Straddle.h"
#include "Square.h"

#include "Normal.h"
#include "LogNormal.h"

class FakeGenerator {
    std::vector<double> values;
    std::size_t index = 0;

public:
    explicit FakeGenerator(std::vector<double> v) : values(std::move(v)) {}

    double next() {
        if (index >= values.size()) throw std::out_of_range("No more values");
        return values[index++];
    }
};

TEST(FakeGeneratorTest, ReturnsValuesInOrder) {
    // Arrange
    std::vector<double> sequence = {0.1, -0.5, 1.3};
    FakeGenerator gen(sequence);

    // Act & Assert
    EXPECT_DOUBLE_EQ(gen.next(), 0.1);
    EXPECT_DOUBLE_EQ(gen.next(), -0.5);
    EXPECT_DOUBLE_EQ(gen.next(), 1.3);
}

TEST(FakeGeneratorTest, ThrowsWhenExhausted) {
    FakeGenerator gen({42.0});
    gen.next(); // valid
    EXPECT_THROW(gen.next(), std::out_of_range);
}

struct PricerTestCase {
    std::shared_ptr<domain::Model> model;
    std::shared_ptr<domain::Option> option;
    std::vector<double> inputs;
    double expected;
};

class MonteCarloPricerTest : public ::testing::TestWithParam<PricerTestCase> {};

TEST_P(MonteCarloPricerTest, ComputesCorrectAveragePayoff) {
    const auto& p = GetParam();
    FakeGenerator rng(p.inputs);

    constexpr auto S = 100._price;
    constexpr auto sigma = 0.2_vol;
    constexpr  auto T = 1._maturity;

    const double result = use_case::MonteCarloPricer::execute(*p.model, *p.option, rng, S, sigma, T, static_cast<int>(p.inputs.size()));
    EXPECT_NEAR(result, p.expected, 1e-6);
}

INSTANTIATE_TEST_SUITE_P(AllModelOptionCombinations, MonteCarloPricerTest,
    ::testing::Values(
        PricerTestCase{std::make_unique<infra::models::LogNormalModel>(), std::make_unique<infra::options::Call>(100.0_strike), {0.0}, std::max(std::exp(-0.5 * 0.2 * 0.2) * 100 - 100, 0.0)},
        PricerTestCase{std::make_unique<infra::models::LogNormalModel>(), std::make_unique<infra::options::Put>(100.0_strike), {0.0}, std::max(100 - std::exp(-0.5 * 0.2 * 0.2) * 100, 0.0)},
        PricerTestCase{std::make_unique<infra::models::LogNormalModel>(), std::make_unique<infra::options::Straddle>(100.0_strike), {0.0}, std::abs(std::exp(-0.5 * 0.2 * 0.2) * 100 - 100)},
        PricerTestCase{std::make_unique<infra::models::LogNormalModel>(), std::make_unique<infra::options::Square>(), {0.0}, std::pow(std::exp(-0.5 * 0.2 * 0.2) * 100, 2)},
        PricerTestCase{std::make_unique<infra::models::NormalModel>(), std::make_unique<infra::options::Call>(100.0_strike), {0.0}, std::max(100.0 - 100.0, 0.0)},
        PricerTestCase{std::make_unique<infra::models::NormalModel>(), std::make_unique<infra::options::Put>(100.0_strike), {0.0}, std::max(100.0 - 100.0, 0.0)},
        PricerTestCase{std::make_unique<infra::models::NormalModel>(), std::make_unique<infra::options::Straddle>(100.0_strike), {0.0}, std::abs(100.0 - 100.0)},
        PricerTestCase{std::make_unique<infra::models::NormalModel>(), std::make_unique<infra::options::Square>(), {0.0}, std::pow(100.0, 2)}
    ));