#include <cassert>
#include <iostream>
#include <string>
#include <vector>

struct Range {
  long long lowest;
  long long highest;
};

bool overlap(const Range& r, const Range& s) {
  return 
    s.highest >= r.lowest && s.highest <= r.highest ||
    r.highest >= s.lowest && r.highest <= s.highest;
}

bool included(const Range& r, const Range& s) {
  return r.lowest <= s.lowest && r.highest >= s.highest;
}

void merge(Range& merge_into, const Range& other) {
  merge_into.lowest = std::min(merge_into.lowest, other.lowest);
  merge_into.highest = std::max(merge_into.highest, other.highest);
}

void add_range(const Range& range, std::vector<Range>& ranges) {
  for (auto& r : ranges) {
    if (included(r, range)) {
      return;
    }
    if (included(range, r)) {
      r = range;
      return;
    }
    if (overlap(r, range)) {
      merge(r, range);
      return;
    }
  }
  ranges.push_back(range);
}

bool fresh_id(const std::string& s, std::vector<Range>& ranges) {
  if (s.empty()) {
    return false;
  }

  size_t index {s.find('-')};
  if (index != std::string::npos) {
    add_range(
        Range {
          std::stoll(s.substr(0, index)), 
          std::stoll(s.substr(index + 1, s.size()))
        },
        ranges
    );
    return false;
  }

  long long cur {std::stoll(s)};
  for (const auto& r : ranges) {
    if (cur >= r.lowest && cur <= r.highest) {
      return true;
    }
  }
  return false;
}

bool merge_overlapping(Range& cur, const size_t index_cur, std::vector<Range>& ranges) {
  for (size_t i {index_cur + 1}; i < ranges.size(); ++i) {
    if (included(cur, ranges[i])) {
      ranges.erase(ranges.begin() + i);
      return true;
    } else if (included(ranges[i], cur)) {
      ranges.erase(ranges.begin() + index_cur);
      return true;
    } else if (overlap(cur, ranges[i])) {
      merge(cur, ranges[i]);
      ranges.erase(ranges.begin() + i);
      return true;
    }
  }
  return false;
}

void reduce(std::vector<Range>& ranges) {
  size_t i {0};
  while (i < ranges.size()) {
    if (!merge_overlapping(ranges[i], i, ranges)) {
      ++i;
    }
  }
}

void print(const std::vector<Range>& ranges) {
  std::cout << "\n\n";
  for (const auto& r : ranges) {
    std::cout << r.lowest << " - " << r.highest << '\n';
  }
  std::cout << "\n\n";
}

int main() {
  std::cout << "Please enter your list of ranges and IDs below:\n";
  std::vector<Range> ranges;
  std::string input;
  int num_fresh {0};
  while (std::getline(std::cin, input)) {
    num_fresh += fresh_id(input, ranges);
  }
  reduce(ranges);
  long long total_num_fresh_id {0};
  for (const auto& r : ranges) {
    total_num_fresh_id += (r.highest - r.lowest) + 1;
  }
  std::cout << "\nNumber of available fresh ingredient IDs part one: " << num_fresh << '\n';
  std::cout << "\nNumber of total fresh ingredient IDs part two: " << total_num_fresh_id << '\n';
  return 0;
}
