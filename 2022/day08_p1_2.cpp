#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>

bool left(std::vector<std::vector<int>>& trees, int r, int c) {
  int tree = trees[r][c];
  for (int col = 0; col < c; col++) {
    if (trees[r][col] >= tree) {
      return false;
    }
  }
  return true;
}

bool right(std::vector<std::vector<int>>& trees, int r, int c) {
  int tree = trees[r][c];
  for (int col = c+1; col < trees[r].size(); col++) {
    if (trees[r][col] >= tree) {
      return false;
    }
  }
  return true;
}

bool up(std::vector<std::vector<int>>& trees, int r, int c) {
  int tree = trees[r][c];
  for (int raw = 0; raw < r; raw++) {
    if (trees[raw][c] >= tree) {
      return false;
    }
  }
  return true;
}

bool down(std::vector<std::vector<int>>& trees, int r, int c) {
  int tree = trees[r][c];
  for (int raw = r+1; raw < trees.size(); raw++) {
    if (trees[raw][c] >= tree) {
      return false;
    }
  }
  return true;
}

int parse_trees(std::vector<std::vector<int>>& trees) {
  int result = trees.size() * 2 + (trees[0].size() - 2) * 2;

  for (int r = 1; r < trees.size()-1; r++) {
    for (int c = 1; c < trees[r].size()-1; c++) {
      if (left(trees, r, c) || right(trees, r, c) || up(trees, r, c) || down(trees, r, c)) {
        result++;
      }
    }
  }

  return result;
}

// PART 2
int left_from_tree(std::vector<std::vector<int>>& trees, int r, int c) {
  int result = 0;
  int tree = trees[r][c];

  for (int col = c-1; col >= 0; col--) {
    result++;
    if (trees[r][col] >= tree) {
      return result;
    }
  }
  return result;
}

int right_from_tree(std::vector<std::vector<int>>& trees, int r, int c) {
  int result = 0;
  int tree = trees[r][c];

  for (int col = c+1; col < trees[r].size(); col++) {
    result++;
    if (trees[r][col] >= tree) {
      return result;
    }
  }
  return result;
}

int up_from_tree(std::vector<std::vector<int>>& trees, int r, int c) {
  int result = 0;
  int tree = trees[r][c];

  for (int raw = r - 1; raw >= 0; raw--) {
    result++;
    if (trees[raw][c] >= tree) {
      return result;
    }
  }
  return result;
}

int down_from_tree(std::vector<std::vector<int>>& trees, int r, int c) {
  int result = 0;
  int tree = trees[r][c];

  for (int raw = r + 1; raw < trees.size(); raw++) {
    result++;
    if (trees[raw][c] >= tree) {
      return result;
    }
  }
  return result;
}

int look_from_tree(std::vector<std::vector<int>>& trees) {
  int result = 0;

  for (int r = 1; r <trees.size()-1; r++) {
    for (int c = 1; c <trees[0].size()-1; c++) {
      int tree_result = left_from_tree(trees, r, c) * right_from_tree(trees, r, c) * up_from_tree(trees, r, c) *
              down_from_tree(trees, r, c);
      if (result < tree_result) {
        result = tree_result;
      }
    }
  }

  return result;
}

int main() {
  std::ifstream input("input08.txt");
  std::string line;

  std::vector<std::vector<int>> trees;
  int r = 0;
  if (input.is_open()) {
    while (std::getline(input, line)) {
      trees.push_back( std::vector<int>());
      for (int i = 0; i < line.size(); i++) {
        int tree =  line.at(i) - '0';
        trees[r].push_back(tree);
      }
      r++;
    }
  }

  std::cout << "Part 1: " << parse_trees(trees) << std::endl;
  std::cout << "Part 2: " << look_from_tree(trees) << std::endl;

  return 0;
}