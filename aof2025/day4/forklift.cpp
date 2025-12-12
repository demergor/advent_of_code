#include <cassert>
#include <iostream>
#include <string>

#include "grid.h"

constexpr char ROLL {'@'};
constexpr char MARKED {'X'};
constexpr char EMPTY {'.'};

int num_rolls_in_three_cols(const std::string& row, const size_t i) {
  assert(i < row.size());
  int result {0};
  if (i > 0) {
    result += (row[i - 1] == ROLL || row[i - 1] == MARKED);
  }
  if (i < row.size() - 1) {
    result += (row[i + 1] == ROLL || row[i + 1] == MARKED);
  }
  return result + ((row[i] == ROLL) || row[i] == MARKED);
}

int less_than_four_adjacent(
    std::string& upper,
    std::string& middle, 
    std::string& lower
) {
  int num_adjacent {0};
  for (size_t i {0}; i < middle.size(); ++i) {
    int num_adjacent_single {0};
    if (middle[i] != ROLL) {
      continue;
    }
    if (!upper.empty()) {
      num_adjacent_single += num_rolls_in_three_cols(upper, i);
    }
    if (i > 0) {
      num_adjacent_single += middle[i - 1] == ROLL || middle [i - 1] == MARKED;
    }
    if (i < middle.size()) {
      num_adjacent_single += middle[i + 1] == ROLL || middle [i + 1] == MARKED;
    }
    if (!lower.empty()) {
      num_adjacent_single += num_rolls_in_three_cols(lower, i);
    }
    if (num_adjacent_single < 4) {
      ++num_adjacent;
      middle[i] = MARKED;
    }
  }
  return num_adjacent;
}

void cleanup(Grid& g) {
  for (auto& s : g.rows) {
    for (auto& c : s) {
      if (c == MARKED) {
        c = EMPTY;
      }
    }
  }
}

bool access_rolls(Grid& g) {
  int num_accessed_rolls_before {g.num_accessed_rolls};
  for (size_t i {0}; i < g.rows.size(); ++i) {
    std::string upper {i > 0 ? g.rows[i - 1] : ""};
    std::string lower {i < g.rows.size() - 1 ? g.rows[i + 1] : ""};
    g.num_accessed_rolls += less_than_four_adjacent(upper, g.rows[i], lower);
  }
  return num_accessed_rolls_before != g.num_accessed_rolls;
}

int main() {
  Grid grid {};
  Grid grid2 {};
  std::cout << "Please enter your grid of paper rolls below:\n";
  std::string input;
  while (std::getline(std::cin, input)) {
    grid.rows.push_back(input);
    grid2.rows.push_back(input);
  }
  access_rolls(grid);
  while (access_rolls(grid2)) {
    cleanup(grid2);
  }
  std::cout << "\nNumber of accessible paper rolls part one: " << grid.num_accessed_rolls << '\n';
  std::cout << "Number of accessible paper rolls part two: " << grid2.num_accessed_rolls << '\n';
  return 0;
}
