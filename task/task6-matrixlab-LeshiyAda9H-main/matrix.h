#ifndef MATRIX
#define MATRIX

#include "fraction.h"
#include <iostream>

class Matrix {

	Fraction** data = nullptr;
	int rows;
	int cols;

	void swap(Matrix&);
	void Gauss();
	unsigned int* MaxLenCol() const;

public:
	Matrix();
	Matrix(unsigned int, unsigned int);
	Matrix(const Matrix&);
	Matrix(const Fraction&);
	Matrix(Matrix&&) noexcept;
	Matrix(unsigned int, unsigned int, const Fraction&);


	Matrix& operator= (const Matrix&);
	Matrix& operator= (Matrix&&) noexcept;


	Matrix& onesOnDiagonal();
	Matrix& addition(const Matrix&);
	Matrix& subtraction(const Matrix&);
	Matrix& elementByElementMultiplication(const Matrix&);
	Matrix& elementByElementDivision(const Matrix&);
	Matrix& matrixMultiplication(const Matrix&);
	Matrix& matrixDivision(const Matrix&);
	Matrix& linspace(const Fraction&, const Fraction&);
	
	
	Fraction determinant() const;
	Fraction sum() const;
	Fraction prod() const;
	Matrix inverse() const;
	Matrix transpose() const;
	Matrix min(const Matrix&) const;
	Matrix max(const Matrix&) const;
	Matrix negative() const;
	Matrix diag() const;

	
	Matrix& horzcat(const Matrix&);
	Matrix& vertcat(const Matrix&);

	
	std::ostream& disp(std::ostream&) const;

	
	bool isScalar() const;
	operator Fraction() const;
	operator unsigned int() const;
	
	~Matrix() {
		if (data != nullptr) {
			for (int row = 0; row < rows; ++row) {
				delete[] data[row];
			}

			delete[] data;
		}
	}
};

Matrix addition(const Matrix&, const Matrix&);
Matrix subtraction(const Matrix&, const Matrix&);
Matrix elementByElementMultiplication(const Matrix&, const Matrix&);
Matrix elementByElementDivision(const Matrix&, const Matrix&);
Matrix matrixMultiplication(const Matrix&, const Matrix&);
Matrix matrixDivision(const Matrix&, const Matrix&);
Matrix min(const Matrix&, const Matrix&);
Matrix max(const Matrix&, const Matrix&);


Matrix ones(unsigned int, unsigned int);
Matrix eye(unsigned int, unsigned int);
Matrix zeros(unsigned int, unsigned int);


Matrix linspace(const Fraction&, const Fraction&, unsigned int);


Matrix transpose(const Matrix&);
Matrix det(const Matrix&);
Matrix inverse(const Matrix&);
Matrix negative(const Matrix&);
Matrix sum(const Matrix&);
Matrix prod(const Matrix&);
Matrix diag(const Matrix&);


Matrix& vertcat(Matrix&, const Matrix&);
Matrix& horzcat(Matrix&, const Matrix&);


std::ostream& operator<< (std::ostream&, const Matrix&);

#endif
