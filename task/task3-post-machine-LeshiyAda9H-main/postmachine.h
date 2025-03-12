#ifndef POST
#define POST

#include <iostream>
#include <fstream>
#include <string>

struct Command {

	int number;
	int transition1;
	int transition2;
	
	char symbol;
	
	Command() : symbol(0), transition1(0), transition2(0), number(0) {}
	Command(int num, int t1, int t2, char ch) : transition1(t1), transition2(t2), number(num), symbol(ch) {}
};


class arrCommand{

private:
	Command* arr;
	int length;
	int capacity;

public:
	arrCommand() : arr(nullptr), length(0), capacity(0){}  

	arrCommand(const arrCommand& Long) : length(Long.length), capacity(Long.length) {
		arr = new Command[length];
		
		for (int index = 0; index < length; ++index) {
			arr[index] = Long.arr[index];
		}
	}

	const Command& operator[] (int index) const {
		if (index < 0 || index >= length) {
			throw "index out of range";
		}
		return arr[index];
	}

	int find(int number) {
		int left = 0;
		int right = length - 1;

		while (left < right) {
			int middle = (right - left) / 2 + left;
			if (number < arr[middle].number) { right = middle - 1; }
			else if (number > arr[middle].number) { left = middle + 1; }
			else {
				left = middle;
				break;
			}
		}

		if (arr[left].number != number) { throw "Error"; }
		return left;
	}

	void add(const Command& com) {
		if(length == capacity) {
			capacity = (capacity == 0) ? 1: capacity*2;
			
			Command* tmp = new Command[capacity];
			
			for (int index = 0; index < length; ++index) {
				tmp[index] = arr[index];
			}
			
			delete[] arr;
			
			arr = tmp;
		}

		arr[length] = com;
		
		for (int index = length; index > 0; --index) {
			if (arr[index].number < arr[index - 1].number) {
				std::swap(arr[index], arr[index - 1]);
			}
			else { break; }
		}
		++length; 
	}

	~arrCommand() {
		delete[] arr;
	}
};

class PostMachine {
private:
	arrCommand array;
	char* tape;
	int current;
	int size;

public:
	PostMachine(int s, const arrCommand& arr) : size(s), current(0), array(arr) {
		//create tape
		tape = new char[size];
		for (int index = 0; index < size; ++index) {
			tape[index] = '0';
		}
	}

	std::string calc(std::string const& init, int maxsteps);

	~PostMachine() {
		delete[] tape;
	}
};

std::ifstream& operator>> (std::ifstream&, arrCommand&);
std::ifstream& operator>> (std::ifstream&, Command&);


#endif
