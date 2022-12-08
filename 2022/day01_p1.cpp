#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
	std::ifstream input("input01.txt");
	std::string line;
	int biggest_cal = 0;
	int cur_elf_cal = 0;

	if (input.is_open()) {
		while (std::getline(input, line))	
		{
			if (line == "") {
				// std::cout << "blank" << std::endl;
				biggest_cal = cur_elf_cal > biggest_cal ? cur_elf_cal : biggest_cal;
				cur_elf_cal = 0;
			} else {
				int cal = std::stoi(line);
				cur_elf_cal += cal;
			}
		}		
	}

	std::cout << biggest_cal << std::endl;
    return 0;
}
