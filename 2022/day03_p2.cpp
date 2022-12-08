#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>

int get_priority(char found_item) {
	// get priority
	// std::cout << found_item << " - " << (int)found_item << std::endl;
	if (std::isupper(found_item)) {
		std::cout << found_item << " - " << (int)found_item << "converted to: " << (int)found_item - 38 << std::endl;
		return (int)found_item - 38;
	}
	std::cout << found_item << " - " << (int)found_item << " converted to: " << (int)found_item - 96 << std::endl;
	return (int)found_item - 96; //lowercase
}

int find_item(std::string comp1, std::string comp2) {
	if (comp1.size() != comp2.size()) {
		std::cout << "comps are not equal" << std::endl;
		std::cout << comp1 << " size: " << comp1.size() << "\n" 
			<< comp2 << " size: " << comp2.size() << std::endl;
		return 0;
	}
	
	std::cout << comp1 << " size: " << comp1.size() << "\n" 
		<< comp2 << " size: " << comp2.size() << std::endl;
	
	char found_item;
	std::set<char> c1, c2;
	for (size_t i = 0; i < comp1.size(); i++) {
		char item_c1 = comp1.at(i);
		char item_c2 = comp2.at(i);

		c1.insert(item_c1);
		c2.insert(item_c2);

		if (auto search = c1.find(item_c2); search != c1.end()) {
			found_item = item_c2;
			break;
		}

		if (auto search = c2.find(item_c1); search != c2.end()) {
			found_item = item_c1;
			break;
		}
	}

	return get_priority(found_item);
}



int calc_group(std::vector<std::string>& group) {
	std::map<char, std::set<int>> group_inv;
	for (int bagnum = 0; bagnum < group.size(); bagnum++) {
		std::cout << group[bagnum] << std::endl;
		for (char ch : group[bagnum]) {
			group_inv[ch].insert(bagnum);
		}
	}

	for (auto pair : group_inv) {
		if (pair.second.size() == 3) {
			return get_priority(pair.first);
		}
	}

	std::cout << "Didn't find a common item" << std::endl;
	// return -1000000000;
	return 0;
}

int main(int argc, char **argv) {
  std::ifstream input("input03.txt");
  std::string backpack;
  int priority_sum = 0;

	std::vector<std::string> group;
  if (input.is_open()) {
    while (std::getline(input, backpack)) {
			group.push_back(backpack);
			if (group.size() == 3) {
				priority_sum += calc_group(group);
				group.clear();
			} 
    }
  }

	std::cout << priority_sum << std::endl;
  return 0;
}
