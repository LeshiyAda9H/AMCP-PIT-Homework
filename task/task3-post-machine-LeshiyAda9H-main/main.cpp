#include "postmachine.h"

int main(int argc, const char* argv[])
{
	std::ifstream inFile(argv[2]);

	if (!inFile) {
		return 1;
	}

	int size;
	int maxCycl;
	std::string init;

	inFile >> size >> maxCycl;

	while (isdigit(inFile.peek()) == 0) { inFile.ignore(); }
	inFile >> init;

	std::ifstream progrFile(argv[1]);
	if (!progrFile) {
		return 2;
	}

	arrCommand arr;
	progrFile >> arr;

	PostMachine post(size, arr);

	std::ofstream outFile(argv[3]);
	if (!outFile) {
		return 3;
	}

	try {
		outFile << post.calc(init, maxCycl);
	}
	catch (...) {
		outFile << "Error";
	}

	inFile.close();
	progrFile.close();
	outFile.close();


	return 0;
}