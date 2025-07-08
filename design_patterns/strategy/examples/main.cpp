//
// Created by samuel benibgui on 08/07/2025.
//


#include "../include/strategy_lib.hpp"
#include <iostream>
#include <cmath>

using namespace  strategy_lib;

/* ───────── Component A : Pricing Engine ─────────
   signature : double(double price)
--------------------------------------------------*/
using PriceSig = double(double);

class TaxStrategy : public IStrategy<PriceSig> {
public:
    explicit TaxStrategy(double rate) : rate_(rate) {}
    double execute(double price) override { return price * (1.0 + rate_); }
private:
    double rate_;
};

class DiscountStrategy : public IStrategy<PriceSig> {
public:
    explicit DiscountStrategy(double pct) : pct_(pct) {}
    double execute(double price) override { return price * (1.0 - pct_); }
private:
    double pct_;
};

/* ───────── Component B : Enemy AI ─────────
   signature : void(int difficulty, float dt)
--------------------------------------------------*/
using AISig = void(int, float);

class AggressiveAI : public IStrategy<AISig> {
public:
    void execute(int lvl, float dt) override {
        std::cout << "Aggressive AI level " << lvl << " dt=" << dt << '\n';
    }
};

int main()
{
    using namespace std;

    /* ===== Component A usage ===== */
    strategy_lib::Context<PriceSig> priceCtx{ TaxStrategy{0.20} };
    cout << "Tax on 100  → " << priceCtx.run(100.0) << '\n';

    priceCtx.setStrategy( DiscountStrategy{0.15} );
    cout << "Discount on 100 → " << priceCtx.run(100.0) << '\n';

    /* lambda move-only example */
    auto special = [coef = sqrt(2.0)](double p){ return p * coef; };
    priceCtx.setStrategy( std::move(special) );
    cout << "Special on 100 → " << priceCtx.run(100.0) << '\n';

    /* ===== Component B usage ===== */
    strategy_lib::Context<AISig> aiCtx{ AggressiveAI{} };
    aiCtx.run(5, 0.016f);

    aiCtx.setStrategy( [](int lvl, float dt){
        std::cout << "Stealth AI lvl " << lvl << " dt=" << dt << '\n';
    });
    aiCtx.run(3, 0.033f);

    return 0;
}