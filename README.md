# cpp_module_09

Validated in Jun 2023 with Grade 100 and one ```outstanding work``` rating.

_cpp_module_09_ is the 10th and last module of 42 school C++ piscine.
It emphasizes on the use of `containers` and `iterators`. 
Each container type must be used **only once** to solve 3 independent problems.

||problem| solution|
|---|---|---|
|ex00| [Bitcoin](./ex00) |`std::map` container to store key-value pairs|
|ex01| [RPN calculator](./ex01)|`std::deque` container to stack numbers|
|ex02| [PmergeMe](.ex/02)|`std::vec` and `std:list` to sort number sequences|

## ex00 • Bitcoin

A file containing **Bitcoin** price over time, has to be read, parsed and stored in a `database`.
The `date` format has to be adapted for sorting. I chose to convert dates to an integer fomat `YYYYMMDD` instead of using std:strings.
The `std::map` container was found to be very suitable for a database sorted in a chronological manner, associating each date to the corresponding bitcoin value,  
Indeed, The C++ `std::map` is a **sorted associative container** that contains key-value pairs.
[map to file](https://marketsplash.com/tutorials/cpp/cplusplus-map-to-file/)

In a second time, another file has to be read, providing a date and an amount of bitcoins.
The `monetary value` for that date:amount pair has to be found. 
`Exceptions` are thrown with explict `error messages` if there is any problem either with the date or the bitcoin amount.
Ultimately, bitcoin value at a certain date is calculated based on the most recent bitcoin value in the database.

## ex01 • RPN calculator

A string sequence of single-digit numbers and arithmetic operations are provided as a unique argument to **RPN** executable.

```./RPN "2 4 + 1 - 5 *"```

The argument string is parsed from left to right. 
If a digit is found it is `pushed` as an `int` to a `stack`. 
If a `operation` is found. Two numbers are `popped` from the stack and serve as operands for the operation.
The result is `pushed`, thus being at the top of the stack.
The final result is printed on stdout only if there is only one remaining number at the end of the argument parsing.

## ex02 • PmergeMe

PMergeMe is an array sorting problem. a sequence of positive integers is provided as arguments.
The sequence are to be placed
PMergeme must sort the sequence with the `Ford-Johnson Merge-insert algorithm`.
Two types of containers have to be compared, and the implementation of the sorting algorithm 

![insert sort](https://www.programiz.com/dsa/insertion-sort)

![merge sort](https://www.programiz.com/dsa/merge-sort)

![binary search](https://www.tutorialspoint.com/binary-insertion-sort-in-cplusplus)

![wikipedia : merge-insertion sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)
`Merge-insertion sort` or the `Ford–Johnson` algorithm is a comparison sorting algorithm published in 1959 by L. R. Ford Jr. and Selmer M. Johnson.
    Ford, Lester R., Jr.; Johnson, Selmer M. A tournament problem. Amer. Math. Monthly 66 (1959), 387–389.

![merge insert sort in Java](https://iq.opengenus.org/merge-insertion-sort/)


https://cplusplus.com/forum/beginner/115630/


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
