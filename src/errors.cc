#include <sstream>

#include "errors.hh"
#include "util.hh"

fqs::err::FQSError::FQSError(const fqs::pos::Pos& start,
                             const fqs::pos::Pos& end, const std::string& name,
                             const std::string& details)
    : start(start), end(end), name(name), details(details) {}

std::string fqs::err::FQSError::str() const {
    std::ostringstream result;
    result << name << ": " << details << '\n'
           << "File '" << start.fn << "', line " << start.ln + 1 << "\n\n"
           << util::stringWithArrows(start.ftxt, start, end) << '\n';
    return result.str();
}

fqs::err::FQSIllegalCharError::FQSIllegalCharError(const fqs::pos::Pos& start,
                                                   const fqs::pos::Pos& end,
                                                   const std::string& details)
    : fqs::err::FQSError(start, end, "Illegal Character", details) {}

fqs::err::FQSUnknownLitError::FQSUnknownLitError(const fqs::pos::Pos& start,
                                                 const fqs::pos::Pos& end,
                                                 const std::string& details)
    : fqs::err::FQSError(start, end, "Unknown Literal", details) {}

fqs::err::FQSUnclosedCommentError::FQSUnclosedCommentError(
    const fqs::pos::Pos& start, const fqs::pos::Pos& end)
    : fqs::err::FQSError(start, end, "Unclosed Comment", "") {}

std::string fqs::err::FQSUnclosedCommentError::str() const {
    std::ostringstream result;
    result << name << '\n'
           << "File '" << start.fn << "', line " << start.ln + 1 << "\n\n"
           << util::stringWithArrows(start.ftxt, start, end) << '\n';
    return result.str();
}
