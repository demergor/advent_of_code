#include <cassert>
#include <iostream>
#include <string>

#include "digit_container.h"

constexpr char ADD {'+'};
constexpr char MUL {'*'};

void test_grand_sum() {
  DigitContainer dc;
  dc.add_blocks({1, 2, 3, 44});
  dc.add_blocks({3, 4, 1,  1});
  dc.operations("+ + * +");
  std::cout << dc.grand_sum(dc.blocks()) << '\n';
  assert(dc.grand_sum(dc.blocks()) == 1 + 3 + 2 + 4 + 3 * 1 + 44 + 1); // 58
}

std::vector<int> split(const std::string& s, const char delimiter) {
  std::vector<int> result;
  std::string intermediate;
  for (const auto& val : s) {
    if (val != delimiter) {
      intermediate += val;
    } else if (!intermediate.empty()) {
      result.push_back(std::stoi(intermediate));
      intermediate.clear();
    }
  }
  if (!intermediate.empty()) {
    result.push_back(std::stoi(intermediate));
  }
  return result;
}

void print(const std::vector<std::vector<int>>& vec) {
  for (const auto& v : vec) {
    for (const auto& val : v) {
      std::cout << val << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

int main() {
  test_grand_sum();
  DigitContainer dc;
  std::string input;
  while (std::getline(std::cin, input)) {
    if (input.find(::ADD) == std::string::npos && input.find(::MUL) == std::string::npos) {
      dc.add_blocks(split(input, ' '));
      dc.add_cols(input);
    } else {
      dc.operations(input);
    }
  }
  print(dc.blocks());
  // print(dc.convert_cols());
  std::cout << "\nGrand total part one: " << dc.grand_sum(dc.blocks()) << '\n';
  std::cout << "Grand total part two: " << dc.grand_sum(dc.convert_cols()) << '\n';
  return 0;
}
