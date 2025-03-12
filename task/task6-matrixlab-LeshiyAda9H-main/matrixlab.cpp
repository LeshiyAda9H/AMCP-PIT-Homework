#include <fstream>
#include <iostream>
#include "matrixlabexpression.h"

int main(int argc, const char* argv[]){
	
	if (argc < 3) {
		std::cout << "Specify the input and output files" << std::endl;
		
		return 1;
	}

	std::ifstream inFile(argv[1]);
	if (!inFile.is_open()) {
		std::cout << "Can not open file to read!!!" << std::endl;
		
		return 2;
	}

	std::ofstream outFile(argv[2]);
	if (!outFile.is_open()) {
		std::cout << "Can not write to file!!!" << std::endl;
		
		return 3;
	}

	global::out = &outFile;

	char expression[1024]{};
	int count_line = 1;

	while (!inFile.eof()) {
		inFile.getline(expression, 1024);
		try {
			executingExpression(expression);
		}
		catch (...) {
			*global::out << "Error in line " << count_line << std::endl;
			break;
		}
		++count_line;
	}

	inFile.close();
	outFile.close();
	global::out = nullptr;
	return 0;
}
