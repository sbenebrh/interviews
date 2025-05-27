# Monte Carlo Pricer – Architecture Report

## Overview
This document outlines the architectural decisions and key design principles behind the Monte Carlo pricer implementation. The system was developed with modularity, testability, and clarity in mind using hexagonal architecture principles.

---

## 1. Objectives
- Implement a Monte Carlo pricing engine supporting various option types (Call, Put, Straddle, Square).
- Support multiple pricing models (LogNormal, Normal).
- Ensure testability, correctness, and extensibility.
- Maintain a clean separation of concerns.

---

## 2. Architecture Structure

### Hexagonal (Ports & Adapters) Style
The system is divided into clear layers:

- **Entities**: Domain primitives such as `SpotPrice`, `Strike`, `Volatility`, `TimeToMaturity`. These enforce constraints and validation.

- **Domain**: Pure abstract interfaces such as `Option` and `Model`. This layer defines the contracts for pricing logic and simulation.

- **Infra**: Concrete implementations of domain contracts:
    - Options: `Call`, `Put`, `Straddle`, `Square`
    - Models: `LogNormalModel`, `NormalModel`
    - Random generators: `StdNormalGenerator`, `FakeGenerator`

- **Use Case**: The `MonteCarloPricer` is the orchestrator that coordinates a pricing simulation using injected models, options, and generators.

- **Factory**: Includes `OptionFactory`, `ModelFactory`, and a top-level `AbstractFactory` to build components based on string-based user input.

- **Executable**: The `main.cpp` entry point presents an interactive interface, prompts for parameters, and invokes the pricer repeatedly until the user chooses to exit.

---

## 3. Design Decisions

### a. Value Objects as Entities
All core inputs (e.g., spot, volatility, maturity) are wrapped in value types to enforce domain-specific rules and ensure clarity in function signatures.

### b. Interface-driven Design for Options and Models
Business logic relies on pure virtual interfaces to allow flexible substitution and mocking. This aligns with the Dependency Inversion Principle.

### c. Use of Concepts for Random Generator
A C++20 `concept` replaces the need for virtual inheritance for random generators. This improves readability, avoids runtime overhead, and ensures type constraints are checked at compile time.

### d. Static Method Template instead of Templating the Class
The `MonteCarloPricer::execute()` method is templated over the generator, avoiding unnecessary instantiations of the entire class and simplifying usage.

### e. Factory and Abstract Factory
Separate factories for options and models encapsulate construction logic. A higher-level `AbstractFactory` simplifies the CLI usage and abstracts those factories.

### f. Interactive Main Loop
The application runs in a loop, prompting the user to input simulation parameters. Errors are caught, and the user can rerun simulations interactively.

### g. Removed `std::execution::par_unseq`
I originally considered using parallel reduction, but due to limitations in Clang’s support on macOS, I fallback to `std::accumulate`, which is portable and simpler.

---

## 4. Questions Considered
- Should options/models be chosen at compile time or runtime?
  → Runtime selection was chosen to enable flexibility in the CLI interface.

- Should factories support automatic registration?
  → This was deferred in favor of simple hardcoded mapping in the factories.

- Why not parallelize payoff accumulation?
  → Due to tooling limitations and the focus on clarity and determinism, I used simple `std::accumulate`.

- Why use a `concept` instead of an interface for random generators?
  → `concepts` provide better compile-time guarantees and improve performance by avoiding vtables.

---

## 5. Testing Strategy
- Value objects and option/model logic are tested in isolation.
- Parametrized tests verify all `Model × Option` combinations.
- `FakeGenerator` enables fully deterministic and controlled testing.
- Test cases confirm the pricer’s output matches theoretical expectations for known inputs.

---

## 6. Improvements and Extensions
- Extend the factories to support registration via a map for plugin-style extension.
- Improve the CLI with input validation and a menu-based system.
- Enable parallel execution with thread-safe random number generators.

---

## Conclusion
The Monte Carlo pricer is modular, testable, and robust. The use of value objects, concept-based design, and clear architectural boundaries ensures that the implementation is maintainable and ready for future enhancements.
