#ifndef FRACTION
#define FRACTION

#include "biginteger.h"

class Fraction {
	BigInteger numerator;
	BigInteger denominator;

	void swap(Fraction&);
	Fraction& simplify();

	static BigInteger NOD_Evklid(const BigInteger&, const BigInteger&);
public:
	Fraction();
	Fraction(const BigInteger&);
	Fraction(const std::string&);
	Fraction(const BigInteger&, const BigInteger&);

	Fraction(const Fraction&);
	Fraction(Fraction&&) noexcept;

	Fraction& operator= (const Fraction&);
	Fraction& operator= (Fraction&&) noexcept;

	Fraction& operator+= (const Fraction&);
	Fraction& operator-= (const Fraction&);
	Fraction& operator*= (const Fraction&);
	Fraction& operator/= (const Fraction&);

	Fraction operator- () const;

	bool isLess(const Fraction&) const;
	bool isEqual(const Fraction&) const;

	operator std::string() const;

	operator BigInteger() const;
};

Fraction operator+ (const Fraction&, const Fraction&);
Fraction operator- (const Fraction&, const Fraction&);
Fraction operator* (const Fraction&, const Fraction&);
Fraction operator/ (const Fraction&, const Fraction&);

bool operator< (const Fraction&, const Fraction&);
bool operator> (const Fraction&, const Fraction&);
bool operator<= (const Fraction&, const Fraction&);
bool operator>= (const Fraction&, const Fraction&);
bool operator== (const Fraction&, const Fraction&);
bool operator!= (const Fraction&, const Fraction&);

const Fraction ONE_FRAC(ONE);
const Fraction ZERO_FRAC(ZERO);

#endif