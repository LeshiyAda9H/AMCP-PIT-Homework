#ifndef QUEUEMINMAX
#define QUEUEMINMAX

#include "myStack.h"
#include <iostream>
#include <fstream>

class Queue
{
private:
	struct forStack{
		int number;
		int minimum;
		int maximum;
	};

	forStack tmp;
	
	MyStack<forStack> stackFirst;
	MyStack<forStack> stackSecond;

	

public:
	Queue(): tmp(), stackFirst(), stackSecond() {}

	~Queue() {}


	void push(int value) {

		tmp.number = value;

		if (stackFirst.empty()) {
			tmp.minimum = value;
			tmp.maximum = value;

			stackFirst.push(tmp);
			return;
		}

		if (value < tmp.minimum) {
			tmp.minimum = value;
		}
		if (value > tmp.maximum) {
			tmp.maximum = value;
		}

		stackFirst.push(tmp);


	}

	void pop() {
		if (stackSecond.empty()) {

			tmp = stackFirst.top();
			tmp.maximum = tmp.number;
			tmp.minimum = tmp.number;

			stackSecond.push(tmp);
			stackFirst.pop();
			

			while (!stackFirst.empty()) {

				if (stackFirst.top().number < tmp.minimum) {
					tmp.minimum = stackFirst.top().number;
				}
				if (stackFirst.top().number > tmp.maximum) {
					tmp.maximum = stackFirst.top().number;
				}
				stackSecond.push(tmp);
				stackFirst.pop();
			}
			stackSecond.pop();
			return;
		}

		stackSecond.pop();

	}


	int max() {
		
		if (stackFirst.empty() && stackSecond.empty()) {
			throw;
		}
		
		if (!stackFirst.empty() && !stackSecond.empty()) {
			if (stackFirst.top().maximum > stackSecond.top().maximum) {
				return stackFirst.top().maximum;
			}
			
			return stackSecond.top().maximum;
		}
		
		if (stackFirst.empty()) {
			return stackSecond.top().maximum;
		}

		return stackFirst.top().maximum;

	}

	int min() {

		if (stackFirst.empty() && stackSecond.empty()) {
			throw;
		}

		if (!stackFirst.empty() && !stackSecond.empty()) {
			if (stackFirst.top().minimum < stackSecond.top().minimum) {
				return stackFirst.top().minimum;
			}

			return stackSecond.top().minimum;
		}

		if (stackFirst.empty()) {
			return stackSecond.top().minimum;
		}

		return stackFirst.top().minimum;

	}
				
};


#endif
