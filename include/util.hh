#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include "pos.hh"

namespace util {
bool strcontains(const std::initializer_list<std::string>& strs, char ch);
bool strcontains(const std::string& str, char ch);

template <typename T>
bool veccontains(const std::vector<T>& vec, const T& elem);

std::string strreplace(std::string str, const std::string& search,
                       const std::string& replace);

std::string stringWithArrows(const std::string& text,
                             const fqs::pos::Pos& start,
                             const fqs::pos::Pos& end);
}  // namespace util
