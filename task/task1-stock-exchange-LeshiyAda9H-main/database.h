#ifndef DATABASE
#define DATABASE

#include "stock.h"

class DataBase{
private:
	Stock* data = nullptr;
	int counter;
	int capacity;
	int ID;

	void ChooseSort(bool (*cmp)(const Stock&, const Stock&));
public:
	DataBase() : data(nullptr), capacity(0), counter(0), ID(0){}

	~DataBase() {
		delete[] data;
	}

	void load(std::ifstream&);
	void save(std::ofstream&) const;

	void add(Stock&);
	void kill(int);
	void clear();

	void print(std::ostream&);
	void dom(const char*, std::ostream&);
	void exporti(std::ofstream&);

};


#endif 