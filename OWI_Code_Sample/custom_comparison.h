#pragma once
class custom_comparison
{
public:
	template <typename T>
	static bool compare_matrix(T source_matrix, T other_matrix)
	{
		try
		{
			for (size_t i = 0; i < std::size(source_matrix); ++i)
			{
				for (size_t j = 0; j < std::size(source_matrix[i]); ++j)
				{
					if (source_matrix[i][j] != other_matrix[i][j])
					{
						throw false;
					}
				}
			}

			return true;
		}
		catch (bool error)
		{
			return error;
		}
	}
};

