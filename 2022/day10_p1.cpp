#include <iostream>
#include <fstream>
#include <algorithm>

int incr_cycle(int& cycle, int reg_x) {
  cycle++;

  int result = 0;
  int checks[] = {20,60,100,140,180,220};
  auto it = std::find(std::begin(checks), std::end(checks), cycle);
  if (it != std::end(checks)) {
    result = cycle * reg_x;
  }
  return result;
}

int addx(int& cycle, int& reg_x, const int val) {
  int result = incr_cycle(cycle, reg_x);
  result += incr_cycle(cycle, reg_x);
  reg_x += val;
  return result;
}

int main() {
  std::ifstream input("input10.txt");
  int cycle = 0;
  int reg_x = 1;
  int sum = 0;

  if (input.is_open()) {
    std::string cmd;
    int val = 0;
    while (input >> cmd) {
      if (cmd == "noop") {
        // noop
        sum += incr_cycle(cycle, reg_x);
      } else {
        input >> val;
        sum += addx(cycle, reg_x, val);
      }
    }
  }

  std::cout << "Part 1: " << sum << std::endl;
  return 0;
}