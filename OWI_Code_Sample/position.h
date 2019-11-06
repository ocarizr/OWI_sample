#pragma once
class position
{
	int m_horizontal;
	int m_vertical;

public:
	position() = default;
	position(int vertical, int horizontal) noexcept : m_horizontal(horizontal), m_vertical(vertical) {}
	position(const position& source) = default;
	position(position&& source) = default;

	position& operator =(const position& source) noexcept
	{
		m_horizontal = source.m_horizontal;
		m_vertical = source.m_vertical;

		return *this;
	}

	position& operator =(position&& source) noexcept
	{
		m_horizontal = source.m_horizontal;
		m_vertical = source.m_vertical;

		return *this;
	}

	int get_horizontal() const noexcept { return m_horizontal; }
	int get_vertical() const noexcept { return m_vertical; }

	void change(int vertical, int horizontal) noexcept
	{
		m_horizontal = horizontal;
		m_vertical = vertical;
	}

	bool operator ==(const position& other) const noexcept
	{
		return m_horizontal == other.m_horizontal && m_vertical == other.m_vertical;
	}

	bool operator !=(const position& other) const noexcept
	{
		return m_horizontal != other.m_horizontal || m_vertical != other.m_vertical;
	}

	static position get_upper(const position& pos) noexcept
	{
		position res(pos.m_vertical - 1, pos.m_horizontal);
		return res;
	}

	static position get_left(const position& pos) noexcept
	{
		position res(pos.m_vertical, pos.m_horizontal - 1);
		return res;
	}
};

