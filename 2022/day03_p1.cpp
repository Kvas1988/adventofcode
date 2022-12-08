#include <fstream>
#include <iostream>
#include <set>
#include <string>

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
	
	// get priority
	// std::cout << found_item << " - " << (int)found_item << std::endl;
	if (std::isupper(found_item)) {
		std::cout << found_item << " - " << (int)found_item << "converted to: " << (int)found_item - 38 << std::endl;
		return (int)found_item - 38;
	}
	std::cout << found_item << " - " << (int)found_item << " converted to: " << (int)found_item - 96 << std::endl;
	return (int)found_item - 96; //lowercase
}

int main(int argc, char **argv) {
  std::ifstream input("input03.txt");
  std::string backpack;
  int priority_sum = 0;

  if (input.is_open()) {
    while (std::getline(input, backpack)) {
    	// divide backpack by half (comp1 comp2)
    	int mid = backpack.size() / 2;
			std::cout << backpack << std::endl;
			std::string comp1 = backpack.substr(0, mid);
			std::string comp2 = backpack.substr(mid, backpack.size()-1);

    	// find in both comps the same symbol
    	// get priority of item
    	priority_sum += find_item(comp1, comp2);
    	// break;
    }
  }

	std::cout << priority_sum << std::endl;
  return 0;
}
