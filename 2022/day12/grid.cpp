#include <stdexcept>
#include <iostream>
#include "grid.h"

void Grid::add_row() {
  data.push_back(std::vector<Location>());
}

void Grid::push_back(char c) {
  int row = data.size() - 1;
  int col = data.back().size() == 0 ? 0 : data.back().size();
  Location loc(row, col, c);
  data.back().push_back(loc);
}

std::vector<Location> Grid::neighbors(Location cur){
  std::vector<Location> neighbors;
  Position add[] = {Position(1,0), Position(0,1), Position(-1, 0), Position(0, -1)};

  for (Position to_add : add) {
    Position pos = cur.pos + to_add;

    try {
      Location next = get(pos);
      if (next.height - cur.height <= 1) {
        neighbors.push_back(next);
      }
    } catch (const std::out_of_range& e) {
      //std::cout << e.what() << std::endl;
      continue;
    }
  }
  
  return neighbors;
}

bool Grid::is_valid(Position pos) {
  return pos.r >= 0 && pos.r < data.size() && pos.c >= 0 && pos.c < data[0].size();
}

Location Grid::get(Position pos) {
  if (is_valid(pos)) {
    return data[pos.r][pos.c];
  }
  throw std::out_of_range(std::string("given position: (") + std::to_string(pos.r) + ", "
          + std::to_string(pos.c) + ") is out of grid");
}

Location Grid::back() {
  return data.back().back();
}

int Grid::size() {
  return data.size() * data[0].size();
}