#include <iostream>
#include <fstream>
#include <vector>

class TreeNode {
public:
    enum Type {Array, Integer};
    //virtual void test() {}

    TreeNode(int i) : integer(i), type(Integer) {}
    TreeNode(Type type) : type(type) {}

    void push_back(TreeNode node) {
      if (type == Array) {
        arr.push_back(node);
      }
    }

    TreeNode operator[](const int& i) const {
      if (type == Integer) {
        if (i == 0) {
          return {integer};
        }
      }

      return arr[i];
    }

    bool operator <(TreeNode other) {
      if (type == Integer && other.type == Integer) {
        return integer < other.integer;
      }

      if (type == Integer) {
        convert_to_arr();
      }
      if (other.type == Integer) {
        other.convert_to_arr();
      }

      for (int i = 0; i < arr.size(); i++) {
        if (i >= other.size()) {
          return false;
        }

        if (arr[i] == other[i]) {
          continue;
        } else {
          return arr[i] < other[i];
        }
      }

      return true;
    }

    bool operator <=(TreeNode other) {
      if (type == Integer && other.type == Integer) {
        return integer <= other.integer;
      }

      if (type == Integer) {
        convert_to_arr();
      }
      if (other.type == Integer) {
        other.convert_to_arr();
      }

      for (int i = 0; i < arr.size(); i++) {
        if (i >= other.size()) {
          return false;
        }

        if (arr[i] == other[i]) {
          continue;
        } else {
          return arr[i] < other[i];
        }
      }
      return true;
    }

    bool operator ==(TreeNode other) {
      if (type == Integer && other.type == Integer) {
        return integer == other.integer;
      }

      if (type == Integer) {
        convert_to_arr();
      }
      if (other.type == Integer) {
        other.convert_to_arr();
      }

      if (size() != other.size()) {
        return false;
      }
      for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == other[i]) {
          continue;
        } else {
          return false;
        }
      }

      return true;
    }

    int size() {
      if (type == Integer) {
        return 1;
      }

      return arr.size();
    }

    Type get_type() { return type; }

private:
    std::vector<TreeNode> arr;
    int integer;
    Type type;

    void convert_to_arr() {
      type = Array;
      arr.push_back(integer);
    }
};


class Parser {
public:
    static TreeNode parse(const std::string& line) {
      int start = 0;
      return parse_expr(line, start);
    }

    static bool is_right_order(std::vector<TreeNode>& pairs) {
      //if (pairs.size() != 2) {
      //  throw std::runtime_error("pairs size is not 2");
      //}

      TreeNode left = pairs[0];
      TreeNode right = pairs[1];

      //int min = std::min(left.size(), right.size());
      //for (int i = 0; i < min; i++) {
      for (int i = 0; i < left.size(); i++) {
        if (i >= right.size()) {
          return false;
        }
        if (left[i] == right[i]) {
          continue;
        } else {
          return left[i] < right[i];
        }
      }
      return true;
    }

private:

    static TreeNode parse_array(const std::string &line, int& start) {
      TreeNode result(TreeNode::Type::Array);
      start++;
      while (line[start] != ']') {
        if (line[start] == ',') {
          start++;
        }
        result.push_back(parse_expr(line, start));
        //start++;
      }

      if (start < line.size()-1) {
        start++;
      }
      return result;
    }

    static TreeNode parse_token(const std::string &line, int& start) {
      int token = 0;
        while (line[start] != ',' && line[start] != ']') {
          if (line[start] >= 48 && line[start] <= 57) {
            int digit = line[start] - '0';
            token = token * 10 + digit;
          }
          start++;
      }
      return {token};
    }

    static TreeNode parse_expr(const std::string &line, int& start) {
      if (line[start] == '[') {
        return parse_array(line, start);
      }  else {
        return parse_token(line, start);
      }
    }
};

class Sorter {
public:
    static void quick_sort(std::vector<TreeNode>& data, int low, int high) {
      if (low < high) {
        int p = partition(data, low, high);

        quick_sort(data, low, p - 1);
        quick_sort(data, p + 1, high);
      }
    }

    static int find_nodes(std::vector<TreeNode>& nodes, TreeNode first, TreeNode second) {
      int first_idx, second_idx;
      for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] == first) {
          first_idx = i;
        }
        if (nodes[i] == second) {
          second_idx = i;
        }
      }
      return first_idx * second_idx;
    }

private:

    static int partition(std::vector<TreeNode>& data, const int& low, const int& high) {
      TreeNode pivot = data[high];
      int i = (low - 1);

      for (int j = low; j < high; j++) {
        if (data[j] <= pivot) {
          i++;
          std::swap(data[i], data[j]);
        }
      }

      std::swap(data[i+1], data[high]);
      return (i + 1);
    }
};

int main() {
  std::ifstream input("input13.txt");
  std::string line;
  int result = 0;
  int index = 1;
  std::vector<TreeNode> pairs;
  std::vector<TreeNode> nodes;

  if (input.is_open()) {
    while (input >> line) {
      TreeNode node = Parser::parse(line);
      pairs.push_back(node);
      nodes.push_back(node);

      if (pairs.size() == 2) {
        if (Parser::is_right_order(pairs)) {
          //if (pairs[0] < pairs[1]) {
          result += index; // debug pair N5
        }
        index++;
        pairs.clear();
      }
    }
  }
  std::cout << "Part 1: " << result << std::endl;

  TreeNode first_node = Parser::parse("[[2]]");
  TreeNode second_node = Parser::parse("[[6]]");
  nodes.push_back(first_node);
  nodes.push_back(second_node);
  Sorter::quick_sort(nodes, 0, nodes.size());
  int second = Sorter::find_nodes(nodes, first_node, second_node);
  std::cout << "Part 2: " << second << std::endl;

  return 0;
}