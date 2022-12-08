#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>

int handle_round(char p1, char p2) {
    
    std::map<std::array<char, 2>, int> rps_comb{
        {{'A', 'Y'}, 6+2}, {{'A', 'Z'}, 0+3}, {{'A', 'X'}, 3+1}, 
        {{'B', 'X'}, 0+1}, {{'B', 'Z'}, 6+3}, {{'B', 'Y'}, 3+2},
        {{'C', 'X'}, 6+1}, {{'C', 'Y'}, 0+2}, {{'C', 'Z'}, 3+3}       
    };
    
    return rps_comb[{p1, p2}];
}

int main(int argc, char** argv) {
	std::ifstream input("input02.txt");
	char player1, player2;
	int total_points = 0;

    while (input >> player1 >> player2)	{
        // std:: cout << player1 << " - " << player2 << std::endl;
        total_points += handle_round(player1, player2);
    }		

    std::cout << total_points << std::endl;
    return 0;
}
