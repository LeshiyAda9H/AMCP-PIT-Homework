#include <iostream>
#include <fstream>

struct student {
    int id;
    double score;
};

void heapify(student arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left].score > arr[largest].score)
        largest = left;

    if (right < n && arr[right].score > arr[largest].score)
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(student arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main(int argc, const char* argv[])
{
    std::ifstream inFile(argv[1]);

    int n = 0;
    inFile >> n;

    while (inFile.get() != '\n') {}

    student* arr = new student[n];

    for (int i = 0; i < n; ++i) {
        inFile >> arr[i].score;

        arr[i].id = i + 1;
    }
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    heapSort(arr, n);

    std::cout << arr[0].id << " " << arr[n/2].id << " " << arr[n-1].id;

    delete[] arr;

    return 0;
}
