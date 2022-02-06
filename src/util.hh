#ifndef FQS_UTIL_HH
#define FQS_UTIL_HH

#include <string>
#include <vector>

namespace util {
bool strcontains(const std::string& str, const char& ch);
template <typename T>
bool veccontains(const std::vector<T>& vec, const T& elem);
}  // namespace util

#endif /* FQS_UTIL_HH */
