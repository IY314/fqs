#include "tokenizer.hpp"

#include <sstream>

#include "error/lex-error.hpp"

fqs::tok::Tok number(std::string::const_iterator &it,
                     const std::string::const_iterator &end,
                     fqs::Pos &pos)
{
    const fqs::Pos &start(pos);
    bool isFloat = false;
    std::ostringstream res;

    while (it != end && (std::isdigit(*it) || *it == '.'))
    {
        if (*it == '.')
        {
            if (isFloat) break;
            isFloat = true;
        }
        res << *it;
        it++, pos += *it;
    }

    return fqs::tok::Tok(
        isFloat ? fqs::tok::Tok::Type::FLOAT : fqs::tok::Tok::Type::INT,
        res.str(),
        start,
        pos);
}

Result<fqs::tok::Tok, fqs::err::FqsError> string(
    std::string::const_iterator &it,
    const std::string::const_iterator &end,
    fqs::Pos &pos)
{
    const fqs::Pos &start(pos);
    bool escaped;
    std::ostringstream res;

    it++, pos += *it;
    if (it == end) return fqs::err::FqsUnclosedStringError(start, pos);

    while (it != end && (escaped || *it != '"'))
    {
        if (escaped)
        {
            switch (*it)
            {
            case '\\': res << '\\'; break;
            case 'n': res << '\n'; break;
            case 'r': res << '\r'; break;
            case 't': res << '\t'; break;
            case '"': break;
            // TODO: escape codes
            default:
                return fqs::err::FqsInvalidEscapeError(
                    start,
                    pos,
                    std::string(1, '\\') + *it);
            }
            escaped = false;
        }
        else if (*it == '\\')
            escaped = true;
        else
            res << *it;

        it++, pos += *it;
    }

    if (it == end) return fqs::err::FqsUnclosedStringError(start, pos);

    it++, pos += *it;

    return fqs::tok::Tok(fqs::tok::Tok::Type::STRING, res.str(), start, pos);
}

namespace fqs::tok
{
    Result<std::vector<Tok>, err::FqsError> tokenize(const std::string &fname,
                                                     const std::string &ftext)
    {
        std::vector<Tok> tokens;
        Pos pos{0, 0, 0, fname, ftext};
        std::string::const_iterator it = ftext.cbegin();

        while (it != ftext.cend())
        {
            if (std::isspace(*it))
                it++, pos += *it;
            else if (std::isdigit(*it))
                tokens.push_back(number(it, ftext.cend(), pos));
            else if (std::isalpha(*it))
                // TODO: ident
                int x;
            else if (*it == '"')
            {
                const auto &res = string(it, ftext.cend(), pos);
                if (res)
                    tokens.push_back(*res);
                else
                    return ~res;
            }
            // TODO: comment
            // TODO: operator
            // TODO: literal
            else
            {
                const Pos &errPos(pos);
                return err::FqsIllegalCharError(errPos, *it);
            }
        }

        return tokens;
    }
}  // namespace fqs::tok
