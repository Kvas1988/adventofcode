#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>

int main(int argc, char** argv) {
	std::ifstream input("input01.txt");
	std::string line;
	std::set<int> top3;
	int cur_elf_cal = 0;

	if (input.is_open()) {
		while (std::getline(input, line))	
		{
			if (line == "") {
				// std::cout << "blank" << std::endl;
				if (top3.size() < 3) {
					top3.insert(cur_elf_cal);
				} else {
					if (*top3.begin() < cur_elf_cal) {
						top3.erase(top3.begin());
						top3.insert(cur_elf_cal);
					}
				}
				cur_elf_cal = 0;
			} else {
				int cal = std::stoi(line);
				cur_elf_cal += cal;
			}
		}		
	}

	int result = 0;
	for (int num : top3) {
		result += num;
		std::cout << num << std::endl;
	}

	std::cout << "sum: " << result << std::endl;
  return 0;
}
