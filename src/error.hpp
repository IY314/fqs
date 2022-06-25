#pragma once

#include "pos.hpp"

namespace fqs::err
{
    class FqsError
    {
    public:
        FqsError(const Pos &start,
                 const Pos &end,
                 const std::string &name,
                 const std::string &info) noexcept;

        virtual std::string toString() const noexcept;

    private:
        Pos m_start, m_end;
        std::string m_name, m_info;
    };

    class FqsIllegalCharError : public FqsError
    {
    public:
        FqsIllegalCharError(const Pos &start,
                            const Pos &end,
                            const char &ch) noexcept;
    };
}  // namespace fqs::err
