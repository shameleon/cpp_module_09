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

Bitcoin exchange rate.

### Usage

`cd ex00 && make` : will compile and `./btc` executable is ready !

If `data.csv` and  `ìnput.csv` are **Not** present in `ex00/cpp_09` directory :
`make data` can **wget** the necessary .tgz ressource from intra42 URL.
if link is broken, either update URL or place cpp_09.tgz. In both cases,`data` rule will uncompress the ressource and install required files.

To execute :
```shell
➜ ./btc ./cpp_09/input.txt
```

Output :
```
Bitcoin DB size : 1612 entries

2011-01-03 | 3 => 0.9
2011-01-03 | 2 => 0.6
2011-01-03 | 1 => 0.3
2011-01-03 | 1.2 => 0.36
2011-01-09 | 1 => 0.32
Error : not a positive number.
Error : bad input format => 2001-42-42
2012-01-11 | 1 => 7.1
Error : too large a number.
Error : bad input => date older than bitcoin
2022-12-14 | 0.21 => 9894.35
Error : bad input format => 2018/02-03 | 1
Error : bad input date   => 2018-02-30 | 1
2018-02-03 | 0 => 0
Error : too large a number.
2022-03-29 | 0.1 => 4711.59
```

### Bitcoin exchange database to calculate asset monetary value

A file containing **Bitcoin** price over time, has to be read, parsed and stored in a `database`.
The `date` format has to be pratical for sorting. I chose to convert dates to an integer fomat `YYYYMMDD` instead of using `std:string`.
The `std::map` container was found to be very suitable for a database that has to be sorted in a chronological manner, associating each date to the corresponding bitcoin value : 
```std::map<int, double>``` as attribute of ```BitcoinExchange``` class.
Indeed, The C++ `std::map` is a **sorted associative container** that contains key-value pairs.
[map to file](https://marketsplash.com/tutorials/cpp/cplusplus-map-to-file/)

In a second time, another file has to be read, providing a date and an amount of bitcoins.
The `monetary value` for that **date:amount pair** has to be found, accordingly to the bitcoin exchange rate.
`Exceptions` are thrown with explict `error messages` if there is any problem either with the date or the bitcoin asset quantity.
Ultimately, bitcoin value at a certain date is calculated based on the most recent bitcoin value in the database.

## ex01 • RPN calculator

_Reverse polish notation_ (RPN) 
Explanations and example of an [online RNP calculator](https://www.dcode.fr/reverse-polish-notation)

### Usage 

```make``` to compile and obtain `.RPN` executable.

A **unique string argument** , provided as a unique argument to **./RPN** executable. That argument string is a sequence of single-digit numbers and arithmetic operations. 

```shell
➜ ./RPN "2 4 + 1 - 5 *"
25
```
Of course, invalid sequences will output error messages.

```shell
➜ ./RPN "2 4 + 1"
Error : missing operator(s). 
```

```shell
➜ ./RPN "2 4 1 +"
Error : missing operand(s). 
```

```shell
➜ ./RPN "4 2 2 - /"
Error : Division by zero. 
```

## RPN stack mechanism
The argument string is parsed from left to right. 
If a digit is found, it is `pushed` as an `int` to a `stack`, which is a
`std::deque<int>` container.	
If a `operation` is found. Two numbers are `popped` from the stack and serve as operands for the operation.
The result is `pushed`, thus being at the top of the stack.
The final result is printed on stdout only if there is only one remaining number at the end of the argument parsing.

## ex02 • PmergeMe

PMergeMe is an array **sorting problem**. A `sequence of positive integers` is provided as arguments to `.PMergeMe`.
The sequence are to be placed
`./PMergeme` must sort the sequence with the `Ford-Johnson algorithm`, using two different container types, not used in previous exercises.

### Usage

`make` for compilation.
Then 
```shell
➜ ./PMergeMe 2 3 5 0 1 4
```

### Subject
The name of the program is PmergeMe.
• Your program must be able to use a positive integer sequence as argument.
• Your program must use a merge-insert sort algorithm to sort the positive integer
sequence.
• If an error occurs during program execution, an error message should be displayed
on the standard output.
You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.
It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.

A scrambled sequence of the 3000 first positive integers:

```shell
./PMergeMe `shuf -i 1-3000 -n 3000 | tr "\n" " "`
```

### Ford-Johnson algorithm

`Merge-insertion sort` or the `Ford–Johnson` algorithm is a comparison sorting algorithm published in 1959 by L. R. Ford Jr. and Selmer M. Johnson.
    Ford, Lester R., Jr.; Johnson, Selmer M. A tournament problem. Amer. Math. Monthly 66 (1959), 387–389.

[wikipedia : merge-insertion sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)

[merge-insertion-sort in Java](https://iq.opengenus.org/merge-insertion-sort/)


Other links for better understanding of other soring algorithms :

[insert sort](https://www.programiz.com/dsa/insertion-sort)

[merge sort](https://www.programiz.com/dsa/merge-sort)

[binary search](https://www.tutorialspoint.com/binary-insertion-sort-in-cplusplus)

### Mechanism

In brief:

• The unsorted sequence is `grouped into pairs`. if the sequence length is an odd number `2k + 1`, the last unpaired element is kept aside as `ending_singleton`.

• Each pair is sorted ascendingly such as `sorted pair` $A_i | B_i$ has $A_i <= B_i$. There are k pairs to sort (k comparisons).

• Pairs are ascendingly sorted by their right element $B_i$.
$A_1 | B_1   A_2 | B_2 ... A_k | B_k$

• At this stage $B_i$ elements, which are already sorted, and pushed to the final container : $B_1   B_2 ... B_k$

• Left elements $A_1 A_2... A_k$ are taken one by one, starting from the `front`, and inserted after a `binary search` into the  final container. Not forgetting the kept aside `ending_singleton`.

$A_1$ being smaller than $B_1$ and of all $B_1   B_2 ... B_k$, can be pushed to the front : $A_1 B_1   B_2 ... B_k$

Example:

```
unsorted     9 7 1 5 8 3 6 2 4
pairs      9 2    1 5    8 3    6 7    4
swap_sort  2 9    1 5    3 8    6 7    4      4 comparisons
sort_2     1 5    6 7    3 8    2 9    4      5 comparisons

sorted                  to sort
     5 7 8 9            1 6 3 2 4  
   1 5 7 8 9              6 3 2 4         0 comparisons
   1 5 6 7 8 9              3 2 4         2 comparisons
   1 3 5 6 7 8 9              2 4         2 comparisons
   1 2 3 5 6 7 8 9              4         2 comparisons
   1 2 3 5 6 7 8 9              4         4 comparisons

total : 19 comparisons for 9-element sequence
```

There is no binary search for such small sequence.
`binary search` is activated only above a chosen threshold, that cna be optimized. 

Excellent explanation here, about `minimizing comparisons` plus links therein (such as Jacobsthal numbers) : 
[decidedlys readme.md](https://github.com/decidedlyso/merge-insertion-sort/blob/master/README.md)

### Vector or List 

Two types of containers have to be compared, with the the `timed` implementation of the mandatory F-J sorting algorithm.

```C++
std::vector<int>		*_pvec;
std::list<int>			*_plist;
```

For longer sequences, in my hands, ```std::vector``` seems to be faster than ```std::list```. 
Vector is a ```random access``` container, ```Contigous memory```.

Some good explanations are found here. 
[Using C++ containers efficiently](https://blog.quasar.ai/using-c-containers-efficiently)
