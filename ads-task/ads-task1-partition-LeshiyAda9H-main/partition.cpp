#include <iostream>

long long partition(int n, int k);

int main () {
	int n = 0;
	int k = 0;
	std::cin >> n >> k;
	std::cout << partition(n, k);
	return 0;
}

long long partition(int n, int k){
  if (k == 1 && n == 1) {
        return 1;
    }
    
    long long tmp1 = 0;
    long long tmp2 = 0;

    long long* array_ = new long long[n];
    for (int i = 0; i < n; i++) {
        array_[i] = 1;
    }

    for (int rows = 2; rows <= k; ++rows) {
        for (int cols = 1; cols <= n; ++cols) {

            if (rows > cols) {

                array_[cols - 1] = 0;
            }
            else if (rows == cols || cols - rows == 1) {
                tmp1 = array_[cols - 1];
                array_[cols - 1] = 1;
            }
            else {
                tmp2 = array_[cols - 1];
                array_[cols - 1] = tmp1 + array_[cols - rows - 1];
                tmp1 = tmp2;
            }
        }
    }
    
    tmp1 = array_[n-1];
    delete[] array_;
    return tmp1;
    
}
