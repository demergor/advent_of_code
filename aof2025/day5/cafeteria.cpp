#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>

int num_fresh {0};

void print(const std::unordered_set<int>& us) {
  for (const auto& val : us) {
    std::cout << val << '\n';
  }
}

void add_range(const std::string& s, std::unordered_set<int>& range) {
  if (s.empty()) {
    return;
  }

  print(range);

  size_t index {s.find('-')};
  if (std::string::npos == index) {
    ::num_fresh += range.find(std::stoi(s)) == range.end() ? 0 : 1;
    return;
  }

  assert (index < s.size() - 1);
  for (int i {std::stoi(s.substr(0, index))}; i <= std::stoi(s.substr(index + 1, s.size())); ++i) {
    range.insert(i);
  }
}


int main() {
  std::cout << "Please enter your list of ranges and IDs below:\n";
  std::unordered_set<int> fresh_range;
  std::string input;
  std::cin >> input;
  while (!input.empty()) {
    add_range(input, fresh_range);
    std::cin >> input;
  }
  int num_fresh {0};
  int id {0};
  while (std::cin >> id) {
    num_fresh += (fresh_range.find(id) == fresh_range.end()) ? 0 : 1;
  }
  std::cout << "\nNumber of available fresh ingredient IDs part one: " << num_fresh << '\n';
  print(fresh_range);
  return 0;
}
