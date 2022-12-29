#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <set>

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    Point() = default;

    Point operator+(const Point& r) {
      return Point(x + r.x, y + r.y);
    }

    Point& operator+=(const Point& r) {
      this->x += r.x;
      this->y += r.y;
      return *this;
    }

    bool operator !=(const Point& r) const {
      return x != r.x || y != r.y;
    }

    bool operator<(const Point &rhs) const {
      return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y));
    }

    static int deepest_point(const std::set<Point>& points) {
      int max = 0;
      for (Point p : points) {
        max = p.y > max ? p.y : max;
      }
      return max;
    }

    int x;
    int y;
};


void add_points(std::set<Point>& points, Point start, Point end) {

  Point add = start.x == end.x ? Point(0, end.y - start.y >= 0 ? 1 : -1) :
          Point(end.x - start.x >= 0 ? 1 : -1, 0);

  Point current = start;
  while(current != end) {
    points.insert(current);
    current += add;
  }
  points.insert(end);
}

Point drop_sand(const std::set<Point>& rocks, std::set<Point>& sand, Point start, int deepest) {
  Point cur = start;
  Point next = cur + Point(0,1);

  while (cur.y <= deepest) {
    // down
    auto rock_it = rocks.find(next);
    auto sand_it = sand.find(next);
    if (rock_it == rocks.end() && sand_it == sand.end()) {
      cur = next;
      next += Point(0,1);
      continue;
    }

    //down-left
    Point next_left = next + Point(-1,0);
    rock_it = rocks.find(next_left);
    sand_it = sand.find(next_left);
    if (rock_it == rocks.end() && sand_it == sand.end()) {
      cur = next_left;
      next = next_left + Point(0,1);
      continue;
    }

    //down-right
    Point next_right = next + Point(1,0);
    rock_it = rocks.find(next_right);
    sand_it = sand.find(next_right);
    if (rock_it == rocks.end() && sand_it == sand.end()) {
      cur = next_right;
      next = next_right + Point(0,1);
      continue;
    }
    return cur;
  }
  return cur;
}


int sandflow(const std::set<Point>& points, Point start) {
  int deepest = Point::deepest_point(points);
  std::set<Point> sand;

  Point new_point = drop_sand(points, sand, start, deepest);
  sand.insert(new_point);
  int result = 1;
  while (new_point != start) { // TODO: what's the condition
    new_point = drop_sand(points, sand, start, deepest);
    if (new_point.y > deepest) {
      break;
    }
    sand.insert(new_point);
    result++;
  }
  return result;
}


int main() {
  std::ifstream input("input14.txt");
  std::string line;
  std::set<Point> points;

  if (input.is_open()) {
    std::string str;
    int x,y;

    while (std::getline(input, line)) {
      std::istringstream stream(line);
      std::vector<Point> lines;

      while(stream >> str) {
        if (str != "->") {
          x = std::stoi(str.substr(0, str.find(',')));
          y = std::stoi(str.substr(str.find(',')+1));
          Point p(x,y);

          if (lines.size() > 0) {
            add_points(points, lines.back(), p);
          }
          lines.push_back(p);
          //std::cout << x << ", " << y <<std::endl;
        }
      }
    }
  }

  Point start(500, 0);
  std::cout << "Part 1: " << sandflow(points, start) << std::endl;

  return 0;
}