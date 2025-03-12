#include "matrix.h"


Matrix::Matrix() : rows(0), cols(0), data(nullptr){}

Matrix::Matrix(unsigned int rows, unsigned int columns) : rows(static_cast<int>(rows)), cols(static_cast<int>(columns)) {
	
	data = new Fraction * [rows];
	
	for (int row = 0; row < rows; ++row) {
		data[row] = new Fraction[columns];
	}
}
Matrix::Matrix(unsigned int rows, unsigned int columns, const Fraction& filler) : rows(static_cast<int>(rows)), cols(static_cast<int>(columns)) {
	
	data = new Fraction * [rows];
	
	for (int row = 0; row < rows; ++row) {
		data[row] = new Fraction[columns];
		
		for (int col = 0; col < columns; ++col) {
			data[row][col] = filler;
		}
	}
}
Matrix::Matrix(const Fraction& frac) : rows(1), cols(1) {
	this->data = new Fraction * [rows];
	this->data[0] = new Fraction[cols];
	this->data[0][0] = frac;
}

Matrix::Matrix(const Matrix& alien) : rows(alien.rows), cols(alien.cols) {
	
	this->data = new Fraction * [this->rows];
	
	for (int row = 0; row < this->rows; ++row) {
		this->data[row] = new Fraction[this->cols];
	}

	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {

			this->data[row][col] = alien.data[row][col];
		}
	}
}
Matrix::Matrix(Matrix&& alien) noexcept {
	this->swap(alien);
}

Matrix& Matrix::operator= (const Matrix& alien) {
	if (this != &alien) {
		Matrix tmp(alien);
		this->swap(tmp);
	}
	
	return *this;
}
Matrix& Matrix::operator= (Matrix&& alien) noexcept {
	if (this != &alien) {
		this->swap(alien);
	}

	return *this;
}

Matrix& Matrix::onesOnDiagonal() {

	for (int index = 0; index < this->rows; ++index) {

		this->data[index][index] = ONE_FRAC;
	}

	return *this;
}
Matrix& Matrix::addition(const Matrix& alien) {

	if (this->rows != alien.rows || this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}

	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			this->data[row][col] += alien.data[row][col];
		}
	}

	return *this;
}
Matrix& Matrix::subtraction(const Matrix& alien) {

	if (this->rows != alien.rows || this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}
	
	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			this->data[row][col] -= alien.data[row][col];
		}
	}
	
	return *this;
}
Matrix& Matrix::elementByElementMultiplication(const Matrix& alien) {
	
	if (this->rows != alien.rows || this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}
	
	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			this->data[row][col] *= alien.data[row][col];
		}
	}
	
	return *this;
}
Matrix& Matrix::elementByElementDivision(const Matrix& alien) {
	
	if (this->rows != alien.rows || this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}
	
	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			this->data[row][col] /= alien.data[row][col];
		}
	}
	
	return *this;
}
Matrix& Matrix::matrixMultiplication(const Matrix& alien) {
	
	if (this->cols != alien.rows && !this->isScalar() && !alien.isScalar()) {
		throw "Unsuitable matrix sizes";
	}

	if (this->isScalar()) {
		
		Matrix result(alien);
		
		for (int row = 0; row < result.rows; ++row) {
			for (int col = 0; col < result.cols; ++col) {
				result.data[row][col] *= this->data[0][0];
			}
		}
		this->swap(result);
		
		return *this;
	}

	if (alien.isScalar()) {
		
		for (int row = 0; row < this->rows; ++row) {
			for (int col = 0; col < this->cols; ++col) {
				
				this->data[row][col] *= alien.data[0][0];
			}
		}
		
		return *this;
	}

	Matrix result(this->rows, alien.cols);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < result.cols; ++col) {
			for (int cur = 0; cur < this->cols; ++cur) {
				
				result.data[row][col] += this->data[row][cur] * alien.data[cur][col];
			}
		}
	}
	this->swap(result);
	
	return *this;
}
Matrix& Matrix::matrixDivision(const Matrix& alien) {
	
	if (this->cols != alien.rows) {
		throw "Unsuitable matrix sizes";
	}
	
	return this->matrixMultiplication(alien.inverse());
}
Matrix& Matrix::linspace(const Fraction& x0, const Fraction& x1) {
	
	if (this->rows != 1) {
		throw "Unsuitable matrix sizes";
	}
	
	Fraction step((x1 - x0) / Fraction(this->cols - 1));
	
	this->data[0][0] = x0;
	
	for (int col = 1; col < this->cols; ++col) {
		
		this->data[0][col] = this->data[0][col - 1] + step;
	}
	
	return *this;
}

Fraction Matrix::determinant() const {
	
	if (this->rows != this->cols) {
		throw "Unsuitable matrix sizes";
	}
	
	Matrix copy(*this);
	copy.Gauss();
	
	Fraction Det(ONE);
	
	for (int index = 0; index < this->rows; ++index) {
		Det *= copy.data[index][index];
	}
	
	return Det;
}
Fraction Matrix::sum() const {
	
	Fraction sum(ZERO_FRAC);
	
	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			sum += this->data[row][col];
		}
	}
	
	return sum;
}
Fraction Matrix::prod() const {
	
	Fraction prod(ONE_FRAC);
	
	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			prod *= this->data[row][col];
		}
	}
	
	return prod;
}

Matrix Matrix::inverse() const {
	
	if (this->determinant() == ZERO_FRAC) {
		throw "The determinant is zero";
	}
	
	Matrix copy(*this);
	copy.horzcat(eye(copy.rows, copy.cols));
	copy.Gauss();
	
	for (int row = 0; row < copy.rows; ++row) {
		for (int col = this->cols; col < copy.cols; ++col) {
			
			copy.data[row][col] /= copy.data[row][row];
		}
	}
	
	Matrix result(this->rows, this->cols);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < result.cols; ++col) {
			
			result.data[row][col] = copy.data[row][col + this->cols];
		}
	}

	return result;
}
Matrix Matrix::transpose() const {
	
	Matrix result(this->cols, this->rows);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < result.cols; ++col) {
			
			result.data[row][col] = this->data[col][row];
		}
	}
	
	return result;
}
Matrix Matrix::min(const Matrix& alien) const {
	
	if (this->rows != alien.rows || this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}
	
	Matrix result(this->rows, this->cols);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < result.cols; ++col) {
			
			result.data[row][col] = (this->data[row][col] < alien.data[row][col]) ? this->data[row][col] : alien.data[row][col];
		}
	}
	
	return result;
}
Matrix Matrix::max(const Matrix& alien) const {
	
	if (this->rows != alien.rows || this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}
	
	Matrix result(this->rows, this->cols);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < result.cols; ++col) {
			
			result.data[row][col] = (this->data[row][col] > alien.data[row][col]) ? this->data[row][col] : alien.data[row][col];
		}
	}
	
	return result;
}
Matrix Matrix::negative() const {
	
	Matrix result(this->rows, this->cols);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < result.cols; ++col) {
			
			result.data[row][col] = -this->data[row][col];
		}
	}
	
	return result;
}


Matrix& Matrix::horzcat(const Matrix& alien) {
	
	if (this->rows != alien.rows) {
		throw "Unsuitable matrix sizes";
	}
	
	Matrix result(this->rows, this->cols + alien.cols);
	
	for (int row = 0; row < result.rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			result.data[row][col] = this->data[row][col];
		}
		
		for (int col = this->cols; col < result.cols; ++col) {
			
			result.data[row][col] = alien.data[row][col - this->cols];
		}
	}
	this->swap(result);
	
	return *this;
}
Matrix& Matrix::vertcat(const Matrix& alien) {
	
	if (this->cols != alien.cols) {
		throw "Unsuitable matrix sizes";
	}
	
	Matrix result(this->rows + alien.rows, this->cols);
	
	for (int col = 0; col < result.cols; ++col) {
		for (int row = 0; row < this->rows; ++row) {
			
			result.data[row][col] = this->data[row][col];
		}
		for (int row = this->rows; row < result.rows; ++row) {
			
			result.data[row][col] = alien.data[row - this->rows][col];
		}
	}
	this->swap(result);
	
	return *this;
}

std::ostream& Matrix::disp(std::ostream& out) const {
	
	if (this->rows == 1 && this->cols == 1) {
		out << (std::string)this->data[0][0];
		
		return out;
	}

	unsigned int* arrayLengths = this->MaxLenCol();

	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			std::string fraction = (std::string)this->data[row][col];
			unsigned int length = fraction.length();

			for (unsigned int space = length; space < arrayLengths[col]; ++space) {
				out.put(' ');
			}
			out << fraction;
			
			if (col != this->cols - 1) {
				out.put(' ');
			}
		}
		if (row != this->rows - 1) {
			out << std::endl;
		}
	}

	delete[] arrayLengths;
	return out;
}

void Matrix::swap(Matrix& alien) {
	std::swap(this->rows, alien.rows);
	std::swap(this->cols, alien.cols);
	std::swap(this->data, alien.data);
}

void Matrix::Gauss() {
	for (int index = 0; index < this->rows && index < this->cols; ++index) {
		if (this->data[index][index] == ZERO_FRAC) {
			
			for (int jndex = 0; jndex < this->rows && jndex < this->cols; ++jndex) {
				if (this->data[jndex][index] != ZERO_FRAC) {
					
					std::swap(this->data[index], this->data[jndex]);
					break;
				}
			}
		}
		if (this->data[index][index] != ZERO_FRAC) {
			for (int jndex = 0; jndex < this->rows && jndex < this->cols; ++jndex) {
				
				if (jndex != index) {
					Fraction coefficient = this->data[jndex][index] / this->data[index][index];
					
					for (int kndex = index; kndex < this->cols; ++kndex) {
						this->data[jndex][kndex] -= coefficient * this->data[index][kndex];
					}
				}
			}
		}
	}
}
unsigned int* Matrix::MaxLenCol() const {
	
	unsigned int* arrLen = new unsigned int[this->cols]{0};
	
	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->cols; ++col) {
			
			unsigned int length = ((std::string)this->data[row][col]).length();
			
			if (arrLen[col] < length) {
				arrLen[col] = length;
			}
		}
	}
	
	return arrLen;
}

bool Matrix::isScalar() const { 
	return this->rows == 1 && this->cols == 1;
}

Matrix::operator Fraction() const {
	
	if (this->rows != 1 || this->cols != 1) {
		throw "Convert is impossible";
	}
	
	return this->data[0][0];
}

Matrix::operator unsigned int() const {
	return ((this->operator Fraction()).operator BigInteger()).operator unsigned int();
}

Matrix addition(const Matrix& left, const Matrix& right) {
	
	Matrix result(left);
	result.addition(right);
	
	return result;
}

Matrix subtraction(const Matrix& left, const Matrix& right) {
	
	Matrix result(left);
	result.subtraction(right);
	
	return result;
}

Matrix elementByElementMultiplication(const Matrix& left, const Matrix& right) {
	
	Matrix result(left);
	result.elementByElementMultiplication(right);
	
	return result;
}

Matrix elementByElementDivision(const Matrix& left, const Matrix& right) {
	
	Matrix result(left);
	result.elementByElementDivision(right);
	
	return result;
}

Matrix matrixMultiplication(const Matrix& left, const Matrix& right) {
	
	Matrix result(left);
	result.matrixMultiplication(right);
	
	return result;
}

Matrix matrixDivision(const Matrix& left, const Matrix& right) {
	
	Matrix result(left);
	result.matrixDivision(right);
	
	return result;
}

Matrix ones(unsigned int rows, unsigned int columns) { 
	return Matrix(rows, columns, ONE_FRAC);
}

Matrix eye(unsigned int rows, unsigned int columns) {
	
	Matrix result(rows, columns);
	result.onesOnDiagonal();
	
	return result;
}

Matrix zeros(unsigned int rows, unsigned int columns) { 
	return Matrix(rows, columns);
}

Matrix linspace(const Fraction& x0, const Fraction& x1, unsigned int columns) {
	
	Matrix result(1, columns);
	result.linspace(x0, x1);
	
	return result;
}

Matrix Matrix::diag() const {
	
	Matrix result(1, (this->rows < this->cols) ? this->rows : this->cols);

	for (int elem = 0; elem < this->cols && elem < this->rows; ++elem) {
		result.data[0][elem] = this->data[elem][elem];
	}
	
	return result;
}

Matrix transpose(const Matrix& matrix) {
	return matrix.transpose();
}

Matrix det(const Matrix& matrix) {
	return Matrix(matrix.determinant());
}

Matrix inverse(const Matrix& matrix) { 
	return matrix.inverse();
}

Matrix min(const Matrix& left, const Matrix& right) { 
	return left.min(right); 
}

Matrix max(const Matrix& left, const Matrix& right) { 
	return left.max(right);
}

Matrix negative(const Matrix& matrix) { 
	return matrix.negative();
}

Matrix sum(const Matrix& matrix) { 
	return matrix.sum();
}

Matrix prod(const Matrix& matrix) { 
	return matrix.prod();
}

Matrix diag(const Matrix& matrix) {
	return matrix.diag();
}

Matrix& vertcat(Matrix& left, const Matrix& right) {
	return left.vertcat(right);
}

Matrix& horzcat(Matrix& left, const Matrix& right) {
	return left.horzcat(right);
}

std::ostream& operator<< (std::ostream& out, const Matrix& matrix) { 
	return matrix.disp(out);
}
