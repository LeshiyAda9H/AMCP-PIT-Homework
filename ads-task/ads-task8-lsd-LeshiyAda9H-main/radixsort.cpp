#include <iostream>
#include <fstream>

void mergeSort(const char* line, int* inds, int n)
{
	int* tmp = new int[n];
	int* from = inds;
	int* to = tmp;

	for (int step = 1; step < n; step *= 2){

		int to_ind = 0;
		
		for (int start = 0; start < n; start += 2 * step){
			
			int start1 = start;
			int end1 = (start1 + step < n) ? start1 + step : n;
			
			int start2 = end1;
			int end2 = (start2 + step < n) ? start2 + step : n;
			
			while (start1 < end1 && start2 < end2){

				if (line[from[start2]] < line[from[start1]]){
					to[to_ind++] = from[start2++];
				}
				else{
					to[to_ind++] = from[start1++];
				}
			}
			
			while (start1 < end1) { 
				to[to_ind++] = from[start1++];
			}
			
			while (start2 < end2) {
				to[to_ind++] = from[start2++];
			}
		}
		
		std::swap(from, to);
	}

	if (from != inds) {
		
		int ind = 0;
		while (ind < n) {
			inds[ind] = tmp[ind];
			++ind;
		}
	}


	delete[] tmp;
}

int main(int argc, const char* argv[])
{
	
	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[2]);
	
	int n = 0;
	int m = 0;
	int k = 0;
	
	inFile >> n >> m >> k;
	inFile.ignore();

	char** str = new char* [m];

	for (int index = 0; index < m; ++index){
		
		str[index] = new char[n + 1];
		inFile.getline(str[index], n + 1);
	}

	int* inds = new int[n];
	for (int index = 0; index < n; ++index){
		inds[index] = index;
	}

	for (int i = 0; i < k; ++i){
		mergeSort(str[m - i - 1], inds, n);
	}
	
	for (int i = 0; i < n; ++i){
		outFile << str[0][inds[i]];
	}

	
	for (int index = 0; index < m; ++index){
		delete[] str[index];
	}

	delete[] str;
	delete[] inds;


	inFile.close();
	outFile.close();
	
	return 0;
}

