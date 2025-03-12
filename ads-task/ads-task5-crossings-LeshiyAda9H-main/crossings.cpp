#include <iostream>
#include <fstream>

struct line{
	int x0;
	int x1;
};

bool sravn9tor_x0(const line& line1, const line& line2) {
	return line1.x0 < line2.x0;
}

bool sravn9tor_x1(const line& line1, const line& line2) {
	return line1.x1 < line2.x1;
}

long long MergeSortA(line* M, int n, bool (*sravn9tor)(const line&, const line&));

int main(int argc, const char* argv[]){
	
	std::ifstream inFile(argv[1]);
	int n;
	inFile >> n;

	line* arr = new line[n];

	for (int i = 0; n > i; ++i) {
		inFile >> arr[i].x0 >> arr[i].x1;
	}

	MergeSortA(arr, n, sravn9tor_x0);

	std::cout << MergeSortA(arr, n, sravn9tor_x1);
	delete[] arr;

	return 0;
	
}
long long MergeSortA(line* M, int n, bool (*sravn9tor)(const line&, const line&)) {

	long long counter = 0;

	line* tmp = new line[n];
	line* from = M;
	line* to = tmp;
	
	for (int step = 1; step < n; step *= 2) {
		
		int start1, end1, start2, end2;
		int indto = 0;
		
		for (int start = 0; start < n; start += 2 * step) {
			
			start1 = start; end1 = start1 + step; end1 = end1 < n ? end1 : n;
			start2 = end1;  end2 = start2 + step; end2 = end2 < n ? end2 : n;

			while (start1 < end1 && start2 < end2) {

				if (sravn9tor(from[start1], from[start2])) {
					to[indto++] = from[start1++];

				}
				else {
					counter += end1 - start1;
					to[indto++] = from[start2++];

				}

			}

			while (start1 < end1) {
				to[indto++] = from[start1++];
			}

			while (start2 < end2) {
				to[indto++] = from[start2++];
			}
		}

		std::swap(from, to);
	}

	if (from != M) {
		
		int ind = 0;
		
		while (ind < n) {
			M[ind] = tmp[ind];
			++ind;
		}
	}

	delete[] tmp;

	return counter;
}