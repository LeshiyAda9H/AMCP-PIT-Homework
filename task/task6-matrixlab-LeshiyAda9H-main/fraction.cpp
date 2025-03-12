#include "fraction.h"


Fraction::Fraction() : numerator(ZERO), denominator(ONE){}
Fraction::Fraction(const BigInteger& number) : numerator(number), denominator(ONE){}

Fraction::Fraction(const BigInteger& numeratorForConstructor, const BigInteger& denominatorForConstructor) :
	numerator(numeratorForConstructor), denominator(denominatorForConstructor){}

Fraction::Fraction(const std::string& str) {
	
	unsigned int length = str.length();
	
	int index = 0;
	for (; index < length && str[index] != '/'; ++index){}

	if (index == length) {
		this->numerator = BigInteger(str);
		this->denominator = ONE;
	}
	else {
		this->numerator = BigInteger(str.substr(0, index));
		this->denominator = BigInteger(str.substr(index + 1, length - index - 1));
	}
}

Fraction::Fraction(const Fraction& alien) :
	numerator(alien.numerator), denominator(alien.denominator){}

Fraction::Fraction(Fraction&& alien) noexcept {
	this->swap(alien);
}

Fraction& Fraction::operator= (const Fraction& alien) {
	if (this != &alien) {
		Fraction tmp(alien);
		this->swap(tmp);
	}
	
	return *this;
}

Fraction& Fraction::operator= (Fraction&& alien) noexcept {
	if (this != &alien) {
		this->swap(alien);
	}

	return *this;
}

Fraction& Fraction::operator+= (const Fraction& alien) {

	this->numerator *= alien.denominator;
	this->numerator += alien.numerator * this->denominator;
	this->denominator *= alien.denominator;
	
	return this->simplify();
}

Fraction& Fraction::operator-= (const Fraction& alien) {
	
	this->numerator *= alien.denominator;
	this->numerator -= alien.numerator * this->denominator;
	this->denominator *= alien.denominator;
	
	return this->simplify();
}
Fraction& Fraction::operator*= (const Fraction& alien) {
	
	this->numerator *= alien.numerator;
	this->denominator *= alien.denominator;
	
	return this->simplify();
}
Fraction& Fraction::operator/= (const Fraction& alien) {
	
	if (alien.numerator == ZERO) {
		throw "Oh, no... Don't divide by zero!";
	}
	
	this->numerator *= alien.denominator;
	this->denominator *= alien.numerator;
	this->denominator.upMinus(this->numerator);
	
	return this->simplify();
}

Fraction Fraction::operator- () const {

	Fraction result(*this);
	result.numerator = -result.numerator;
	
	return result;
}

bool Fraction::isLess(const Fraction& alien) const {
	return this->numerator * alien.denominator < alien.numerator* this->denominator;
}

bool Fraction::isEqual(const Fraction& alien) const {
	return this->numerator == alien.numerator && this->denominator == alien.denominator;
}

Fraction::operator std::string() const {

	if (this->denominator == ONE) {
		return to_string(this->numerator);
	}
	
	return to_string(this->numerator) + std::string("/") + to_string(this->denominator);
}


Fraction operator+ (const Fraction& left, const Fraction& right) {

	Fraction result(left);
	result += right;
	
	return result;
}
Fraction operator- (const Fraction& left, const Fraction& right) {
	
	Fraction result(left);
	result -= right;
	
	return result;
}
Fraction operator* (const Fraction& left, const Fraction& right) {
	
	Fraction result(left);
	result *= right;
	
	return result;
}
Fraction operator/ (const Fraction& left, const Fraction& right) {
	
	Fraction result(left);
	result /= right;
	
	return result;
}

bool operator< (const Fraction& left, const Fraction& right) {
	return left.isLess(right);
}

bool operator> (const Fraction& left, const Fraction& right) {
	return right.isLess(left);
}

bool operator<= (const Fraction& left, const Fraction& right) {
	return !right.isLess(left);
}

bool operator>= (const Fraction& left, const Fraction& right) {
	return !left.isLess(right);
}

bool operator== (const Fraction& left, const Fraction& right) {
	return left.isEqual(right);
}

bool operator!= (const Fraction& left, const Fraction& right) {
	return !left.isEqual(right);
}

void Fraction::swap(Fraction& other) {
	std::swap(this->numerator, other.numerator);
	std::swap(this->denominator, other.denominator);
}

Fraction& Fraction::simplify() {

	BigInteger NOD = (this->numerator < ZERO) ? NOD_Evklid(-this->numerator, this->denominator)
		: NOD_Evklid(this->numerator, this->denominator);
	
	if (NOD != ONE) {
		this->numerator /= NOD;
		this->denominator /= NOD;
	}
	
	return *this;
}

BigInteger Fraction::NOD_Evklid(const BigInteger& left, const BigInteger& right) {
	
	if (right == ZERO) { return left; }
	return NOD_Evklid(right, left % right);
}

Fraction::operator BigInteger() const {
	
	if (this->denominator != ONE) {
		throw "Convert is impossible";
	}
	return this->numerator;
}
