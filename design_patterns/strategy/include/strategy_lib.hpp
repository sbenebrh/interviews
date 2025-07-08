//
// Created by samuel benibgui on 08/07/2025.
//




#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <type_traits>

namespace strategy_lib {


template<typename> struct IStrategy;

template<typename R, typename... A>
struct IStrategy<R(A...)> {
    virtual ~IStrategy() = default;
    virtual R execute(A... a) = 0;
};

template<class Fun, typename Sig>
struct _callable : std::false_type {};

template<class Fun, typename R, typename... A>
struct _callable<Fun, R(A...)>
    : std::bool_constant<std::is_invocable_r_v<R, Fun, A...>> {};

template<class F, typename Sig>
concept Callable = _callable<F, Sig>::value;

template<class T, typename Sig>
concept Derived = std::derived_from<std::decay_t<T>, IStrategy<Sig>>;

template<typename Sig, Derived<Sig> S>
auto to_std_function(S&& obj)
{
    using Dec = std::decay_t<S>;
    auto ptr  = std::make_shared<Dec>(std::forward<S>(obj));
    if constexpr (std::is_void_v<Sig>)
        return std::function<Sig>{
            [ptr](auto&&... a){ ptr->execute(std::forward<decltype(a)>(a)...); }};
    else
        return std::function<Sig>{
            [ptr](auto&&... a){ return ptr->execute(std::forward<decltype(a)>(a)...); }};
}

template<typename Sig, Callable<Sig> F>
auto to_std_function(F&& f)
{
    return std::function<Sig>{ std::forward<F>(f) };
}

template<typename Sig>
class Context {
public:
    template<class S>
        requires (Derived<S, Sig> || Callable<S, Sig>)
    explicit Context(S&& s)
        : call_{ to_std_function<Sig>(std::forward<S>(s)) } {}

    template<class S>
        requires (Derived<S, Sig> || Callable<S, Sig>)
    void setStrategy(S&& s)
    {
        call_ = to_std_function<Sig>(std::forward<S>(s));   // forte sécurité d’exception
    }

    template<typename... Args>
    auto run(Args&&... a) const
    { return call_(std::forward<Args>(a)...); }

private:
    std::function<Sig> call_;
};

} // namespace strategy_lib