#include <cassert>
#include <iostream>

struct Dial {
  int pos;
  int num_hits;
  int num_passes;
  int direction;
};

void init_dial(Dial& dial) {
  dial.pos = 50;
  dial.num_hits = 0;
  dial.num_passes = 0;
  dial.direction = 1;
}

void update_passes(Dial& dial, const bool started_from_zero) {
  if (dial.pos >= 100) {
    dial.num_passes += dial.pos / 100;
  } else if (dial.pos <= 0) {
    dial.num_passes -= -1 * !started_from_zero + dial.pos / 100;
  }
}

void update_hits(Dial& dial) {
  dial.pos %= 100;
  if (dial.pos < 0) {
    dial.pos = 100 + dial.pos;
  }
  if (!dial.pos) {
    ++dial.num_hits;
  }
}

bool rotate_dial(Dial& dial, std::string& s) {
  switch (s[0]) {
    case 'L': dial.direction = -1; break;
    case 'R': dial.direction = 1; break;
    default: 
      return false;
  }
  s.erase(s.begin());
  dial.pos += dial.direction * std::stoi(s);
  return true;
}

int main() {
  Dial dial {};
  init_dial(dial);
  std::cout << "Enter your input below:\n";
  std::string input;
  bool was_at_zero {false};
  while (std::getline(std::cin, input)) {
    assert(!input.empty());
    if (!rotate_dial(dial, input)) {
      break;
    }
    update_passes(dial, was_at_zero);
    update_hits(dial);
    was_at_zero = dial.pos == 0;
  }
  std::cout << "\nPassword part one: " << dial.num_hits;
  std::cout << "\nPassword part two: " << dial.num_passes << "\n";
  return 0;
}
