#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;  // Generating random numbers between 0 and 9999
    }
}

void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// Sorting algorithms implementations...

// Bubble Sort
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Radix Sort
int getMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countingSort(int arr[], int size, int exp) {
    int output[size];
    int count[10] = {0};

    for (int i = 0; i < size; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int size) {
    int max = getMax(arr, size);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, size, exp);
    }
}

int main() {
    const int maxSize = 100000;  // Maximum array size to test
    const int stepSize = 10000;  // Size increment

    cout << setw(15) << "Array Size" << setw(20) << "Merge Sort" << setw(20)
         << "Bubble Sort" << setw(20) << "Quick Sort" << setw(20) << "Radix Sort" << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

    for (int arraySize = stepSize; arraySize <= maxSize; arraySize += stepSize) {
        int* originalArray = new int[arraySize];
        int* tempArray1 = new int[arraySize];
        int* tempArray2 = new int[arraySize];
        int* tempArray3 = new int[arraySize];

        generateRandomArray(originalArray, arraySize);
        copyArray(originalArray, tempArray1, arraySize);
        copyArray(originalArray, tempArray2, arraySize);
        copyArray(originalArray, tempArray3, arraySize);

        auto startTime = chrono::high_resolution_clock::now();
        mergeSort(tempArray2, 0, arraySize - 1);
        auto endTime = chrono::high_resolution_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << setw(15) << arraySize << setw(20) << elapsedTime.count() << " ms";
        //cout << setw(20) << elapsedTime.count() << " ms";

        startTime = chrono::high_resolution_clock::now();
        bubbleSort(tempArray1, arraySize);
        endTime = chrono::high_resolution_clock::now();
        elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << setw(20) << elapsedTime.count() << " ms";
        //cout << setw(15) << arraySize << setw(20) << elapsedTime.count() << " ms";

        

        startTime = chrono::high_resolution_clock::now();
        quickSort(tempArray3, 0, arraySize - 1);
        endTime = chrono::high_resolution_clock::now();
        elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

        cout << setw(20) << elapsedTime.count() << " ms";

        startTime = chrono::high_resolution_clock::now();
        radixSort(tempArray3, arraySize);
        endTime = chrono::high_resolution_clock::now();
        elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

        cout << setw(20) << elapsedTime.count() << " ms" << endl;

        delete[] originalArray;
        delete[] tempArray1;
        delete[] tempArray2;
        delete[] tempArray3;
    }

    return 0;
}
