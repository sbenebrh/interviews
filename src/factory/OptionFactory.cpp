//
// Created by samuel benibgui on 27/05/2025.
//

#include "OptionFactory.h"

#include "Call.h"
#include "Put.h"
#include "Square.h"
#include "Straddle.h"


std::unique_ptr<domain::Option> factory::OptionFactory::create(const std::string& name, const entities::Strike &strike) {
    if (name == "Call") {
        return std::make_unique<infra::options::Call>(strike);
    }
    if (name == "Put") {
        return std::make_unique<infra::options::Put>(strike);
    }
    if (name == "Straddle") {
        return std::make_unique<infra::options::Straddle>(strike);
    }
    if (name == "Square") {
        return std::make_unique<infra::options::Square>();
    }
    throw std::invalid_argument("Unknown option type: " + name);
}
