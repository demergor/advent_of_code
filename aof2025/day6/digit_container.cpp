#include <cassert>
#include <string>
#include <vector>

#include "digit_container.h"

namespace {
  bool is_delimiting_column(const std::vector<std::vector<char>>& vec, const size_t index) {
    for (const auto& val : vec) {
      if (val.empty()) {
        continue;
      }
      if (val[index] != ' ') {
        return false;
      }
    }
    return true;
  }

  std::vector<int> convert_and_transpose(
      const std::vector<std::vector<char>>& vec,
      const size_t lower,
      const size_t upper
  ) {
    assert(lower >= 0 && upper < vec.size());
    std::vector<int> result;
    for (const auto& val : vec) {
      if (val.empty()) {
        continue;
      }
      int cur {0};
      for (size_t i {lower}; i < upper; ++i) {
        if (val[i] != ' ') {
          cur = cur * 10 + (val[i] - '0');
        }
      }
      result.push_back(cur);
    }
    return result;
  }
}

void DigitContainer::add_blocks(const std::vector<int>& vec) {
  // Needs initialization
  blocks_.push_back(vec);
}

void DigitContainer::add_cols(const std::string& s) {
  if (cols_.empty()) {
    // Initialize with a value that should suffice
    initialize_cols(20);
  }

  for (size_t i {0}; i < cols_.size(); ++i) {
    for (const auto& val : s) {
      cols_[i].push_back(val);
    }
  }
}

long long DigitContainer::grand_sum(const std::vector<std::vector<int>>& vec) const {
  long long sum {0};
  for (size_t i {0}; i < operations_.size(); ++i) {
    assert(operations_[i] == '*' || operations_[i] == '+');
    long long intermediate {operations_[i] == '*' ? 1 : 0};
    for (const auto& val : vec) {
      if (operations_[i] == '*') {
        sum *= val[i];
      } else {
        sum += val[i];
      }
    }
    sum += intermediate;
  }
  return sum;
}

std::vector<std::vector<int>> DigitContainer::convert_cols() const {
  std::vector<std::vector<int>> result;
  size_t lower_bound {0};
  size_t upper_bound {0};
  for (size_t i {0}; i < cols_.size(); ++i) {
    if (is_delimiting_column(cols_, i)) {
      upper_bound = i;
    }
    result.emplace_back(convert_and_transpose(cols_, lower_bound, upper_bound));
    lower_bound = upper_bound;
  }
  return result;
}

void DigitContainer::operations(const std::string& s) {
  for (const auto& val : s) {
    if (val == '*' || val == '+') {
      operations_.push_back(val);
    }
  }
}

std::vector<std::vector<int>> DigitContainer::blocks() const {
  return blocks_;
}

void DigitContainer::initialize_cols(const int size) {
  for (size_t i {0}; i < size; ++i) {
    cols_.push_back({});
  }
}

void DigitContainer::shrink_cols() {
  for (size_t i {0}; i < cols_.size(); ++i) {
    if (cols_[i].empty()) {
      cols_.erase(cols_.begin() + i, cols_.end());
      return;
    } 
  }
}
