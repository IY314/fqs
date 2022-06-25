#pragma once

#include "pos.hpp"

namespace fqs::tok
{

    struct Tok
    {
        enum struct Type
        {
            INT,
            FLOAT,
            STRING,
            IDENT,
            OPERATOR,
            LITERAL,
            END,
        } m_type;
        std::string m_value;
        Pos m_start, m_end;

        Tok(Type type,
            const std::string &value,
            const Pos &start,
            const Pos &end) noexcept;
        Tok(Type type, const Pos &pos) noexcept;
        Tok(Type type, const std::string &value, const Pos &pos) noexcept;
        Tok(const Tok &other) noexcept = default;
        ~Tok() noexcept = default;
    };
}  // namespace fqs::tok
