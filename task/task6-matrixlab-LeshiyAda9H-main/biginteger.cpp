#include "biginteger.h"

bool remainder(std::string& str);


BigInteger::BigInteger(std::string str) : counter(0), capacity(1) {
	
	if (str.length() == 0) { throw std::invalid_argument(str); }

	if (str[0] == '-') {
		sign = -1;
		str.erase(0, 1);
	}
	else { sign = 1; }

	if (str == "0") { sign = 0; }

	if (str.length() == 0) { throw std::invalid_argument(str); }

	digit = new unsigned int[capacity] {0};

	int bit = 0;
	while (true) {
		if (counter == capacity) {
			capacity *= 2;
			unsigned int* tmp = new unsigned int[capacity];
			for (int index = 0; index < counter; ++index) {
				tmp[index] = digit[index];
			}
			for (int index = counter; index < capacity; ++index) {
				tmp[index] = 0;
			}
			delete[] digit;
			digit = tmp;
		}

		
		digit[counter] += (1 << bit) * (static_cast<unsigned int>(str[str.length() - 1]) % 2);
		++bit;

		try {
			if (remainder(str)) { break; }
		}
		catch (...) {
			delete[] digit;
			throw;
		}

		if (bit == 32) {
			bit = 0;
			++counter;
		}
	}
	++counter;
}

bool remainder(std::string& str) {
	char left = 0;
	bool stringIsZeros = true;
	for (int right = 0; right < str.length(); ++right) {
		if (left % 2 == 0) {
			switch (str[right]) {
			case '0':
			case '1':
				left = str[right];
				str[right] = '0';
				break;
			case '2':
			case '3':
				left = str[right];
				str[right] = '1';
				stringIsZeros = false;
				break;
			case '4':
			case '5':
				left = str[right];
				str[right] = '2';
				stringIsZeros = false;
				break;
			case '6':
			case '7':
				left = str[right];
				str[right] = '3';
				stringIsZeros = false;
				break;
			case '8':
			case '9':
				left = str[right];
				str[right] = '4';
				stringIsZeros = false;
				break;
			default:
				throw std::invalid_argument(str);
			}
		}
		else {
			switch (str[right]) {
			case '0':
			case '1':
				left = str[right];
				str[right] = '5';
				stringIsZeros = false;
				break;
			case '2':
			case '3':
				left = str[right];
				str[right] = '6';
				stringIsZeros = false;
				break;
			case '4':
			case '5':
				left = str[right];
				str[right] = '7';
				stringIsZeros = false;
				break;
			case '6':
			case '7':
				left = str[right];
				str[right] = '8';
				stringIsZeros = false;
				break;
			case '8':
			case '9':
				left = str[right];
				str[right] = '9';
				stringIsZeros = false;
				break;
			default:
				throw std::invalid_argument(str);
			}
		}
	}
	return stringIsZeros;
}

BigInteger::BigInteger(const BigInteger& copyrighted) : sign(copyrighted.sign), counter(copyrighted.counter), capacity(copyrighted.capacity) {
	digit = new unsigned int[capacity];

	for (int index = 0; index < capacity; ++index) {
		digit[index] = copyrighted.digit[index];
	}
}
BigInteger::BigInteger(BigInteger&& robbed) noexcept {
	swap(robbed);
}


BigInteger& BigInteger::operator= (const BigInteger& copyrighted) {
	if (this != &copyrighted) {
		BigInteger tmp(copyrighted);
		swap(tmp);
	}
	return *this;
}
BigInteger& BigInteger::operator= (BigInteger&& robbed) noexcept {
	if (this != &robbed) {
		swap(robbed);
	}
	return *this;
}

bool BigInteger::below(const BigInteger& compared) const {
	if (sign != compared.sign) {
		return sign < compared.sign;
	}
	if (counter != compared.counter) {
		return (sign < 0 && counter > compared.counter) || (sign > 0 && counter < compared.counter);
	}

	for (int index = counter - 1; index >= 0; --index) {
		if (digit[index] != compared.digit[index]) { 
			return (sign < 0 && digit[index] > compared.digit[index]) || (sign > 0 && digit[index] < compared.digit[index]);
		}
	}
	return false;
}

bool BigInteger::same(const BigInteger& compared) const {
	if (sign != compared.sign) { return false; }
	if (counter != compared.counter) { return false; }

	for (int index = 0; index < counter; ++index) {
		if (digit[index] != compared.digit[index]) { return false; }
	}
	return true;
}


bool operator< (const BigInteger& left, const BigInteger& right) {
	return left.below(right);
}
bool operator<= (const BigInteger& left, const BigInteger& right) {
	return !right.below(left);
}
bool operator> (const BigInteger& left, const BigInteger& right) {
	return right.below(left);
}
bool operator>= (const BigInteger& left, const BigInteger& right) {
	return !left.below(right);
}
bool operator== (const BigInteger& left, const BigInteger& right) {
	return left.same(right);
}
bool operator!= (const BigInteger& left, const BigInteger& right) {
	return !left.same(right);
}

BigInteger& BigInteger::operator+= (const BigInteger& alien) {

	if (*this == ZERO) {
		*this = alien;
		return *this;
	}
	if (alien == ZERO) {
		return *this;
	}
	if (this->sign != alien.sign && this->abs() == alien.abs()) {
		*this = ZERO;
		return *this;
	}

	int seniorCapacity = 0;
	if (alien.counter < this->counter) {
		seniorCapacity = this->counter + 1;
	}
	else{
		seniorCapacity = alien.counter + 1;
	}
	
	BigInteger answer;
	answer.capacity = seniorCapacity;
	answer.counter = seniorCapacity;
	delete[] answer.digit;

	answer.digit = new unsigned int[seniorCapacity] {0};

	unsigned int inMind = 0;

	if (this->sign == alien.sign) {
		answer.sign = alien.sign;
		for (int index = 0; index < seniorCapacity; ++index) {
			unsigned long long sum = inMind;
			if (index < this->counter) {
				sum += this->digit[index];
			}
			if (index < alien.counter) {
				sum += alien.digit[index];
			}
			answer.digit[index] = sum % DEGREEBIGINTEGER;
			inMind = sum / DEGREEBIGINTEGER;
		}
	}
	else{
		if (this->abs() < alien.abs()) {
			answer.sign = alien.sign;

			for (int index = 0; index < alien.counter; ++index) {
				long long dif = alien.digit[index];
				if (index < this->counter) {
					dif -= this->digit[index];
				}
				dif -= inMind;
				if (dif < 0) {
					inMind = 1;
				}
				else {
					inMind = 0;
				}
				answer.digit[index] = dif;
			}
		}
		else {
			answer.sign = this->sign;

			for (int index = 0; index < this->counter; ++index) {
				long long dif = this->digit[index];
				if (index < alien.counter) {
					dif -= alien.digit[index];
				}
				dif -= inMind;
				if (dif < 0) {
					inMind = 1;
				}
				else {
					inMind = 0;
				}
				answer.digit[index] = dif;
			}
		}
	}
	
	this->swap(answer);
	this->pruning();
	return *this;
}
BigInteger& BigInteger::operator-= (const BigInteger& alien) {
	this->sign *= -1;
	*this += alien;
	this->sign *= -1;
	return *this;
}

BigInteger& BigInteger::operator*= (const BigInteger& alien) {
	if (*this == ZERO) {
		return *this;
	}
	if (alien == ZERO) {
		return *this = ZERO;
	}

	if (*this == ONE) {
		return *this = alien;
	}
	if (*this == NEGATIVE_ONE){
		return *this = -alien;
	}
	
	if (alien == ONE) {
		return *this;
	}
	if (alien == NEGATIVE_ONE) {
		this->sign *= -1;
		return *this;
	}

	BigInteger answer;
	delete[] answer.digit;
	answer.counter = answer.capacity = alien.capacity + this->capacity;
	answer.digit = new unsigned int[answer.capacity]{ 0 };

	answer.sign = static_cast<char>(static_cast<int>(alien.sign) * static_cast<int>(this->sign));

	for (int index = 0; index < this->counter; ++index) {
		unsigned long long inMind = 0;
		for (int jindex = 0; jindex < alien.counter; ++jindex) {
			unsigned long long mult = static_cast<unsigned long long>(alien.digit[jindex])
				* static_cast<unsigned long long>(this->digit[index]) + inMind + answer.digit[index + jindex];
			answer.digit[index + jindex] = mult % DEGREEBIGINTEGER;
			inMind = mult / DEGREEBIGINTEGER;
		}
		if (inMind != 0) {
			answer.digit[index + alien.counter] += inMind;
		}
	}

	this->swap(answer);
	this->pruning();
	return *this;
}

BigInteger& BigInteger::operator/= (const BigInteger& alien){
	if (alien == ZERO) {
		throw "Error: Divide by zero";
	}
	if (*this == ZERO) {
		return *this;
	}
	if (alien == ONE) {
		return *this;
	}
	if (alien == NEGATIVE_ONE) {
		this->sign *= -1;
		return *this;
	}

	BigInteger thisABS = this->abs();
	BigInteger alienABS = alien.abs();

	if (thisABS < alienABS) {
		return *this = ZERO;
	}

	BigInteger answer;
	delete[] answer.digit;
	answer.sign = 1;

	answer.capacity = answer.counter = this->counter - alien.counter + 1;
	answer.digit = new unsigned int[answer.capacity]{0};

	for (int index = answer.counter - 1; index >= 0; --index) {

		unsigned int trulyDigit = 0;
		unsigned int left = 0;
		unsigned int right = DEGREEBIGINTEGER - 1;

		while (left < right) {
			unsigned int mid = (right - left) / 2 + left;
			answer.digit[index] = mid;
			BigInteger tmp = answer * alienABS;
			if (tmp > thisABS) {
				right = mid;
			}
			else if (tmp < thisABS) {
				left = mid + 1;
				trulyDigit = mid;
			}
			else {
				trulyDigit = mid;
				break;
			}
		}
		answer.digit[index] = trulyDigit;
	}

	answer.sign = static_cast<char>(static_cast<int>(this->sign) * static_cast<int>(alien.sign));
	this->swap(answer);
	this->pruning();
	return *this;
}
BigInteger& BigInteger::operator%= (const BigInteger& alien) {
	*this -= (*this / alien) * alien;
	return *this;
}

std::string BigInteger::str() const
{
	std::string answer = std::to_string( this->digit[this->counter - 1]);

	for (int index = this->counter - 2; index >= 0; --index) {

		int length = static_cast<int>(answer.length());

		unsigned long long value = 0;
		unsigned long long  inMind = 0;

		for (int jindex = length - 1; jindex >= 0; --jindex) {
			
			value = (static_cast<unsigned long long>(answer[jindex] - '0') << 32) + inMind;
			answer[jindex] = static_cast<char>((value % 10) + '0');
			
			inMind = value / 10;
		}
		if (inMind != 0) {
			std::string tmp = std::move(answer);
			answer = std::to_string(inMind);
			answer += tmp;
		}

		length = static_cast<int>(answer.length());

		inMind = 0;
		unsigned int current = this->digit[index];

		for (int jindex = length - 1; jindex >= 0 && inMind + current != 0; --jindex) {

			value = current % 10 + static_cast<unsigned int>(answer[jindex] - '0') + inMind;
			answer[jindex] = static_cast<char>((value % 10) + '0');

			inMind = value / 10;
			current /= 10;
		}

		value = current + inMind;
		if (value != 0) {
			std::string tmp = std::move(answer);
			answer = std::to_string(value);
			answer += tmp;
		}
	}

	if (this->sign < 0) { answer = std::string("-") + answer; }

	return answer;
}

BigInteger operator+ (const BigInteger& left, const BigInteger& right) {
	BigInteger answer(left);
	answer += right;
	return answer;
}
BigInteger operator- (const BigInteger& left, const BigInteger& right) {
	BigInteger answer(left);
	answer -= right;
	return answer;
}
BigInteger operator* (const BigInteger& left, const BigInteger& right) {
	BigInteger answer(left);
	answer *= right;
	return answer;
}
BigInteger operator/ (const BigInteger& left, const BigInteger& right) {
	BigInteger answer(left);
	answer /= right;
	return answer;
}
BigInteger operator% (const BigInteger& left, const BigInteger& right) {
	BigInteger answer(left);
	answer %= right;
	return answer;
}

std::string to_string(const BigInteger& inDecimal) {
	return inDecimal.str();
}
