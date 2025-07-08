
# 🧠 Design Pattern Study Sheet

## 📌 Pattern Name :
Strategy Pattern

---

## 🎯 Problem it Solves :
_ When you have multiple algorithms or behaviors that should be interchangeable at runtime without duplicating code or adding complex condifitional logic inside a single class.

---

## 🛠️ General Structure :
•    Context: Uses a strategy object to perform a task.
•    Strategy (Interface/Abstract class): Declares an interface common to all supported algorithms.
•    ConcreteStrategyA/B: Implement the strategy interface with specific behavior.

+--------------------+          +------------------------+
|      Context       |<>------->|       Strategy         |
|--------------------|          +------------------------+
| - strategy:Strategy|          ^            ^          
|--------------------|          |            |
| +setStrategy(s)    |     +------------+  +------------+
| +executeStrategy() |     | ConcreteA  |  | ConcreteB  |
+--------------------+     +------------+  +------------+


---

## ✅ Common Use Cases
_   •    Pricing engines with multiple discount strategies.
    •    Sorting algorithms that can change at runtime.
    •    Game characters with interchangeable movement or attack behaviors.
    •    Encoding or compression strategies (e.g., ZIP, RAR).

---


## 💬 Explication orale type (entretien) :
_"The Strategy Pattern is a behavioral design pattern that allows an object to change its behavior at runtime by switching between different algorithms or strategies.

Instead of using if or switch statements inside a class to choose between behaviors, we define a common interface for all the strategies, and delegate the behavior to a concrete strategy object.

This promotes flexibility and respects the Open/Closed Principle — I can add new strategies without modifying the context class.

---

