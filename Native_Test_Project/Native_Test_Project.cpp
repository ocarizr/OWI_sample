#include "pch.h"
#include "CppUnitTest.h"
#include "../OWI_Code_Sample/puzzle_solver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NativeTestProject
{
	TEST_CLASS(GeneralTests)
	{
	public:
		TEST_METHOD(is_validating_input)
		{
			Assert::IsTrue(puzzle_solver::is_input_valid("aaaa,AAAA,aaaa,AAAA"));
			Assert::IsFalse(puzzle_solver::is_input_valid("aaaa,AAAA,aaaa,AAAA,aaaa"));
			Assert::IsFalse(puzzle_solver::is_input_valid("aaaa,AAAA,aaaa,AAAAa"));
		}
	};

	TEST_CLASS(PieceTests)
	{
	public:
		TEST_METHOD(is_piece_constructor_working)
		{
			std::string input = "aBcD";
			position pos(0, 0);

			piece pc(input, pos);

			Assert::AreEqual(pc.get_left(), input[0]);
			Assert::AreEqual(pc.get_top(), input[1]);
			Assert::AreEqual(pc.get_bottom(), input[2]);
			Assert::AreEqual(pc.get_right(), input[3]);
		}

		TEST_METHOD(is_piece_copy_working)
		{
			std::string input = "aBcD";
			position pos(0, 0);

			piece pc(input, pos);
			piece other_piece(pc);

			Assert::AreEqual(other_piece.get_left(), input[0]);
			Assert::AreEqual(other_piece.get_top(), input[1]);
			Assert::AreEqual(other_piece.get_bottom(), input[2]);
			Assert::AreEqual(other_piece.get_right(), input[3]);

			piece another_piece;
			another_piece = pc;

			Assert::AreEqual(another_piece.get_left(), input[0]);
			Assert::AreEqual(another_piece.get_top(), input[1]);
			Assert::AreEqual(another_piece.get_bottom(), input[2]);
			Assert::AreEqual(another_piece.get_right(), input[3]);

			Assert::IsTrue(other_piece == pc);
			Assert::IsTrue(another_piece == pc);
			Assert::IsFalse(another_piece != pc);
		}

		TEST_METHOD(check_piece_connection)
		{
			std::optional<piece> left, top;

			std::string input = "aBcD";
			position pos(0, 0);

			piece pc(input, pos);

			Assert::IsTrue(pc.check_left_and_top_connections(left, top));

			{
				pos.change(0, 1);
				piece other("dCba", pos);
				top.emplace(other);
			}

			{
				pos.change(1, 0);
				piece other("cBDA", pos);
				left.emplace(other);
			}

			Assert::IsTrue(pc.check_left_and_top_connections(left, top));

			{
				left.reset();
				piece other("cBDa", pos);
				left.emplace(other);
			}

			Assert::IsFalse(pc.check_left_and_top_connections(left, top));
		}

		TEST_METHOD(to_string_is_working)
		{
			std::string input = "aBcD";
			position pos(0, 0);

			piece pc(input, pos);

			Assert::AreEqual(pc.to_string(), input);
		}
	};

	TEST_CLASS(PositionTests)
	{
	public:
		TEST_METHOD(position_constructor_and_overload_working)
		{
			position pos(4, 2);

			Assert::AreEqual(pos.get_horizontal(), 2);
			Assert::AreEqual(pos.get_vertical(), 4);

			position other_pos(pos);

			Assert::AreEqual(other_pos.get_horizontal(), 2);
			Assert::AreEqual(other_pos.get_vertical(), 4);

			position another_pos = pos;

			Assert::AreEqual(another_pos.get_horizontal(), 2);
			Assert::AreEqual(another_pos.get_vertical(), 4);

			position final_pos(4, 2);

			Assert::IsTrue(pos == final_pos);
			Assert::IsFalse(pos != final_pos);
		}

		TEST_METHOD(position_getters_working)
		{
			position pos(4, 2);

			Assert::AreEqual(pos.get_horizontal(), 2);
			Assert::AreEqual(pos.get_vertical(), 4);
		}

		TEST_METHOD(change_position_working)
		{
			position pos;
			pos.change(1, 1);

			Assert::AreEqual(pos.get_horizontal(), 1);
			Assert::AreEqual(pos.get_vertical(), 1);
		}

		TEST_METHOD(get_side_positions)
		{
			int cell = 2;

			position left = position::get_left(cell, cell);
			position upper = position::get_upper(cell, cell);

			Assert::AreEqual(2, left.get_vertical());
			Assert::AreEqual(1, left.get_horizontal());
			Assert::AreEqual(1, upper.get_vertical());
			Assert::AreEqual(2, upper.get_horizontal());
		}
	};

	TEST_CLASS(BoardTests)
	{
		TEST_METHOD(constructors_and_overloads_working)
		{
			board table("aaaa,AAAA,aaaa,AAAA");

			matrix sample(2);

			std::string piece_input[4]{ "aaaa","AAAA","aaaa","AAAA" };

			for (int i = 0; i < 4; ++i)
			{
				int horizontal = i % 2;
				int vertical = i / 2;

				position pos(vertical, horizontal);
				piece pc(piece_input[i], pos);
				sample[vertical].push_back(pc);
			}

			Assert::AreEqual(table.get_size(), 2);
			Assert::IsTrue(custom_comparison::compare_matrix(table.get_board_arrangement(), sample));

			board other_table(table);

			Assert::AreEqual(table.get_size(), other_table.get_size());
			Assert::IsTrue(custom_comparison::compare_matrix(table.get_board_arrangement(), other_table.get_board_arrangement()));

			board another_table;
			another_table = table;

			Assert::AreEqual(table.get_size(), another_table.get_size());
			Assert::IsTrue(custom_comparison::compare_matrix(table.get_board_arrangement(), another_table.get_board_arrangement()));

			board moved_table(std::move(other_table));

			Assert::IsTrue(table == moved_table);
		}

		TEST_METHOD(is_inside_board)
		{
			board table("aaaa,AAAA,aaaa,AAAA");

			position pos(0, 0);

			Assert::IsTrue(table.is_inside(pos));

			pos.change(1, 1);

			Assert::IsTrue(table.is_inside(pos));

			pos.change(-1, 0);

			Assert::IsFalse(table.is_inside(pos));

			pos.change(0, 2);

			Assert::IsFalse(table.is_inside(pos));
		}

		TEST_METHOD(is_getting_pieces_right)
		{
			board table("aaaa,AAAA,aaaa,AAAA");
			position pos(0, 0);

			auto piece = table.get_piece_from(pos);

			Assert::IsTrue(piece.has_value());

			pos.change(-1, 0);
			piece = table.get_piece_from(pos);

			Assert::IsFalse(piece.has_value());
		}
	};

	TEST_CLASS(SolverTests)
	{
	public:
		TEST_METHOD(check_if_input_is_solution)
		{
			Assert::IsTrue(puzzle_solver::check_if_solution("aaaa,AAAA,AAAA,aaaa"));
		}

		TEST_METHOD(get_correct_amount_of_solutions)
		{
			Assert::AreEqual(49, puzzle_solver::get_amount_of_solutions("cBAA,acaa,AbAb,cabb,BABA,aaac,aBaB,bbaa,AAbb"));
		}
		TEST_METHOD(obtained_correct_solutions)
		{
			auto solution = puzzle_solver::get_all_solutions("aaaa,AAAA,aaaa,AAAA");

			std::set<std::string> sample;

			sample.emplace("aaaa,AAAA,AAAA,aaaa");
			sample.emplace("AAAA,aaaa,aaaa,AAAA");

			Assert::AreEqual(std::size(sample), std::size(solution));
			Assert::IsTrue(std::equal(std::begin(solution), std::end(solution), std::begin(sample), std::end(sample)));
		}
	};
}
