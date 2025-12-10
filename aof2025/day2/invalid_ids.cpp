#include <cassert>
#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string& s, const char delimiter) {
  std::vector<std::string> result;
  std::string cur;
  for (const auto& c : s) {
    if (c == delimiter) {
      result.push_back(cur);
      cur.clear();
    } else {
      cur += c;
    }
  }
  if (!cur.empty()) {
    result.push_back(cur);
  }
  return result;
}

bool valid(long long n) {
  long long factor {1};
  long long comp {0};
  while (n) {
    long long back_digit {n % 10};
    comp += back_digit * factor;
    n /= 10;
    if (n == comp && back_digit) {
      return false;
    }
    factor *= 10;
  }
  return true;
}

bool forms_repetitional_pattern(const std::string& s, const int divisor) {
  size_t chunk_size {s.size() / divisor};
  assert(chunk_size * divisor == s.size());
  std::string whole {s};
  std::string comp {whole.substr(0, chunk_size)};
  whole.erase(0, chunk_size);
  do {
    std::string cur {whole.substr(0, chunk_size)};
    if (cur != comp) {
      return false;
    }
    comp = cur;
    whole.erase(0, chunk_size);
  } while (!whole.empty());
  return true;
}

bool valid2(const std::string& number_as_string) {
  std::vector<int> divisors;
  for (int i {2}; i <= number_as_string.size(); ++i) {
    if (number_as_string.size() % i == 0) {
      divisors.push_back(i);
    }
  }
  for (const auto& div : divisors) {
    if (forms_repetitional_pattern(number_as_string, div)) {
      return false;
    }
  }
  return true;
}

long long sum_invalid_ids(const std::string& s) {
  const std::vector<std::string> range {split(s, '-')};
  assert(range.size() == 2);
  long long sum {0};
  long long lower {std::stoll(range[0])};
  const long long upper {std::stoll(range[1])};
  for (; lower <= upper; ++lower) {
    if (!valid(lower)) {
      sum += lower;
    }
  }
  return sum;
}

long long sum_invalid_ids2(const std::string& s) {
  const std::vector<std::string> range {split(s, '-')};
  assert(range.size() == 2);
  long long sum {0};
  long long lower {std::stoll(range[0])};
  const long long upper {std::stoll(range[1])};
  for (; lower <= upper; ++lower) {
    if (!valid2(std::to_string(lower))) {
      sum += lower;
    }
  }
  return sum;
}

int main() {
  std::cout << "Please enter the list of ID's below:\n";
  long long invalid_id_sum {0};
  long long invalid_id_sum2 {0};
  std::string input;
  while (std::getline(std::cin, input)) {
    std::vector<std::string> ranges {split(input, ',')};
    for (const auto& s : ranges) {
      invalid_id_sum += sum_invalid_ids(s);
      invalid_id_sum2 += sum_invalid_ids2(s);
    }
  }
  std::cout << "\nSum of invalid IDs part one: " << invalid_id_sum;
  std::cout << "\nSum of invalid IDs part two: " << invalid_id_sum2 << '\n';
  return 0;
}
