#ifndef ARRAY2D_HPP
#define ARRAY2D_HPP

#include <vector>
#include <stdexcept>

namespace MyCppUtils
{
	template <typename T>
	class Array2D
	{
	public:
		Array2D(int rows, int cols) : data(rows * cols), nrows{rows}, ncols{cols} {}

		T &operator[](int row, int col)
		{
			return data.at(row * ncols + col); // at() does array bounds checking
		}

		const T &operator[](int row, int col) const
		{
			return data.at(row * ncols + col); // at() does array bounds checking
		}

		int rows() const
		{
			return nrows;
		}

		int cols() const
		{
			return ncols;
		}

	private:
		std::vector<T> data;
		int nrows;
		int ncols;
	};
}

#endif // ARRAY2D_HPP