#pragma once

#include <string>

#include "pos.hh"

namespace fqs::err {
struct FQSError {
   public:
    FQSError(const pos::Pos& start, const pos::Pos& end,
             const std::string& name, const std::string& details);

    virtual std::string str() const;

   private:
    pos::Pos start, end;
    std::string name, details;
};

struct FQSIllegalCharError : public FQSError {
   public:
    FQSIllegalCharError(const pos::Pos& start, const pos::Pos& end,
                        const std::string& details);
};

struct FQSUnknownLitError : public FQSError {
   public:
    FQSUnknownLitError(const pos::Pos& start, const pos::Pos& end,
                       const std::string& details);
};
}  // namespace fqs::err
