#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

void draw_pixel(int& cycle, int reg_x, std::vector<std::string>& canvas) {
  cycle++;
  int row = (cycle - 1)/ 40;
  int sprite[] = {reg_x-1, reg_x, reg_x+1};
  int lookup = (cycle % 40) - 1;
  auto it = std::find(std::begin(sprite), std::end(sprite), lookup);
  if (it != std::end(sprite)) {
    canvas[row].push_back('#');
  } else {
    canvas[row].push_back('.');
  }
}

void addx(int& cycle, int& reg_x, const int val, std::vector<std::string>& canvas) {
  draw_pixel(cycle, reg_x, canvas);
  draw_pixel(cycle, reg_x, canvas);
  reg_x += val;
}

int main() {
  std::ifstream input("input10.txt");
  std::vector<std::string> canvas;
  for (int i = 0; i < 6; i++) {
    canvas.push_back(std::string());
  }
  int cycle = 0;
  int reg_x = 1;
  // TODO: Wrong drawings at the end of lines...
  if (input.is_open()) {
    std::string cmd;
    int val = 0;
    while (input >> cmd) {
      if (cmd == "noop") {
        draw_pixel(cycle, reg_x, canvas);
      } else {
        input >> val;
        addx(cycle, reg_x, val, canvas); 
      }
    }
  }

  for (auto row : canvas) {
    std::cout << row << std::endl;
  }

  return 0;
}
