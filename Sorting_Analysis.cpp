#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;
// Bubble Sort
void bubbleSort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// Merge Sort
void merge(std::vector<int>& vec, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = vec[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = vec[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            ++i;
        } else {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& vec, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(vec, left, middle);
        mergeSort(vec, middle + 1, right);
        merge(vec, left, middle, right);
    }
}

// Quick Sort
int partition(std::vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (vec[j] < pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }

    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main() {
    srand(time(nullptr)); // Seed the random number generator
int arr[]={100,1000,2000,5000,10000};
int n=sizeof(arr)/sizeof(int);
    vector<int>inputSizes(arr,arr+n);// Add more sizes as needed

    std::cout << "Sorting Algorithm Time Analysis\n";

    for (int vectorSize : inputSizes) {
        std::vector<int> vec(vectorSize);

        // Generate random data
        for (int i = 0; i < vectorSize; ++i) {
            vec[i] = rand();
        }

        // Bubble Sort
        {
            std::vector<int> tempVec = vec;
            auto start = std::chrono::high_resolution_clock::now();
            bubbleSort(tempVec);
            auto end = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::cout << "Bubble Sort - Vector Size: " << vectorSize << ", Execution Time: " << duration << " seconds\n";
        }

        // Merge Sort
        {
            std::vector<int> tempVec = vec;
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(tempVec, 0, vectorSize - 1);
            auto end = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::cout << "Merge Sort - Vector Size: " << vectorSize << ", Execution Time: " << duration << " seconds\n";
        }

        // Quick Sort
        {
            std::vector<int> tempVec = vec;
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(tempVec, 0, vectorSize - 1);
            auto end = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
            std::cout << "Quick Sort - Vector Size: " << vectorSize << ", Execution Time: " << duration << " seconds\n";
        }

        // Add more sorting algorithms as needed

        std::cout << std::endl;
    }

    return 0;
}
