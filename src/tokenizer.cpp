#include "tokenizer.hpp"

#include <sstream>

fqs::tok::Tok number(std::string::const_iterator &it,
                     const std::string::const_iterator &end,
                     fqs::Pos &pos)
{
    using fqs::Pos, fqs::tok::Tok;

    const Pos &start(pos);
    bool isFloat = false;
    std::ostringstream res;

    while (it != end)
    {
        if (*it == '.')
        {
            if (isFloat) break;
            isFloat = true;
        }
        res << *it;
        it++, pos += *it;
    }

    return Tok(isFloat ? Tok::Type::FLOAT : Tok::Type::INT,
               res.str(),
               start,
               pos);
}

Result<fqs::tok::Tok, int> string(std::string::const_iterator &it,
                                  const std::string::const_iterator &end,
                                  fqs::Pos &pos)
{
    using fqs::Pos, fqs::tok::Tok;

    const Pos &start(pos);
    bool escaped;
    std::ostringstream res;

    it++, pos += *it;

    while (it != end)
    {
        if (escaped)
        {
            switch (*it)
            {
            case '\\': res << '\\'; break;
            case 'n': res << '\n'; break;
            case 'r': res << '\r'; break;
            case 't': res << '\t'; break;
            // TODO: escape codes
            default: return 1;
            }
            escaped = false;
        }
    }
}

namespace fqs::tok
{
    Result<std::vector<Tok>, int /* placeholder type */> tokenize(
        const std::string &fname,
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
                const Result<Tok, int> &res = string(it, ftext.cend(), pos);
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
                // TODO: illegal character
            }
        }

        return tokens;
    }
}  // namespace fqs::tok
