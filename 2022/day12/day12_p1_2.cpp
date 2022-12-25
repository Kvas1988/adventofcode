#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stdexcept>

#include "grid.h"

std::vector<Location> reconstruct_path(Location start,
                      Location goal,
                      std::unordered_map<Location, Location, LocationHasher> came_from) {

  std::vector<Location> path;
  Location current = goal;
  if (came_from.find(goal) == came_from.end()) {
    throw std::runtime_error("can't find the way");
    //return path; // no path can be found
  }

  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }

  //path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

void dijkstra_search(Grid grid, const Location& start, const Location& goal,
                     std::unordered_map<Location, Location, LocationHasher>& came_from,
                     std::unordered_map<Location, double, LocationHasher>& cost_so_far) {

  std::queue<Location> frontier;
  frontier.push(start);

  came_from[start] = start;
  cost_so_far[start] = 0;

  while(!frontier.empty()) {
    Location current = frontier.front();
    frontier.pop();

    if (current == goal) {
      break;
    }

    for (const Location& next : grid.neighbors(current)) {
      double new_cost = cost_so_far[current] + 1;
      if (cost_so_far.find(next) == cost_so_far.end() ||
          new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        came_from[next] = current;
        frontier.push(next);
      }
    }
  }
}

int main() {
  std::ifstream input("day12/input12.txt");
  std::string line;
  Grid grid;
  Location start;
  Location goal;

  std::vector<Location> short_starts;

  if (input.is_open()) {
    while (std::getline(input, line)) {
      grid.add_row(); 
      for (char c : line) {
        if (c == 'S') {
          // start
          grid.push_back('a');
          start = grid.back();
          short_starts.push_back(start);
        } else if (c == 'E') {
          // goal
          grid.push_back('z');
          goal = grid.back();
        } else {
          grid.push_back(c);
          if (c == 'a') {
            short_starts.push_back(grid.back());
          }
        }
      }
    }
  } else {
    std::cout << "Error reading file" << std::endl;
  }

  { // part 1
    std::unordered_map<Location, Location, LocationHasher> came_from;
    std::unordered_map<Location, double, LocationHasher> cost_so_far;
    dijkstra_search(grid, start, goal, came_from, cost_so_far);

    std::vector<Location> path = reconstruct_path(start, goal, came_from);
    std::cout << "Part 1: " << path.size() << std::endl;
  }

  { // part 2
    int min = grid.size();

    for (Location possible_start : short_starts) {
      std::unordered_map<Location, Location, LocationHasher> came_from;
      std::unordered_map<Location, double, LocationHasher> cost_so_far;
      dijkstra_search(grid, possible_start, goal, came_from, cost_so_far);
      try {
        std::vector<Location> path = reconstruct_path(possible_start, goal, came_from);
        if (path.size() < min) {
          min = path.size();
        }
      } catch (const std::runtime_error& e) {
        continue;
      }
    }

    std::cout << "Part 2: " << min << std::endl;
  }
  return 0;
}


