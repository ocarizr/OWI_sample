#pragma once
class position
{
	int m_horizontal;
	int m_vertical;

public:
	position() = default;
	position(int vertical, int horizontal) noexcept : m_horizontal(horizontal), m_vertical(vertical) {}
	position(const position& source) noexcept = default;
	position(position&& source) noexcept = default;

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

	static position get_upper(int& vertical, int& horizontal) noexcept
	{
		position res(vertical - 1, horizontal);
		return res;
	}

	static position get_left(int& vertical, int& horizontal) noexcept
	{
		position res(vertical, horizontal - 1);
		return res;
	}
};

