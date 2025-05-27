#pragma once
#include <memory>
#include <string>


namespace domain {
    struct Option;
}

namespace entities {
    class Strike;
}

namespace factory {

    class OptionFactory {
    public:
        static std::unique_ptr<domain::Option> create(const std::string& name, const entities::Strike& strike);

    };
}
