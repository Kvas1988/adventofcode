#pragma once
#include <vector>
#include "location.h"

class Grid {
public:
  void add_row();
  // void add_loc(Location loc);
  void push_back(char c); // get r, c and insert to data
  std::vector<Location> neighbors(Location cur); 
  Location back();
  Location get(Position pos);
  bool is_valid(Position pos);
  int size();
private:
    std::vector<std::vector<Location>> data;
};


