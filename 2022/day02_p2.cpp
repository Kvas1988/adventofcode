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

int choose_shape(char p1, char choice) {
    
    std::map<std::array<char, 2>, int> rps_comb{
        {{'A', 'Y'}, 3+1}, {{'A', 'Z'}, 6+2}, {{'A', 'X'}, 0+3}, 
        {{'B', 'X'}, 0+1}, {{'B', 'Z'}, 6+3}, {{'B', 'Y'}, 3+2},
        {{'C', 'X'}, 0+2}, {{'C', 'Y'}, 3+3}, {{'C', 'Z'}, 6+1}       
    };
    
    return rps_comb[{p1, choice}];
}

int main(int argc, char** argv) {
	std::ifstream input("input02.txt");
	char player1, player2;
	int total_points = 0;

    while (input >> player1 >> player2)	{
        // std:: cout << player1 << " - " << player2 << std::endl;
        total_points += choose_shape(player1, player2);
    }		

    std::cout << total_points << std::endl;
    return 0;
}
