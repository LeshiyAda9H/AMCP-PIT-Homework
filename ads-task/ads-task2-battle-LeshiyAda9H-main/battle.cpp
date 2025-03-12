#include <iostream>
#include <fstream>
#include "queueBattle.h"

void reading(std::ifstream& File, Queue& q);

int main(int argc, const char* argv[])
{
	Queue qFirst;
	Queue qSecond;

	std::ifstream inFile(argv[1]);

	reading(inFile, qFirst);

	reading(inFile, qSecond);



	bool flag = false;

	int million = 1000000;

	int tmp1 = 0;
	int tmp2 = 0;

	Queue qTmp;

	while (million > 0) {

		do {

			tmp1 = qFirst.pop();
			qTmp.push(tmp1);


			tmp2 = qSecond.pop();
			qTmp.push(tmp2);

		} while (tmp1 == tmp2 && qFirst.size() > 0 && qSecond.size() > 0);

		if (tmp1 == 0 && tmp2 == 12) {
			while (qTmp.size() > 0) {
				qFirst.push(qTmp.pop());
			}
		}
		else if (tmp2 == 0 && tmp1 == 12) {
			while (qTmp.size() > 0) {
				qSecond.push(qTmp.pop());
			}
		}
		else if (tmp2 < tmp1) {
			while (qTmp.size() > 0) {
				qFirst.push(qTmp.pop());
			}
		}
		else if (tmp1 < tmp2) {
			while (qTmp.size() > 0) {
				qSecond.push(qTmp.pop());
			}
		}

		if (qFirst.size() == 0 && qSecond.size() == 0) {
			std::cout << "draw";
			break;
		}
		if (qFirst.size() == 0 || qSecond.size() == 52) {
			std::cout << "second";
			break;
		}
		if (qSecond.size() == 0 || qFirst.size() == 52) {
			std::cout << "first";
			break;
		}


		--million;
	}

	if (million == 0) {
		std::cout << "unknown";
	}

	return 0;
}

void reading(std::ifstream& File, Queue& q) {
	for (int i = 0; i < 26; ++i) {
		switch (File.peek())
		{
		case '2':
			q.push(0);
			break;
		case '3':
			q.push(1);
			break;
		case '4':
			q.push(2);
			break;
		case '5':
			q.push(3);
			break;
		case '6':
			q.push(4);
			break;
		case '7':
			q.push(5);
			break;
		case '8':
			q.push(6);
			break;
		case '9':
			q.push(7);
			break;
		case '1':
			q.push(8);
			break;
		case 'J':
			q.push(9);
			break;
		case 'Q':
			q.push(10);
			break;
		case 'K':
			q.push(11);
			break;
		case 'A':
			q.push(12);
			break;
		}

		while (File.get() != '\n') {}
	}
}

