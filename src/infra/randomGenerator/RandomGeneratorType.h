#pragma once
#include <concepts>

namespace infra::rand_generator {

template <typename T>
concept RandomGeneratorType = requires(T gen)
{
  {gen.next()} -> std::convertible_to<double>;
};

}