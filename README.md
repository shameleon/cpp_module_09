# cpp_module_09

## ex 00 : Bitcoin
A `std::map` is a container that stores key-value pairs, where each key maps to a unique value. 

![map to file](https://marketsplash.com/tutorials/cpp/cplusplus-map-to-file/)

## ex 01 : RPN calculator

## ex 02 : PmergeMe 
![merge insert sort in Java](https://iq.opengenus.org/merge-insertion-sort/)

merge insert sort in C++

To combine merge sort and insertion sort in C++, you can apply a hybrid approach where you use merge sort for larger arrays and switch to insertion sort when the size of the subarray falls below a certain threshold. This can improve the performance of the sorting algorithm, as insertion sort is more efficient for smaller arrays.

Here's a step-by-step guide to implementing the hybrid merge-insert sort:

    Implement the insertion sort function:

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

    Modify the merge sort function to incorporate the insertion sort:

void mergeInsertSort(int arr[], int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
        // Use insertion sort for small subarrays
        insertionSort(arr, left, right);
    } else {
        // Continue with merge sort
        int mid = left + (right - left) / 2;
        mergeInsertSort(arr, left, mid, threshold);
        mergeInsertSort(arr, mid + 1, right, threshold);
        merge(arr, left, mid, right);
    }
}

    Determine the threshold value:

You can experiment with different threshold values, but a common choice is around 10 to 20 elements. For example, you can set the threshold to 15:

int main() {
    int arr[] = {6, 5, 12, 10, 9, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int threshold = 15;
    mergeInsertSort(arr, 0, size - 1, threshold);
    printArray(arr, size);
    return 0;
}

Pros of hybrid merge-insert sort:

    It takes advantage of the efficiency of insertion sort for smaller arrays and merge sort for larger arrays.
    The overall performance of the sorting algorithm can be improved.

Cons of hybrid merge-insert sort:

    The code becomes more complex as it requires two different sorting algorithms.
    Determining the optimal threshold value may require experimentation.

In conclusion, combining merge sort and insertion sort in C++ can lead to a more efficient sorting algorithm, particularly for smaller arrays. By using merge sort for larger arrays and switching to insertion sort when the size of the subarray falls below a certain threshold, you can improve the performance of the sorting algorithm geeksforgeeks.org, programiz.com.
