#include <iostream>
#include <string>
#include <vector>

void propagate_left(std::vector<char>& digits) {
  for (size_t i {1}; i < digits.size(); ++i) {
    if (digits[i - 1] >= digits[i]) {
      continue;
    }
    digits[i - 1] = digits[i];
    digits[i] = '\0';
  }
}

long long largest_joltage(const std::string& battery_bank, size_t num_batteries) {
  std::vector<char> digits(num_batteries, '\0');
  for (const auto& decimal : battery_bank) {
    propagate_left(digits);
    if (digits[num_batteries - 1] < decimal) {
      digits[num_batteries - 1] = decimal;
    }
  }
  long long result {0};
  long long factor {1};
  for (int i {static_cast<int>(digits.size()) - 1}; i >= 0; --i, factor *= 10) {
    result += (digits[i] - '0') * factor;
  }
  return result;
}

int main() {
  int total_pair_joltage {0};
  long long total_dozen_joltage {0};
  std::cout << "Please enter your list of battery banks below:\n";
  std::string input;
  while (std::getline(std::cin, input)) {
    total_pair_joltage += largest_joltage(input, 2);
    total_dozen_joltage += largest_joltage(input, 12);
  }
  std::cout << "\nTotal output joltage part one: " << total_pair_joltage;
  std::cout << "\nTotal output joltage part two: " << total_dozen_joltage << '\n';
  return 0;
}
