#include <iostream>
#include <fstream>

void QuickSortS(int* M, int n, int k1, int k2) {

	int N = n, size = 1;
	while (N > 0) {
		N >>= 1; // N=N/2;
		++size;
	}

	size += 2;

	int* stackLeft = new int[size];
	int* stackRight = new int[size];
	int topInStack = -1;

	++topInStack; stackLeft[topInStack] = 0; stackRight[topInStack] = n - 1;

	while (topInStack > -1) {
		int from = stackLeft[topInStack];
		int to = stackRight[topInStack];
		--topInStack;

		int left = from, right = to;
		int p = M[(left + right) >> 1];

		while (left < right) {
			while (M[left] < p) { ++left; }
			while (p < M[right]) { --right; }
			if (left < right) {
				std::swap(M[left], M[right]);

				++left;
				--right;
			}
			else if (left == right) {
				++left;
				--right;
			}
		}

		if (((left + right) >> 1) < left) {
			if (right > from && right >= k1) {
				++topInStack;
				stackLeft[topInStack] = from;
				stackRight[topInStack] = right;
			}
			if (left < to && left <= k2) {
				++topInStack;
				stackLeft[topInStack] = left;
				stackRight[topInStack] = to;
			}
		}
		else {
			if (left < to && left <= k2) {
				++topInStack;
				stackLeft[topInStack] = left;
				stackRight[topInStack] = to;
			}
			if (right > from && right >= k1) {
				++topInStack;
				stackLeft[topInStack] = from;
				stackRight[topInStack] = right;
			}
		}

	}

	delete[] stackLeft;
	delete[] stackRight;
}

int main(int argc, const char* argv[]) {

	std::ifstream inFile(argv[1]);

	std::ofstream outFile(argv[2]);

	int n = 0;
	int k1 = 0;
	int k2 = 0;

	inFile >> n >> k1 >> k2;

	while (inFile.get() != '\n') {}

	int* arr = new int[n];

	int A = 0;
	int B = 0;
	int C = 0;
	inFile >> A >> B >> C;

	inFile >> arr[0] >> arr[1];

	for (int i = 2; n > i; ++i) {
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
	}

	--k1; --k2;

	QuickSortS(arr, n, k1, k2);


	for (int i = k1; i < k2; ++i) {
		outFile << arr[i] << ' ';
	}
	outFile << arr[k2];

	delete[] arr;

	return 0;
}
