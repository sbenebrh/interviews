#pragma once
#include "Model.h"

#include <memory>
namespace factory {

class ModelFactory {
public:
    static std::unique_ptr<domain::Model> create(const std::string& name);
};

} // namespace factory