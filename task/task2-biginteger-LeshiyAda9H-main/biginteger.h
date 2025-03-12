#ifndef BIGINT
#define BIGINT

#include <iostream>
#include <string>


class BigInteger{
private:
	unsigned int* digit = nullptr;
	int counter;
	int capacity;
	char sign;

	void swap(BigInteger& initial) {
		std::swap(digit, initial.digit);
		std::swap(counter, initial.counter);
		std::swap(capacity, initial.capacity);
		std::swap(sign, initial.sign);
	}

	static const unsigned long long DEGREEBIGINTEGER = 1ULL << 32;
public:
	BigInteger() : counter(1), capacity(1), sign(0) {
		digit = new unsigned int[capacity];
		digit[0] = 0;
	};
	~BigInteger() { delete[] digit; }

	BigInteger(int number) : counter(1), capacity(1) {
		if (number < 0) {
			sign = -1;
		}
		else if (number > 0) {
			sign = 1;
		}
		else{
			sign = 0;
		}
		digit = new unsigned int[capacity];
		digit[0] = number * sign;

	}

	BigInteger(unsigned int number) : counter(1), capacity(1) {
		if (number == 0) {
			sign = 0;
		}
		else {
			sign = 1;
		}
		digit = new unsigned int[capacity];
		digit[0] = number;
	}

	BigInteger(long number) : counter(1), capacity(2) {
		if (number < 0) {
			sign = -1;
		}
		else if (number > 0) {
			sign = 1;
		}
		else {
			sign = 0;
		}
		number *= sign;

		digit = new unsigned int[capacity];
		digit[0] = number;

		number /= DEGREEBIGINTEGER;

		digit[1] = number;
		if (number != 0) { ++counter; }
	}
	BigInteger(unsigned long number) : counter(1), capacity(2) {
		if (number == 0) {
			sign = 0;
		}
		else {
			sign = 1;
		}

		digit = new unsigned int[capacity];
		digit[0] = number;

		number /= DEGREEBIGINTEGER;

		digit[1] = number;
		if (number != 0) { ++counter; }
	}

	BigInteger(long long number) : counter(1), capacity(2) {
		if (number < 0) {
			sign = -1;
		}
		else if (number > 0) {
			sign = 1;
		}
		else {
			sign = 0;
		}
		number *= sign;

		digit = new unsigned int[capacity];
		digit[0] = number;

		number /= DEGREEBIGINTEGER;

		digit[1] = number;
		if (number != 0) { ++counter; }
	}

	BigInteger(unsigned long long number) : counter(1), capacity(2) {
		if (number == 0) {
			sign = 0;
		}
		else {
			sign = 1;
		}

		digit = new unsigned int[capacity];
		digit[0] = number;

		number /= DEGREEBIGINTEGER;

		digit[1] = number;
		if (number != 0) { ++counter; }
	}

	BigInteger(std::string);
	BigInteger(const BigInteger&);
	BigInteger(BigInteger&&) noexcept;

	BigInteger& operator= (const BigInteger&);
	BigInteger& operator= (BigInteger&&) noexcept;

	bool below(const BigInteger&) const;
	bool same(const BigInteger&) const;

	BigInteger operator- () const {
		BigInteger copy = *this;
		copy.sign *= -1;
		return copy;
	}
	BigInteger operator+ () const {
		BigInteger copy = *this;
		return copy;
	}

	BigInteger& operator+= (const BigInteger&);
	BigInteger& operator-= (const BigInteger&);
	BigInteger& operator*= (const BigInteger&);
	BigInteger& operator/= (const BigInteger&);
	BigInteger& operator%= (const BigInteger&);


	BigInteger abs() const {
		BigInteger copy(*this);
		if (copy.sign == -1) { copy.sign = 1; }
		return copy;
	}

	void pruning() {
		while(counter > 1 && digit[counter - 1] == 0){
			--counter;
		}
	}

	BigInteger& operator++() {
		*this += 1;
		return *this;
	}
	BigInteger operator++(int) {
		BigInteger copy(*this);
		*this += 1;
		return copy;
	}
	BigInteger& operator--() {
		*this -= 1;
		return *this;
	}
	BigInteger operator--(int) {
		BigInteger copy(*this);
		*this -= 1;
		return copy;
	}

	std::string str() const;
};


bool operator< (const BigInteger&, const BigInteger&);
bool operator<= (const BigInteger& , const BigInteger&);
bool operator> (const BigInteger&, const BigInteger&);
bool operator>= (const BigInteger&, const BigInteger&);
bool operator== (const BigInteger&, const BigInteger&);
bool operator!= (const BigInteger&, const BigInteger&);

BigInteger operator+ (const BigInteger&, const BigInteger&);
BigInteger operator- (const BigInteger&, const BigInteger&);
BigInteger operator* (const BigInteger&, const BigInteger&);
BigInteger operator/ (const BigInteger&, const BigInteger&);
BigInteger operator% (const BigInteger&, const BigInteger&);

std::string to_string(const BigInteger&);


#endif