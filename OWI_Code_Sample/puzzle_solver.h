#pragma once
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include "board.h"

class puzzle_solver
{
	static bool check_if_solution(board& table)
	{
		try
		{
			for (size_t i = 0; i < table.get_size(); ++i)
			{
				for (size_t j = 0; j < table.get_size(); ++j)
				{
					position pos(i, j);
					auto upper = position::get_upper(pos);
					auto left = position::get_left(pos);

					auto upper_piece = table.get_piece_from(upper);
					auto left_piece = table.get_piece_from(left);

					if (!table.get_board_arrangement()[i][j].check_left_and_top_connections(left_piece, upper_piece)) throw false;
				}
			}

			return true;
		}
		catch (bool error)
		{
			return error;
		}
	}

	static void iterate_though_possibilities(const int& slots, std::vector<piece>& pieces_input, std::set<std::string>& result)
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

			position pos(vertical, horizontal);

			for (size_t j = 0; j < 4; ++j)
			{
				pieces[i].rotate();
				board table(pieces);
				auto left = position::get_left(pos);
				auto upper = position::get_upper(pos);

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
						iterate_though_possibilities(reduce_slots, pieces, result);
					}
				}
			}
		}
	}

public:
	static bool is_input_valid(std::string input)
	{
		// The input needs to build a square board
		// Each piece has only four sides
		// Only letters (a-z and A-Z) are allowed

		try
		{
			if (input.empty()) throw false;

			std::vector<std::string> pieces_input;
			size_t strmax = sizeof input.data();
			char* next;
			char* token = strtok_s(input.data(), ",", &next);

			while (token != nullptr)
			{
				pieces_input.push_back(token);
				token = strtok_s(nullptr, ",", &next);
			}
			double sqr = sqrt(std::size(pieces_input));

			if ((sqr - floor(sqr)) != 0)
			{
				throw false;
			}

			std::for_each(std::begin(pieces_input), std::end(pieces_input),
				[](std::string& piece_input)
				{
					if (std::size(piece_input) != 4)
					{
						throw false;
					}

					if (std::any_of(std::begin(piece_input), std::end(piece_input),
						[](const char& letter)
						{
							return !(letter > 64 && letter < 91) && !(letter > 96 && letter < 123);
						}))
					{
						throw false;
					}
				});

			return true;
		}
		catch (bool error)
		{
			return error;
		}
	}

	static bool check_if_solution(std::string input)
	{
		if (!is_input_valid(input)) return false;

		board table(input);

		return check_if_solution(table);
	}

	static int get_amount_of_solutions(std::string input)
	{
		if (!is_input_valid(input)) return -1;

		return get_all_solutions(input).size();
	}

	static std::set<std::string> get_all_solutions(std::string input)
	{
		std::set<std::string> result;
		if (!is_input_valid(input)) return result;

		std::vector<std::string> pieces_input;
		size_t strmax = sizeof input.data();
		char* next;
		char* token = strtok_s(input.data(), ",", &next);

		while (token != nullptr)
		{
			pieces_input.push_back(token);
			token = strtok_s(nullptr, ",", &next);
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

		iterate_though_possibilities(slots, pieces, result);
		
		return result;
	}
};

