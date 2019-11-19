#pragma once
#include <set>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include "board.h"

class puzzle_solver
{
	static void iterate_through_possibilities(const int& slots, std::vector<piece>& pieces_input, std::set<std::string>& result) noexcept
	{
		int side_size = sqrt(std::size(pieces_input));
		for (size_t i = std::size(pieces_input) - slots; i < std::size(pieces_input); ++i)
		{
			auto pieces(pieces_input);

			int index = std::size(pieces) - slots;
			piece aux = pieces[index];
			pieces[index] = pieces[i];
			pieces[i] = aux;
			
			bool has_solution = false;

			int horizontal = i % side_size;
			int vertical = i / side_size;

			for (size_t j = 0; j < 4; ++j)
			{
				pieces[i].rotate();
				board table(pieces);
				auto left = position::get_left(vertical, horizontal);
				auto upper = position::get_upper(vertical, horizontal);

				auto left_piece = table.get_piece_from(left);
				auto upper_piece = table.get_piece_from(upper);

				has_solution = pieces[i].check_left_and_top_connections(left_piece, upper_piece);

				if (has_solution)
				{
					if (slots == 1)
					{
						result.emplace(table.to_string());
					}
					else
					{
						int reduce_slots = slots - 1;
						iterate_through_possibilities(reduce_slots, pieces, result);
					}
				}
			}
		}
	}

public:
	static bool is_input_valid(std::string input) noexcept
	{
		// The input needs to build a square board
		// Each piece has only four sides
		// Only letters (a-z and A-Z) are allowed

		bool result = true;

		if (input.empty()) result = false;
		
		if (result)
		{
			std::vector<std::string> pieces_input;
			char* token = strtok(input.data(), ",");

			while (token != nullptr)
			{
				pieces_input.push_back(token);
				token = strtok(nullptr, ",");
			}
			double sqr = sqrt(std::size(pieces_input));

			if (sqr == 1 || (sqr - floor(sqr)) != 0)
			{
				result = false;
			}
		}

		for (int i = 0; i < std::size(pieces_input) && result; ++i)
		{
			if (std::size(pieces_input[i]) != 4)
			{
				result = false;
			}

			if (std::any_of(std::begin(pieces_input[i]), std::end(pieces_input[i]),
				[](const char& letter)
				{
					return !(letter > 64 && letter < 91) && !(letter > 96 && letter < 123);
				}))
			{
				result = false;
			}
		}
		return result;
	}

	static bool check_if_solution(std::string input) noexcept
	{
		if (!is_input_valid(input)) return false;

		board table(input);

		return check_if_solution(table);
	}

	static int get_amount_of_solutions(std::string input) noexcept
	{
		if (!is_input_valid(input)) return -1;

		return get_all_solutions(input).size();
	}

	static std::set<std::string> get_all_solutions(std::string input) noexcept
	{
		std::set<std::string> result;
		if (!is_input_valid(input)) return result;

		std::vector<std::string> pieces_input;
		char* token = strtok(input.data(), ",");

		while (token != nullptr)
		{
			pieces_input.push_back(token);
			token = strtok(nullptr, ",");
		}

		int slots = std::size(pieces_input);

		std::vector<piece> pieces(std::size(pieces_input));

		for (size_t i = 0; i < std::size(pieces_input); ++i)
		{
			int size = sqrt(std::size(pieces_input));
			int horizontal = i % size;
			int vertical = i / size;

			position pos(vertical, horizontal);
			piece pc(pieces_input[i], pos);
			pieces[i] = pc;
		}

		iterate_through_possibilities(slots, pieces, result);
		
		return result;
	}
};

