#ifndef QUEUEBATTLE
#define QUEUEBATTLE

class Queue {
private:
	int arr[52];
	int begin;
	int end;
	int counter;
public:
	Queue() : begin(0), end(-1), counter(0) {}

	int pop() {
		if (counter == 0) {
			throw "error";
		}
		--counter;
		if (begin == 51) {
			begin = 0;
			return arr[51];
		}

		return arr[begin++];

	}

	void push(int alien) {
		if (counter == 52) {
			throw "error";
		}

		if (end == 51) {
			end = 0;
			arr[end] = alien;
		}
		else {
			arr[++end] = alien;
		}

		++counter;
	}

	int size() const {
		return counter;
	}
};


#endif
