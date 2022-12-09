#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

void regroup_map(std::map<char, int>& seq, int i) {
    for (auto it = seq.begin(); it != seq.end(); ) {
        if (it->second <= i) {
            it = seq.erase(it);
        } else {
            it++;
        }
    }
}

int parse_line_map(const std::string& line, int len) {
    std::map<char, int> seq;

    for (int i = 0; i < line.size(); i++) {
        char sym = line.at(i);
        auto it = seq.find(sym);
        if (it != seq.end()) {
            regroup_map(seq, it->second);
        }

        seq[sym] = i;
        if (seq.size() >= len) {
            return i+1;
        }
    }

    return 0;
}

int main() {
    std::ifstream input("input06.txt");
    std::string line;
    if (input.is_open()) {
        std::getline(input, line);
    }

    std::cout << parse_line_map(line,4) << std::endl;
    std::cout << parse_line_map(line,14) << std::endl;

    return 0;
}