#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
// TODO: not done...

class Monkey {
private:
  uint1024_t operation(uint1024_t num1, char sign, uint1024_t num2) {
    switch (sign) {
      case '*':
        return num1 * num2;
      case '+':
        return num1 + num2;
      case '-':
        return num1 - num2;
      case '/':
        return num1 / num2;
    }
    return 0;
  }

public:

  static void handle_round(std::vector<Monkey>& monkeys) {
    for (Monkey& monkey : monkeys) {
      while (!monkey.items.empty()) {
        monkey.inspected++;
        uint1024_t item = monkey.items.front();
        uint1024_t worry_level = monkey.calculate_worry_level(item);

        int monkey_to_throw;
        if (worry_level % monkey.divisible == 0) {
          monkey_to_throw = monkey.true_monkey;
        } else {
          monkey_to_throw = monkey.false_monkey;
        }
        monkeys[monkey_to_throw].items.push(worry_level);
        monkey.items.pop();
      }
    }
  }

  uint1024_t calculate_worry_level(uint1024_t item) {
    if (use_old_num) {
      return operation(item, operation_sign, item);
    }
    return operation(item, operation_sign, operation_num);
  }

  // std::vector<int> items;
  std::queue<uint1024_t> items;
  char operation_sign;
  uint1024_t operation_num;
  bool use_old_num;
  int divisible;
  int true_monkey;
  int false_monkey;
  int inspected = 0;
};

void parse(const std::string& line, std::vector<Monkey>& monkeys) {
  std::stringstream stream(line);
  std::string word, tmp;
  stream >> word;
  // std::cout << word << std::endl;
  if (word == "Monkey") {
    // add monkey
    monkeys.push_back(Monkey());
  } else if (word == "Starting") {
    while (stream >> tmp) {
      if (tmp != "items:") {
        int num = std::stoi(tmp.substr(0, tmp.find(',')));
        // monkeys.back().items.push_back(num);
        monkeys.back().items.push(num);
      }
    }
  } else if (word == "Operation:") {
    char sign;
    std::string num;
    stream >> tmp >> tmp >> tmp >> sign >> num;
    monkeys.back().operation_sign = sign;
    if (num == "old") {
      monkeys.back().use_old_num = true;
      monkeys.back().operation_num = 0;
    } else {
      monkeys.back().operation_num = std::stoi(num);
    }
  } else if (word == "Test:") {
    int div;
    stream >> tmp >> tmp >> div;
    monkeys.back().divisible = div;
  } else if (word == "If") {
    int num;
    std::string cond;
    stream >> cond >> tmp >> tmp >> tmp >> num;
    if (cond == "true:") {
      // true_monkey
      monkeys.back().true_monkey = num;
    } else {
      // false_monkey
      monkeys.back().false_monkey = num;
    }
  }
}

int main() {
  std::ifstream input("input11_1.txt");
  std::string line;
  std::vector<Monkey> monkeys;

  if (input.is_open()) {
    while (std::getline(input, line)) {
      parse(line, monkeys);
    }
  }

  for (int i = 0; i < 10000; i++) {
    Monkey::handle_round(monkeys);
  }

  std::set<int> scores;
  for (Monkey monkey : monkeys) {
    scores.insert(monkey.inspected);
    std::cout << monkey.inspected << std::endl;
  }

  std::cout << "==============" << std::endl;
  auto it = scores.rbegin();
  uint1024_t result = *it;
  it++;
  result *= *it;
  std::cout << result << std::endl;

  return 0;
}


