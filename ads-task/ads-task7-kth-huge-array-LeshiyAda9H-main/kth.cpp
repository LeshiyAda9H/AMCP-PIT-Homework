#include <fstream>
#include <iostream>

void makeHeap(int* mass, int n) {
	for (int i = 1; i < n; ++i) {
		int pos = i;
		while (pos != 0) {
			int parent = (pos - 1) / 2;

			if (mass[parent] < mass[pos]) {

				std::swap(mass[parent], mass[pos]);
				pos = parent;
			}
			else
				break;
		}
	}
}

void goingDown(int* mass, int n) {

	int index = 0;

	while ( 2*index+1 < n) {

		int max = (2 * index + 2 < n && mass[2 * index + 1] < mass[2 * index + 2]) ? 2 * index + 2 : 2 * index + 1;

		if (mass[index] < mass[max]) {
			std::swap(mass[index], mass[max]);
			index = max;
		}
		else {
			break;
		}
	}
}


int main(int argc, const char* argv[]) {


	std::ifstream inFile(argv[1]);

	std::ofstream outFile(argv[2]);


	int n = 0;
	int k1 = 0;
	int k2 = 0;

	inFile >> n >> k1 >> k2;

	while (inFile.get() != '\n') {}

	int* arr = new int[k2];

	int A = 0;
	int B = 0;
	int C = 0;

	inFile >> A >> B >> C;

	inFile >> arr[0] >> arr[1];

	for (int i = 2; k2 > i; ++i) {
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
	}

	int x_i1 = arr[k2 - 1];
	int x_i2 = arr[k2 - 2];

	makeHeap(arr, k2);

	for (int i = k2; n > i; ++i) {
		int x_i = A * x_i2 + B * x_i1 + C;

		if (x_i < arr[0]) {
			arr[0] = x_i;

			goingDown(arr, k2);
		}

		x_i2 = x_i1;
		x_i1 = x_i;
	}

	--k1; --k2;

	for (int i = k2; i >= k1; --i) {
		std::swap(arr[0], arr[i]);
		goingDown(arr, i);
	}


	for (int i = k1; i < k2; ++i) {
		outFile << arr[i] << ' ';
	}
	outFile << arr[k2];

	delete[] arr;

	return 0;

}
