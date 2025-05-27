#include <iostream>

#include "SpotPrice.h"
#include "Strike.h"
#include "TimeToMaturity.h"
#include "Volatility.h"
#include "AbstractFactory.h"
#include "MonteCarloPricer.h"
#include "StdNormalGenerator.h"

int main() {
    while (true) {
        try {
            std::string optionType, modelType;
            double spot, strike, volatility, maturity;
            int simulations;

            std::cout << "\nEnter option type (Call, Put, Straddle, Square): ";
            std::cin >> optionType;

            std::cout << "Enter model type (LogNormal, Normal): ";
            std::cin >> modelType;

            std::cout << "Enter spot price S: ";
            std::cin >> spot;

            std::cout << "Enter strike K: ";
            std::cin >> strike;

            std::cout << "Enter volatility sigma (0.0 - 1.0): ";
            std::cin >> volatility;

            std::cout << "Enter time to maturity T (in years): ";
            std::cin >> maturity;

            std::cout << "Enter number of simulations N: ";
            std::cin >> simulations;

            auto option = factory::AbstractFactory::createOption(optionType, entities::Strike(strike));
            auto model = factory::AbstractFactory::createModel(modelType);


            entities::SpotPrice S(spot);
            entities::Volatility sigma(volatility);
            entities::TimeToMaturity T(maturity);

            infra::rand_generator::StdNormalGenerator rng;
            const double price = use_case::MonteCarloPricer::execute(*model, *option, rng, S, sigma, T, simulations);

            std::cout << "\nSimulated price: " << price << std::endl;

        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }

        std::string again;
        std::cout << "\nWould you like to run another simulation? (yes/no): ";
        std::cin >> again;
        if (again != "yes" && again != "y") break;
    }

    return 0;

}
