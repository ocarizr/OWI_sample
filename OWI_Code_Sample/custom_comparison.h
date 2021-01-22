#pragma once
class custom_comparison
{
public:
	template <typename T>
	static bool compare_matrix(T source_matrix, T other_matrix) noexcept
	{
		bool result = true;
		for (size_t i = 0; i < std::size(source_matrix) && result; ++i)
		{
			for (size_t j = 0; j < std::size(source_matrix[i]) && result; ++j)
			{
				result = (source_matrix[i][j] == other_matrix[i][j]);
			}
		}

		return result;
	}
};

