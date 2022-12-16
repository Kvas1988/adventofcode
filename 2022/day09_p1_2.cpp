#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

class Position {
public:
    Position(int x, int y) : x(x), y(y) {}
    Position() = default;
    bool operator==(const Position &rhs) const;
    bool operator<(const Position &rhs) const;
    Position operator-(const Position &rhs) const;
    Position operator+(const Position &rhs) const;

public:
    int x = 0;
    int y = 0;
};

bool Position::operator==(const Position& rhs) const {
  return x == rhs.x &&
         y == rhs.y;
}

bool Position::operator<(const Position &rhs) const {
  return x < rhs.x || (x == rhs.x && y < rhs.y);
}

Position Position::operator-(const Position& rhs) const {
  return {x - rhs.x, y - rhs.y};
}

Position Position::operator+(const Position& rhs) const {
  return {x + rhs.x, y + rhs.y};
}

void move(Position& head, Position& tail, char dir, int steps, std::set<Position>& history);
void move(std::vector<Position>& rope, char dir, int steps, std::set<Position>& history);
void move_tail(Position& head, Position& tail);

int main() {
  std::ifstream input("input09.txt");
  std::set<Position> history;

  Position head, tail; // part 1

  // part 2
  std::vector<Position> rope;
  for (int i = 0; i < 10; i++) {
    rope.push_back(Position());
  }

  if (input.is_open()) {
    char dir;
    int steps;
    while (input >> dir >> steps) {
      //move(head, tail, dir, steps, history); // part 1
      move(rope, dir, steps, history); // part 2
    }
  }

  std::cout << "Answer: " << history.size() << std::endl;
  return 0;
}

// Part 1
void move(Position& head, Position& tail, char dir, int steps, std::set<Position>& history) {
  for (int i = 1; i <= steps; i++) {
    switch (dir) {
      case 'U':
        head.y++;
        break;
      case 'D':
        head.y--;
        break;
      case 'R':
        head.x++;
        break;
      case 'L':
        head.x--;
        break;
    }
    move_tail(head, tail);
    history.insert(tail);
  }
}

// Part 2
void move(std::vector<Position>& rope, char dir, int steps, std::set<Position>& history) {
  Position* head = &rope[0];
  for (int i = 1; i <= steps; i++) {
    switch (dir) {
      case 'U':
        head->y++;
        break;
      case 'D':
        head->y--;
        break;
      case 'R':
        head->x++;
        break;
      case 'L':
        head->x--;
        break;
    }
    for (int j = 1; j < rope.size(); j++) {
      move_tail(rope[j-1], rope[j]);
    }
    history.insert(rope.back());
  }
}

void move_tail(Position& head, Position& tail) {
  Position dist = head - tail;
  if (abs(dist.x) < 2 && abs(dist.y) < 2) {
    return;
  }

  bool moved_x = false;

  if (dist.x >= 2) {
    tail.x++;
    moved_x = true;
  } else if (dist.x <= -2) {
    tail.x--;
    moved_x = true;
  }

  if (moved_x) {
    if (dist.y >= 1) {
      tail.y++;
    } else if (dist.y <= -1) {
      tail.y--;
    }
    return;
  }

  bool moved_y = false;
  if (dist.y >= 2) {
    tail.y++;
    moved_y = true;
  } else if (dist.y <= -2) {
    tail.y--;
    moved_y = true;
  }

  if (moved_y) {
    if (dist.x >= 1) {
      tail.x++;
    } else if (dist.x <= -1) {
      tail.x--;
    }
  }
}
