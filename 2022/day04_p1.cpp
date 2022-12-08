#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class Region
{
public:
  Region(int l, int r) : l(l), r(r) {}

  int l;
  int r;

  bool is_full_overlap(Region& other) {
    if ((l <= other.l && other.l <= r && l <= other.r && other.r <= r) ||
        (other.l <= l && l <= other.r && other.l <= r && r <= other.r)
        ) {
      return true;
    }
    return false;
  }

  bool is_overlap(Region& other) {
    if ((l <= other.l && other.l <= r) || (other.l <= l && l <= other.r)) {
      return true;
    }
    return false;
  }
};

int main(int argc, char* argv[]) {
  std::ifstream input("input04.txt");
  std::string line;
  int result = 0;

  if (input.is_open()) {
    // 2-9,9-51
    int l1, r1, l2, r2;
    char tmp;
    while (input >> l1 >> tmp >> r1 >> tmp >> l2 >> tmp >> r2) {
      // std::cout << l1 << "_" << r1 << "," << l2 << "_" << r2 << std::endl;
      Region reg1(l1, r1);
      Region reg2(l2, r2);
      result += reg1.is_overlap(reg2);
    }
  }

  std::cout << result << std::endl;
  return 0;
}
