#pragma once

#include <memory>
#include <string>

#include "ModelFactory.h"
#include "OptionFactory.h"


#include "Option.h"
#include "Model.h"

namespace factory {
class AbstractFactory {
public:
    static std::unique_ptr<domain::Option> createOption(const std::string& name, const entities::Strike& strike) {
        return OptionFactory::create(name, strike);
    }
    static std::unique_ptr<domain::Model> createModel(const std::string& name) {
        return ModelFactory::create(name);
    }
};
}