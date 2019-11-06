#pragma once
#include <cctype>
#include <iostream>
#include <optional>
#include "position.h"

class piece
{
	position m_position;

	char m_left;
	char m_top;
	char m_bottom;
	char m_right;

	bool is_side_connected(char& this_side, char& other_side) noexcept
	{
		if (std::islower(this_side) && std::isupper(other_side) ||
			std::isupper(this_side) && std::islower(other_side))
		{
			return std::tolower(this_side) == std::tolower(other_side);
		}

		return false;
	}

public:
	piece() noexcept = default;
	piece(std::string input, position pos) noexcept : m_position(pos), m_left(input[0]), m_top(input[1]), m_bottom(input[2]), m_right(input[3]) {}
	piece(const piece& source) noexcept : m_position(source.m_position), m_left(source.m_left), m_top(source.m_top), m_bottom(source.m_bottom), m_right(source.m_right) {}
	piece(piece&& source) noexcept : m_position(source.m_position), m_left(source.m_left), m_top(source.m_top), m_bottom(source.m_bottom), m_right(source.m_right) {}

	piece& operator =(const piece& source) noexcept
	{
		m_position = source.m_position;
		m_left = source.m_left;
		m_top = source.m_top;
		m_bottom = source.m_bottom;
		m_right = source.m_right;

		return *this;
	}

	piece& operator =(piece&& source) noexcept
	{
		m_position = std::move(source.m_position);
		m_left = source.m_left;
		m_top = source.m_top;
		m_bottom = source.m_bottom;
		m_right = source.m_right;

		return *this;
	}

	position get_position() const noexcept { return m_position; }
	char get_left() const noexcept { return m_left; }
	char get_top() const noexcept { return m_top; }
	char get_bottom() const noexcept { return m_bottom; }
	char get_right() const noexcept { return m_right; }

	bool check_left_and_top_connections(std::optional<piece>& left, std::optional<piece>& top) noexcept
	{
		auto left_connection = !left.has_value();
		auto top_connection = !top.has_value();

		if (left.has_value())
		{
			left_connection = is_side_connected(m_left, left.value().m_right);
		}

		if (top.has_value())
		{
			top_connection = is_side_connected(m_top, top.value().m_bottom);
		}

		return left_connection && top_connection;
	}

	void rotate() noexcept
	{
		char aux = m_left;
		m_left = m_bottom;
		m_bottom = m_right;
		m_right = m_top;
		m_top = aux;
	}

	std::string to_string() const noexcept
	{
		char buffer[5];
		sprintf_s(buffer, "%c%c%c%c", m_left, m_top, m_bottom, m_right);

		return buffer;
	}

	bool operator ==(const piece& other) const noexcept
	{
		return m_position == other.m_position &&
			m_left == other.m_left &&
			m_top == other.m_top &&
			m_bottom == other.m_bottom &&
			m_right == other.m_right;
	}

	bool operator !=(const piece& other) const noexcept
	{
		return m_position != other.m_position ||
			m_left != other.m_left ||
			m_top != other.m_top ||
			m_bottom != other.m_bottom ||
			m_right != other.m_right;
	}
};

