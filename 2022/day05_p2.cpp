#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <algorithm> // std::copy
#include <iterator>

void print_crates(std::map<int, std::deque<char>>& crates) {
    for (auto crate : crates) {
        std:: cout << crate.second.back() << " - " << crate.second.size() << std::endl;
    }
}

void add_data(const std::string& line, std::map<int, std::deque<char>>& crates) {
    int ptr = 1;
    int crate_num = 1;
    while (ptr < line.size()) {
        if (line.at(ptr) != ' ') {
            crates[crate_num].push_front(line.at(ptr));
        }
        ptr += 4;
        crate_num++;
    }
}

void handle_commands(const std::string& line, std::map<int, std::deque<char>>& crates) {
    std::stringstream stream(line);
    std::string tmp;
    int block_num, crate_from, crate_to;
    stream >> tmp >> block_num >> tmp >> crate_from >> tmp >> crate_to;

    for (int i = 0; i < block_num; ++i) {
        char block = crates[crate_from].back();
        crates[crate_to].push_back(block);
        crates[crate_from].pop_back();
    }
}

void handle_commands9001(const std::string& line, std::map<int, std::deque<char>>& crates) {
    std::stringstream stream(line);
    std::string tmp;
    int block_num, crate_from, crate_to;
    stream >> tmp >> block_num >> tmp >> crate_from >> tmp >> crate_to;

    //char blocks[block_num];
    std::vector<char> blocks;
    for (int i = 0; i < block_num; i++) {
        //blocks[i] = crates[crate_from].back();
        blocks.push_back(crates[crate_from].back());
        crates[crate_from].pop_back();
    }
    std::copy(blocks.rbegin(), blocks.rend(), std::back_inserter(crates[crate_to]));
}

int main (int argc, char* argv[]) {
    std::ifstream input("input05.txt");
    std::string line;

    std::map<int, std::deque<char>> crates;


    if (input.is_open()) {
        int it = 1;
        while (std::getline(input, line)) {
            if (it <= 8) {
                add_data(line, crates);
            } else if (it == 10) {
                // debug
                print_crates(crates);
            } else if (it >= 11) {
                handle_commands9001(line, crates);
            }
            it++;
        }
    }  else {
        std::cout << "Error reading file" << std::endl;
    }

    std::cout << "===============" << std::endl;
    print_crates(crates);
    return 0;
}
