#pragma once

#include <initializer_list>
#include <string>
#include <vector>

namespace util {
bool strcontains(const std::initializer_list<std::string>& strs, char ch);
bool strcontains(const std::string& str, char ch);
template <typename T>
bool veccontains(const std::vector<T>& vec, const T& elem);
}  // namespace util
