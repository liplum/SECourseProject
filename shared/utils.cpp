//
// Created by Liplum on 6/12/2023.
//

#include "utils.h"
#include <iostream>

using namespace std;

string toLowercase(const string &str) {
  string result;
  result.reserve(str.length());

#ifdef _WIN32
  for (auto c: str) {
    result.push_back(tolower(c));
  }
#else
  auto locale = std::locale();
  for (auto c: str) {
    result.push_back(tolower(c, locale));
  }
#endif

  return std::move(result);
}
