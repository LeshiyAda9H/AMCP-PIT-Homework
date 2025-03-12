#include "stock.h"


Stock& Stock::operator=(const Stock& stockich) {
	if (this != &stockich) {
		this->isBuy = stockich.isBuy;
		this->date = stockich.date;
		this->sec = stockich.sec;
		this->price = stockich.price;
		this->id = stockich.id;
		this->count = stockich.count;


		int index = 0;
		while (stockich.ticker[index] != '\0') {
			this->ticker[index] = stockich.ticker[index];
			++index;
		}
		this->ticker[index] = '\0';
	}
	return *this;
}

//add 13/02.2023 10:00:00, Tesla, buy, 5, 125.54

std::istream& operator>> (std::istream& Console, Stock& conStock) {
	
	int day = 0;
	int month = 0;
	int year = 0;

	char buffer[32];
	Console.getline(buffer, 32, ' ');

	int indexBuf = 0;
	
	while (isdigit(buffer[indexBuf]) != 0) {
		day = day * 10 + buffer[indexBuf] - '0';
		++indexBuf;
	}
	if (buffer[indexBuf++] != '.') { throw WrongFormatDate(buffer); }

	while (isdigit(buffer[indexBuf]) != 0) {
		month = month * 10 + buffer[indexBuf] - '0';
		++indexBuf;
	}
	if (buffer[indexBuf++] != '.') { throw WrongFormatDate(buffer); }

	while (isdigit(buffer[indexBuf]) != 0) {
		year = year * 10 + buffer[indexBuf] - '0';
		++indexBuf;
	}
	if (day_Invalid(day, month, year)) {
		indexBuf = 0;
		while (isdigit(buffer[indexBuf]) != 0) { ++indexBuf; }
		buffer[indexBuf] = '\0';
		throw WrongValueDay(buffer);
	}

	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;

	conStock.setdate( day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045);


	indexBuf = 0;
	Console.getline(buffer, 32, ',');

	int hour = 0;
	int minute = 0;
	int second = 0;
	while (isdigit(buffer[indexBuf]) != 0) {
		hour = hour * 10 + buffer[indexBuf] - '0';
		++indexBuf;
	}
	if (hour > 23) {
		throw WrongValueTime(buffer);
	}
	if (buffer[indexBuf++] != ':') { throw WrongFormatTime(buffer); }

	while (isdigit(buffer[indexBuf]) != 0) {
		minute = minute * 10 + buffer[indexBuf] - '0';
		++indexBuf;
	}
	if (minute > 59) {
		throw WrongValueTime(buffer);
	}
	if (buffer[indexBuf++] != ':') { throw WrongFormatTime(buffer); }


	while (isdigit(buffer[indexBuf]) != 0) {
		second = second * 10 + buffer[indexBuf] - '0';
		++indexBuf;
	}
	if (second > 59) {
		throw WrongValueTime(buffer);
	}

	conStock.setSec( hour * 3600 + minute * 60 + second);




	while (isalpha(Console.peek()) == 0) { Console.ignore(); }
	Console.getline(buffer, 16, ',');

	conStock.setTicker(buffer);

	while (isalpha(Console.peek()) == 0) { Console.ignore(); }

	Console.getline(buffer, 32, ',');

	if (strcmp(buffer, "buy") == 0) {
		conStock.setIsBuy(true);
	}
	else if(strcmp(buffer, "sell") == 0) {
		conStock.setIsBuy(false);
	}
	else {
		throw WrongType(buffer);
	}

	int count;
	Console >> count;
	conStock.setCount(count);

	if (Console.get() != ',') { throw "Gde moya zapyatay"; }

	double price;
	Console >> price;
	conStock.setPrice(price);

	return Console;
}

bool day_Invalid(int day, int month, int year) {
	return (day < 1 || day > 31) || (day > 28 && month == 2 && !Leap(year)) || (day > 29 && month == 2)
		|| (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11));
}
bool Leap(int year) {
	if (year % 100 == 0) { return year % 400 == 0; }
	return year % 4 == 0;
}

std::ifstream& operator>> (std::ifstream& inFile, Stock& inStock) {
	int day = 0;
	int month = 0;
	int year = 0;
	inFile >> year;
	inFile.ignore();
	inFile >> month;
	inFile.ignore();
	inFile >> day;
	
	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;

	inStock.setdate(day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045);

	int hour = 0;
	int minute = 0;
	int second = 0;
	inFile >> hour;
	inFile.ignore();
	inFile >> minute;
	inFile.ignore();
	inFile >> second;

	inStock.setSec(hour * 3600 + minute * 60 + second);

	while (isalpha(inFile.peek()) == 0) { inFile.ignore(); }

	char buffer[16];
	inFile.getline(buffer, 16, ',');
	inStock.setTicker(buffer);

	while (isalpha(inFile.peek()) == 0) { inFile.ignore(); }

	inFile.getline(buffer, 16, ',');
	inStock.setIsBuy(strcmp(buffer, "buy") == 0);

	while (isdigit(inFile.peek()) == 0) { inFile.ignore(); }

	int count;
	inFile >> count;
	inStock.setCount(count);

	while (isdigit(inFile.peek()) == 0) { inFile.ignore(); }

	double price;
	inFile >> price;
	inStock.setPrice(price);

	return inFile;
}


std::ostream& operator<< (std::ostream& Console, const Stock& conStock) {

	Console << conStock.getId() << ", ";

	int a = conStock.getDate() + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - (146097 * b) / 4;
	int d = (4 * c + 3) / 1461;
	int e = c - (1461 * d) / 4;
	int m = (5 * e + 2) / 153;

	int year = 100 * b + d - 4800 + m / 10;
	int month = m + 3 - 12 * (m / 10);
	int day = e - (153 * m + 2) / 5 + 1;

	Console << year << "." << month / 10 << month % 10 << "." << day / 10 << day % 10 << " ";

	int hour = conStock.getSec() / 3600;
	int minute = (conStock.getSec() % 3600) / 60;
	int second = conStock.getSec() % 60;

	Console << hour / 10 << hour % 10 << ':' << minute / 10 << minute % 10 << ':' << second / 10 << second % 10 << ", " << conStock.getTicker() << ", ";

	if (conStock.getIsBuy()) {
		Console << "buy, ";
	}
	else {
		Console << "sell, ";
	}

	Console << conStock.getCount() << ", " << std::fixed << std::setprecision(2) << conStock.getPrice();
	return Console;
}

// export: дата и время заявки, тикер, тип заявки, количество, цена.
std::ofstream& operator<< (std::ofstream& outFile, const Stock& outStock) {
	
	int a = outStock.getDate() + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - (146097 * b) / 4;
	int d = (4 * c + 3) / 1461;
	int e = c - (1461 * d) / 4;
	int m = (5 * e + 2) / 153;

	int year = 100 * b + d - 4800 + m / 10;
	int month = m + 3 - 12 * (m / 10);
	int day = e - (153 * m + 2) / 5 + 1;

	outFile << year << "." << month / 10 << month % 10 << "." << day / 10 << day % 10 << " ";

	int hour = outStock.getSec() / 3600;
	int minute = (outStock.getSec() % 3600) / 60;
	int second = outStock.getSec() % 60;

	outFile << hour / 10 << hour % 10 << ':' << minute / 10 << minute % 10 << ':' << second / 10 << second % 10 << ", " << outStock.getTicker() << ", ";

	if (outStock.getIsBuy()) {
		outFile << "buy, ";
	}
	else {
		outFile << "sell, ";
	}

	outFile << outStock.getCount() << ", " << std::fixed << std::setprecision(2) << outStock.getPrice();
	return outFile;
}

bool caps(const char* upTicker, const char* downTicker) {

	int index = 0;

	while (upTicker[index] != '\0' && downTicker[index] != '\0') {
		if ((upTicker[index] & 223) != (downTicker[index] & 223)) {
			return false;
		}
		++index;
	}

	return upTicker[index] == '\0' && downTicker[index] == '\0';
}


bool comparison_Add(const Stock& up, const Stock& down) {
	if (up.getIsBuy() ^ down.getIsBuy()) {
		return !up.getIsBuy();
	}

	if (up.getPrice() != down.getPrice()) {
		return up.getPrice() < down.getPrice();
	}

	return up.getId() < down.getId();
}


bool comparison_Time(const Stock& up, const Stock& down) {
	if (up.getDate() != down.getDate()) { return up.getDate() < down.getDate(); }
	if (up.getSec() != down.getSec()) { return up.getSec() < down.getSec(); }
	return up.getId() < down.getId();
}
bool comparison_Dom(const Stock& up, const Stock& down) {
	if (up.getPrice() != down.getPrice()) { return up.getPrice() > down.getPrice(); }
	if (up.getIsBuy() ^ down.getIsBuy()) { return up.getIsBuy(); }
	return up.getIsBuy() == comparison_Time(up, down);
}
