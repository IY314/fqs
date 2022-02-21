#pragma once

#include <string>

#include "pos.hh"

namespace fqs::err {
struct FQSError {
   public:
    pos::Pos start, end;
    std::string name, details;

    FQSError(const pos::Pos& start, const pos::Pos& end,
             const std::string& name, const std::string& details);

    virtual std::string str() const;
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

struct FQSUnclosedCommentError : public FQSError {
   public:
    FQSUnclosedCommentError(const pos::Pos& start, const pos::Pos& end);

    std::string str() const;
};
}  // namespace fqs::err
