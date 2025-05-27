#include "ModelFactory.h"
#include "LogNormal.h"
#include "Normal.h"
#include <string>

std::unique_ptr<domain::Model> factory::ModelFactory::create(const std::string &name) {
    if (name == "LogNormal") {
        return std::make_unique<infra::models::LogNormalModel>();
    }
    if (name == "Normal") {
        return std::make_unique<infra::models::NormalModel>();
    }
    throw std::invalid_argument("Unknown model type: " + name);
}
