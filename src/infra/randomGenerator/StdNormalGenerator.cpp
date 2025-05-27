//
// Created by samuel benibgui on 26/05/2025.
//

#include "StdNormalGenerator.h"

infra::rand_generator::StdNormalGenerator::StdNormalGenerator(uint64_t seed): mRng(seed), mDist(0.0, 1.0) {}

double infra::rand_generator::StdNormalGenerator::next() {
    return mDist(mRng);
}
