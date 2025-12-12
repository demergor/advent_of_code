#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Range {
  long long lowest;
  long long highest;
};

bool fresh_id(const std::string& s, std::vector<Range>& ranges) {
  if (s.empty()) {
    return false;
  }

  size_t index {s.find('-')};
  if (std::string::npos == index) {
    long long cur {std::stoll(s)};
    for (const auto& r : ranges) {
      if (cur >= r.lowest && cur <= r.highest) {
        return true;
      }
    }
    return false;
  }

  assert (index < s.size() - 1);
  Range r {std::stoll(s.substr(0, index)), std::stoll(s.substr(index + 1, s.size()))};
  ranges.push_back(r);
  return false;
}

void reduce(std::vector<Range>& ranges) {
  bool change_made {false};
  size_t index {0};
  while (index < ranges.size()) {
    Range cur {ranges[index]};
    for (auto it {++ranges.begin()}; it != ranges.end();) {
      if (*it.lowest >= cur.lowest && *it.lowest <= cur.highest) {
        ranges[index] = merge(cur, index);
        break;
      }
    }
    ++index;
  }
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
  std::cout << "\nNumber of available fresh ingredient IDs part one: " << num_fresh << '\n';
  std::cout << "\nNumber of total fresh ingredient IDs part two: " << 
  return 0;
}
