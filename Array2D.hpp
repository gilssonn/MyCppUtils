#ifndef ARRAY2D_HPP
#define ARRAY2D_HPP

#include <cstddef>
#include <expected>
#include <iostream>
#include <sstream>
#include <vector>

namespace MyCppUtils
{
	/**
	 * @brief Error codes for the reshape function
	 *
	 */
	enum class Unreshapable
	{
		BigDimensions,
		SmallDimensions
	};

	/**
	 * @brief Flattened 2D Array
	 *
	 * @tparam T
	 */
	template <typename T>
	class Array2D
	{
		template <typename U>
		friend std::expected<MyCppUtils::Array2D<U>, Unreshapable> reshape(const MyCppUtils::Array2D<U>&, std::size_t, std::size_t);

	  public:
		Array2D(std::size_t rows, std::size_t cols)
		: data(rows * cols),
		  rows{rows},
		  cols{cols}
		{
		}

		T& operator[](std::size_t row, std::size_t col)
		{
			return this->data.at(row * cols + col); // at() does array bounds checking
		}

		const T& operator[](std::size_t row, std::size_t col) const
		{
			return this->data.at(row * cols + col); // at() does array bounds checking
		}

		std::size_t get_rows() const
		{
			return this->rows;
		}

		std::size_t get_cols() const
		{
			return this->cols;
		}

	  private:
		std::vector<T> data;
		std::size_t rows;
		std::size_t cols;

		const std::vector<T>& get_data() const
		{
			return this->data;
		}

		/**
		 * @brief Construct a new Array2D object. Constructor is encapsulated by `reshape` friend function.
		 *
		 * @param arr
		 * @param rows
		 * @param cols
		 */
		Array2D(const MyCppUtils::Array2D<T>& arr, std::size_t rows, std::size_t cols)
		: data{arr.get_data()},
		  rows{rows},
		  cols{cols}
		{
		}
	};

	/**
	 * @brief Reshape an m x n 2D Array into a new array with different dimensions r x c keeping its original data
	 *
	 * Signature: auto newArray = MyCppUtils::reshape<ArrayType>(originalArray, newRowNumber, newColumnNumber);
	 *
	 * @tparam U
	 * @param originalArr
	 * @param rows
	 * @param cols
	 * @return std::expected<MyCppUtils::Array2D<U>, Unreshapable>
	 */
	template <typename U>
	std::expected<MyCppUtils::Array2D<U>, Unreshapable> reshape(const MyCppUtils::Array2D<U>& originalArr, std::size_t rows, std::size_t cols)
	{
		// Check if `originalArr` can be reshaped
		if ((rows * cols) > (originalArr.get_cols() * originalArr.get_rows()))
		{
			std::cerr << "The provided dimensions are too big, the array is unreshapable.\n";
			return std::unexpected(Unreshapable::BigDimensions);
		}

		if ((rows * cols) < (originalArr.get_cols() * originalArr.get_rows()))
		{
			std::cerr << "The provided dimensions are too small, the array is unreshapable.\n";
			return std::unexpected(Unreshapable::SmallDimensions);
		}

		// Initialize a new array with new values for `rows` and `cols` and copy `data` from the original array to the new array
		MyCppUtils::Array2D<U> newArr{originalArr, rows, cols};

		// Return the new array
		return newArr;
	}

	/**
	 * @brief Print a 2D Grid representing the array. For debugging purposes only.
	 *
	 * Assumption: T is a type that can be inserted into an output stream
	 *
	 * @tparam T
	 * @param os
	 * @param arr
	 * @return std::ostream&
	 */
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const MyCppUtils::Array2D<T>& arr)
	{
		for (std::size_t i = 0; i < arr.get_rows(); ++i)
		{
			for (std::size_t j = 0; j < arr.get_cols(); ++j)
			{
				os << arr[i, j] << ' ';
			}
			os << '\n';
		}

		return os;
	}

	/**
	 * @brief Another 2D Grid printer for debugging purposes only.
	 *
	 * Assumption: T is a type that can be inserted into an output stream
	 *
	 * @tparam T
	 * @param os
	 * @param arr
	 * @return std::ostream&
	 */
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const std::expected<MyCppUtils::Array2D<T>, Unreshapable>& arr)
	{
		if (arr)
		{
			for (std::size_t i = 0; i < arr.value().get_rows(); ++i)
			{
				for (std::size_t j = 0; j < arr.value().get_cols(); ++j)
				{
					os << arr.value()[i, j] << ' ';
				}
				os << '\n';
			}
		}
		else
		{
			os << "You are trying to print an error.\n";
		}

		return os;
	}
} // namespace MyCppUtils

#endif // ARRAY2D_HPP