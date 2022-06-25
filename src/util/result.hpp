#pragma once

#include <optional>

class bad_result_access : std::exception
{
};

template<typename T, typename E>
struct Result
{
    const std::optional<T> ok;
    const std::optional<E> err;

    Result<T, E>(T ok) noexcept : ok(ok), err(std::nullopt) {}
    Result<T, E>(E err) noexcept : ok(std::nullopt), err(err) {}

    T value() const noexcept(false)
    {
        if (ok) return ok;
        throw new bad_result_access();
    }

    T operator*() const noexcept(false) { return value(); }

    T value_or(T def) const noexcept { return ok.value_or(def); }

    E error() const noexcept(false)
    {
        if (err) return err;
        throw new bad_result_access();
    }

    E operator~() const noexcept(false) { return error(); }

    E error_or(E def) const noexcept { return err.value_or(def); }

    operator bool() const noexcept { return ok; }
};
