#include "boolexpr.h"
#include <fstream>
#include <cstring>

int main(int argc, const char* argv[]) {
	if (argc < 4) {
		return 1;
	}

	std::ifstream inFile(argv[2]);

	if (!inFile) {
		return 2;
	}

	std::ofstream outFile(argv[3]);

	if (!outFile) {
		inFile.close();
		return 3;
	}

	char buffer[1024];
	try {
		if (strcmp(argv[1], "-cnf") == 0) {
			while (!inFile.eof()) {
				inFile.getline(buffer, 1024);
				BooleanExpression expression(buffer);
				outFile << expression.cnf() << std::endl;
				while (inFile.peek() != '~' && isdigit(inFile.peek()) == 0 &&
					inFile.peek() != 'x' && inFile.peek() != '(' && inFile.get() != EOF) {
				}
			}
		}
		else if (strcmp(argv[1], "-dnf") == 0) {
			while (!inFile.eof()) {
				inFile.getline(buffer, 1024);
				BooleanExpression expression(buffer);
				outFile << expression.dnf() << std::endl;
				while (inFile.peek() != '~' && isdigit(inFile.peek()) == 0 &&
					inFile.peek() != 'x' && inFile.peek() != '(' && inFile.get() != EOF) {
				}
			}
		}
		else if (strcmp(argv[1], "-zh") == 0) {
			while (!inFile.eof()) {
				inFile.getline(buffer, 1024);
				BooleanExpression expression(buffer);
				outFile << expression.zhegalkin() << std::endl;
				while (inFile.peek() != '~' && isdigit(inFile.peek()) == 0 &&
					inFile.peek() != 'x' && inFile.peek() != '(' && inFile.get() != EOF) {
				}
			}
		}
		else if (strcmp(argv[1], "-isfull") == 0) {
			std::vector<BooleanExpression> expressions;
			while (!inFile.eof()) {
				inFile.getline(buffer, 1024);
				BooleanExpression expression(buffer);
				expressions.push_back(expression);
				while (inFile.peek() != '~' && isdigit(inFile.peek()) == 0 &&
					inFile.peek() != 'x' && inFile.peek() != '(' && inFile.get() != EOF) {
				}
			}
			if (isFullSystem(expressions)) {
				outFile << "yes";
			}
			else {
				outFile << "no";
			}
		}
		else {
			return 4;
		}
	}
	catch (...) {
		outFile << "error";
	}

	inFile.close();
	outFile.close();
	return 0;
}