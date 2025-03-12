#include "postmachine.h" 


std::ifstream& operator>>(std::ifstream& inFile, arrCommand& arrCom) {
	
	Command tmp;

	while (inFile.peek() != '%' && isdigit(inFile.peek()) == 0 && inFile.get() != EOF) {}

	while (!(inFile.eof())) {
		if (inFile.peek() != '%') {
			inFile >> tmp;
			arrCom.add(tmp);
		}
		else {
			while(inFile.get() != '\n'){}
		}
		while (inFile.peek() != '%' && isdigit(inFile.peek()) == 0 && inFile.get() != EOF) {}
	}
	return inFile; 
}

std::ifstream& operator>> (std::ifstream& inFile, Command& com) {

	while (inFile.peek() != '%' && isdigit(inFile.peek()) == 0 && inFile.get() != EOF) {}

	inFile >> com.number;
			
	if (inFile.get() != '.') { throw "Error"; }

	while (inFile.peek() == ' ') { inFile.ignore(); }

	if (inFile.peek() != 'V' && inFile.peek() != 'X' && inFile.peek() != 'L' && inFile.peek() != 'R' && inFile.peek() != '?' && inFile.peek() != '!') { throw "Error"; }

	inFile >> com.symbol;

	while (inFile.peek() == ' ') { inFile.ignore(); }

	if (inFile.peek() == '\n' || inFile.peek() == '%') {
		inFile.ignore();
		return inFile;
	}
	if (inFile.peek() == '\r') {
		inFile.ignore();
		if (inFile.peek() == '\n') { inFile.ignore(); }
		return inFile;
	}

	inFile >> com.transition1;

	while (inFile.peek() == ' ') { inFile.ignore(); }

	if (inFile.peek() == '\n' || inFile.peek() == '%') {
		inFile.ignore();
		return inFile;
	}
	if (inFile.peek() == '\r') {
		inFile.ignore();
		if (inFile.peek() == '\n') { inFile.ignore(); }
		return inFile;
	}

	inFile >> com.transition2;

	return inFile;
}



std::string PostMachine::calc(std::string const& init, int maxsteps) {
	for (int index = 0; index < init.length(); ++index) {
		tape[index] = init[index];
	}

	int counter = 0;
	int index = 0;
	bool isOver = false;

	while (counter < maxsteps && !isOver) {
		switch (array[index].symbol) {
		case 'V':
			tape[current] = '1';
			index = array.find(array[index].transition1);
			break;
		case 'X':
			tape[current] = '0';
			index = array.find(array[index].transition1);
			break;
		case 'L':
			current = (current == 0) ? size - 1 : current - 1;
			index = array.find(array[index].transition1);
			break;
		case 'R':
			current = (current == size - 1) ? 0 : current + 1;
			index = array.find(array[index].transition1);
			break;
		case '?':
			index = (tape[current] == '0') ? array.find(array[index].transition1) : array.find(array[index].transition2);
			break;
		case '!':
			isOver = true;
			break;
		}
		++counter;
	}

	if (counter == maxsteps) {
		return std::string("Not applicable");
	}

	int last = (current + 1) % size;
	int tmp = last;

	while (tmp != current) {
		if (tape[tmp] == '1') {
			last = tmp;
		}
		++tmp;
		tmp %= size;
	}

	return (current < last)
		? std::string(tape + current, last - current + 1)
		: std::string(tape + current, size - current) + std::string(tape, last + 1);
}