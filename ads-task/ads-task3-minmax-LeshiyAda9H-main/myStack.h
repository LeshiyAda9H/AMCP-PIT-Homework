#ifndef MYSTACK
#define MYSTACK

template <typename T>
class MyStack{

private:
	T* arr;
	int arrEnd;
	int capacity;

public:
	MyStack(): arr(nullptr), arrEnd(0), capacity(0) {}
	~MyStack() {
		delete[] arr;
	}

	void pop() {
		if(arrEnd == 0){
			throw;
		}

		--arrEnd;
	}

	void push(T alien) {
		if (capacity == arrEnd) {
			capacity = (capacity == 0) ? 1 : capacity * 2;
			T* arrFuture = new T[capacity];

			for (int i = 0; i < arrEnd; ++i) {
				arrFuture[i] = arr[i];
			}
			delete[] arr;

			arr = arrFuture;
		}

		arr[arrEnd] = alien;
		++arrEnd;
	}

	T top() const {
		if (arrEnd == 0) {
			throw;
		}
		return arr[arrEnd - 1];
	}

	bool empty() const {
		return (arrEnd == 0);
	}
	
};


#endif // !MYSTACK
