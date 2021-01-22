#pragma once
#include <sstream>
#include "piece.h"
#include "position.h"
#include "custom_comparison.h"

using matrix = std::vector<std::vector<piece>>;

class board
{
	int m_size;
	matrix m_board_arrangement;

public:
	board() noexcept = default;
	explicit board(std::string input) noexcept : m_size(0), m_board_arrangement()
	{
		std::vector<std::string> pieces_input;
		char* token = strtok(input.data(), ",");

		while (token != nullptr)
		{
			pieces_input.push_back(token);
			token = strtok(nullptr, ",");
		}

		auto amount_of_pieces = std::size(pieces_input);
		m_size = static_cast<int>(sqrt(amount_of_pieces));

		m_board_arrangement.resize(m_size);

		for (int i = 0; i < amount_of_pieces; ++i)
		{
			int vertical = i / m_size;

			piece pc(pieces_input[i]);
			m_board_arrangement[vertical].push_back(pc);
		}
	}

	explicit board(std::vector<piece>& pieces) noexcept : m_size(0), m_board_arrangement()
	{
		int amount_of_pieces = std::size(pieces);
		m_size = sqrt(std::size(pieces));
		m_board_arrangement.resize(m_size);

		for (size_t i = 0; i < amount_of_pieces; ++i)
		{
			int vertical = i / m_size;
			m_board_arrangement[vertical].push_back(pieces[i]);
		}
	}

	board(const board& source) noexcept : m_size(source.m_size), m_board_arrangement(source.m_board_arrangement) {}
	board(board&& source) noexcept : m_size(source.m_size), m_board_arrangement(source.m_board_arrangement) {}

	board& operator =(const board& source) noexcept
	{
		m_size = source.m_size;
		m_board_arrangement.clear();
		m_board_arrangement = source.m_board_arrangement;

		return *this;
	}

	board& operator =(board&& source) noexcept
	{
		m_size = source.m_size;
		m_board_arrangement.clear();
		m_board_arrangement = source.m_board_arrangement;

		return *this;
	}

	int get_size() const noexcept { return m_size; }
	matrix get_board_arrangement() const noexcept { return m_board_arrangement; }

	bool is_inside(const position& pos) const noexcept
	{
		return (pos.get_horizontal() >= 0 && pos.get_horizontal() < m_size) && (pos.get_vertical() >= 0 && pos.get_vertical() < m_size);
	}

	std::optional<piece> get_piece_from(position& pos) noexcept
	{
		std::optional<piece> result;
		if (is_inside(pos))
		{
			result.emplace(m_board_arrangement[pos.get_vertical()][pos.get_horizontal()]);
			return result;
		}

		return {};
	}

	std::string to_string() const noexcept
	{
		std::stringstream ss;

		for (size_t i = 0; i < m_size; ++i)
		{
			for (size_t j = 0; j < m_size; ++j)
			{
				if (i != 0 || j != 0)
				{
					ss << ',';
				}
				ss << m_board_arrangement[i][j].to_string();				
			}
		}

		return ss.str();
	}

	bool operator ==(const board& other) const noexcept
	{
		return m_size == other.m_size && custom_comparison::compare_matrix(m_board_arrangement, other.m_board_arrangement);
	}
};

