#include "queueMinMax.h"

int main(int argc, const char* argv[]){

	//file
	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[2]);
	
	int N = 0;
	inFile >> N;
	while (inFile.get() != '\n') {}

	//queue
	Queue q;
	int number = 0;

	while (N > 0) {
		switch (inFile.get()) {
		case '+':

			inFile >> number;
			while (inFile.get() != '\n') {}

			q.push(number);
			break;

		case '-':
			q.pop();
			while (inFile.get() != '\n') {}
			break;

		case '?':
			outFile << (q.max() - q.min()) << '\n';
			while (inFile.get() != '\n') {}
			break;
		}
		--N;
	}


}