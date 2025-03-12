#ifndef stock
#define stock

#include <iostream>
#include <fstream>
#include <iomanip>
#include "errors.h"
#include <cstring>

class Stock
{
private:
	char ticker[16];
	bool isBuy;
	int count;
	double price;
	int id;

	int date;
	int sec;
public:
	Stock() : isBuy(false), count(0), price(0.0), id(0), date(0), sec(0){}

	Stock& operator= (const Stock&);

	void setId(int ID) {
		id = ID;
	}
	void setdate(int Julian) {
		date = Julian;
	}
	void setSec(int second) {
		sec = second;
	}
	void setTicker(const char* Tickers) {
		int index = 0;
		while (Tickers[index] != '\0') {
			ticker[index] = Tickers[index];
			++index;
		}
		this->ticker[index] = '\0';
	}
	void setIsBuy(bool buy) {
		isBuy = buy;
	}
	void setCount(int amount){
		count = amount;
	}
	void setPrice(double pricee) {
		price = pricee;
	}

	int getId() const {
		return id;
	}
	int getDate() const {
		return date;
	}
	int getSec() const{
		return sec;
	}
	const char* getTicker() const{
		return ticker;
	}
	bool getIsBuy() const {
		return isBuy;
	}
	int getCount() const {
		return count;
	}
	double getPrice() const {
		return price;
	}
	
};

std::istream& operator>> (std::istream&, Stock&);
std::ifstream& operator>> (std::ifstream&, Stock&);


std::ostream& operator<< (std::ostream&, const Stock&);
std::ofstream& operator<< (std::ofstream&, const Stock&);

bool day_Invalid(int day, int month, int year);
bool Leap(int year);

bool comparison_Add(const Stock&, const Stock&);
bool comparison_Time(const Stock&, const Stock&);
bool comparison_Dom(const Stock&, const Stock&);

bool caps(const char*, const char*);

#endif

