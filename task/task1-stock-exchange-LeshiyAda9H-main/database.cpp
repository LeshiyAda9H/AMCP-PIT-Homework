#include "database.h"

void DataBase::load(std::ifstream& inFile) {
	while (!inFile.eof()) {
		if (counter == capacity) {

			capacity = (capacity == 0) ? 1 : capacity * 2;
			Stock* tmp = new Stock[capacity];

			for (int index = 0; index < counter; ++index) {
				tmp[index] = data[index];
			}

			delete[] data;
			data = tmp;
		}

		inFile >> data[counter];
		data[counter++].setId(++ID);

		while (isdigit(inFile.peek()) == 0 && inFile.get() != EOF){}
	}
}
void DataBase::save(std::ofstream& outFile) const {
	for (int index = 0; index < counter; ++index) {
		outFile << data[index] << std::endl;
	}
}

void DataBase::ChooseSort(bool(*cmp)(const Stock&, const Stock&)) {

	for (int step = 0; step < this->counter - 1; ++step) {
		int minimumIndex = step;
		for (int i = minimumIndex + 1; i < this->counter; ++i) {
			if (cmp(this->data[i], this->data[minimumIndex])) {
				minimumIndex = i;
			}
		}
		if (step < minimumIndex) {
			std::swap(this->data[step], this->data[minimumIndex]);
		}
	}
}



void DataBase::add(Stock& dobavka) {
	if (counter == capacity) {

		capacity = (capacity == 0) ? 1 : capacity * 2;
		Stock* tmp = new Stock[capacity];

		for (int index = 0; index < counter; ++index) {
			tmp[index] = data[index];
		}

		delete[] data;
		data = tmp;
	}

	ChooseSort(comparison_Add);
	if (dobavka.getIsBuy()) {
		int index = 0;

		while (index < counter && dobavka.getCount() > 0 && !data[index].getIsBuy() && data[index].getPrice() <= dobavka.getPrice()) {
			if (caps(dobavka.getTicker(), data[index].getTicker())) {
				int min = (dobavka.getCount() > data[index].getCount())? data[index].getCount() : dobavka.getCount();
				dobavka.setCount(dobavka.getCount()-min);
				data[index].setCount(data[index].getCount() - min);
			}
			++index;
		}

	}
	else {
		int index = counter-1;

		while (index >= 0 && dobavka.getCount() > 0 && data[index].getIsBuy() && data[index].getPrice() >= dobavka.getPrice() ) {
			if (caps(dobavka.getTicker(), data[index].getTicker())) {
				int min = (dobavka.getCount() > data[index].getCount()) ? data[index].getCount() : dobavka.getCount();
				dobavka.setCount(dobavka.getCount() - min);
				data[index].setCount(data[index].getCount() - min);
			}
			--index;
		}
	}

	dobavka.setId(++this->ID);
	this->data[counter++] = dobavka;
}

void DataBase::kill(int number) {

	int index = 0;
	while (index < counter && data[index].getId() != number ) {
		++index;
	}
	if (index == counter) {
		return;
	}
	--counter;
	while (index < counter) {
		std::swap(data[index], data[index+1]);
		++index;
	}

}

void DataBase::clear() {
	int index = 0;
	while (index < counter) {
		if (data[index].getCount() == 0) {
			kill(data[index].getId());
			--index;
		}
		++index;
	}
}

void DataBase::print(std::ostream& Console) {
	ChooseSort(comparison_Time);

	for (int index = 0; index < counter; ++index) {
		Console << this->data[index] << std::endl;
	}
}


//dom: òèï çàÿâêè, öåíà, êîëè÷åñòâî, äàòà è âðåìÿ çàÿâêè


void DataBase::dom(const char* Ticker, std::ostream& Console) {
	ChooseSort(comparison_Dom);

	for (int index = 0; index < counter; ++index) {
		if (caps(data[index].getTicker(), Ticker)) {
			if (data[index].getIsBuy()) {
				Console << "buy, ";
			}
			else {
				Console << "sell, ";
			}

			Console << std::fixed << std::setprecision(2) << data[index].getPrice() << ", " << data[index].getCount() << ", ";


			int a = data[index].getDate() + 32044;
			int b = (4 * a + 3) / 146097;
			int c = a - (146097 * b) / 4;
			int d = (4 * c + 3) / 1461;
			int e = c - (1461 * d) / 4;
			int m = (5 * e + 2) / 153;

			int year = 100 * b + d - 4800 + m / 10;
			int month = m + 3 - 12 * (m / 10);
			int day = e - (153 * m + 2) / 5 + 1;

			Console << year << "." << month / 10 << month % 10 << "." << day / 10 << day % 10 << " ";

			int hour = data[index].getSec() / 3600;
			int minute = (data[index].getSec() % 3600) / 60;
			int second = data[index].getSec() % 60;

			Console << hour / 10 << hour % 10 << ':' << minute / 10 << minute % 10 << ':' << second / 10 << second % 10 << std::endl;
		}
	}
}

//export: äàòà è âðåìÿ çàÿâêè, òèêåð, òèï çàÿâêè, êîëè÷åñòâî, öåíà

void DataBase::exporti(std::ofstream& outFile) {
	ChooseSort(comparison_Time);

	for (int index = 0; index < counter; ++index) {
		outFile << this->data[index] << std::endl;
	}

}
