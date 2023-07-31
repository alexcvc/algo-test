#include <fmt/format.h>
#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <regex>


int main() {

  std::regex rgx(strings::strings_utils::join(strings::strings_utils::escapeStrings(delimiters), "|"));

  std::sregex_token_iterator first(str.begin(), str.end(), rgx, -1);
  std::sregex_token_iterator last;
  return std::vector<std::string>(first, last);

  return 0;
}
