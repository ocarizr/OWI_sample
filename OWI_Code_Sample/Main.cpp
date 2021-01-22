#include <vector>
#include <iostream>
#include <algorithm>
#include "puzzle_solver.h"

int main()
{
	std::string input = "aaaa,AAAA,AAAA,aaaa";
	auto is_solution = puzzle_solver::check_if_solution(input);
	int amount_of_solutions = 0;
	std::set<std::string> all_solutions;

	if (is_solution)
	{
		amount_of_solutions = puzzle_solver::get_amount_of_solutions(input);

		if (amount_of_solutions > 0)
		{
			all_solutions = puzzle_solver::get_all_solutions(input);
		}
	}

	std::cout << input << (is_solution ? " is" : " isn't") << " a solution for the puzzle." << std::endl;
	std::cout << input << " input has " << amount_of_solutions << (amount_of_solutions > 1 ? " solutions" : " solution") << std::endl;

	std::cout << "The " << amount_of_solutions << (amount_of_solutions > 1 ? " solutions " : " solution ") << " of " << input
		<< (amount_of_solutions > 1 ? " are:" : " is:") << std::endl;
	std::for_each(std::cbegin(all_solutions), std::cend(all_solutions),
		[](const std::string& solution)
		{
			std::cout << solution << "\n";
		});

	return 0;
}
