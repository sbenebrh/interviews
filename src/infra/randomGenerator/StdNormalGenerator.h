#pragma once

#include <random>

namespace infra::rand_generator {
class StdNormalGenerator {
    std::mt19937 mRng;
    std::normal_distribution<> mDist;

public:
    explicit StdNormalGenerator(uint64_t seed = 0);
    double next();
};
}
