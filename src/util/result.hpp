#pragma once

#include <exception>
#include <optional>

class bad_result_access : std::exception
{
};

template<typename T, typename E>
class Result
{
public:
    const std::optional<T> ok;
    const std::optional<E> err;

    Result<T, E>(T ok) noexcept : ok(ok), err(std::nullopt), isOk(true) {}
    Result<T, E>(E err) noexcept : ok(std::nullopt), err(err), isOk(false) {}

    T value() noexcept(false)
    {
        if (isOk) return ok;
        throw new bad_result_access();
    }

    T operator*() noexcept(false) { return value(); }

    T value_or(T def) noexcept { return isOk ? ok : def; }

    operator bool() const noexcept { return isOk; }

private:
    const bool isOk;
};
