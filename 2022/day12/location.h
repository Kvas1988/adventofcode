#include <functional>
struct Position {
  public:
    Position(int r, int c) : r(r), c(c) {}
    Position() = default;

    Position operator+ (Position other) const {
      return Position(r + other.r, c + other.c);
    }

    int r; 
    int c;
};


class Location {
public:
  Location() = default;
  Location(int r, int c, char height) : height(height) {
    pos = Position(r, c);
  }

  Location(const Location& loc) {
    pos = loc.pos;
    height = loc.height;
  }

    //Location(std::__hash_value_type<Location, double> type) {
    //
    //}

    bool operator==(const Location& other) const {
    return pos.r == other.pos.r && pos.c == other.pos.c && height == other.height;
  }

  bool operator !=(const Location& other) const {
    return pos.r != other.pos.r || pos.c != other.pos.c || height != other.height;
  }

  Position pos;
  char height;
};

struct LocationHasher {
  std::size_t operator()(const Location& loc) const {
    return ((std::hash<int>()(loc.pos.r)
          ^ (std::hash<int>()(loc.pos.c) << 1)) >> 1)
          ^ (std::hash<int>()(loc.height) << 1);
  }
};
