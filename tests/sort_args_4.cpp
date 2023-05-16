#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // sort

/* colors */
# define COL_RED    "\e[0;31m"
# define COL_BRED	"\e[1;31m"
# define COL_GRN    "\e[0;32m"
# define COL_BGRN	"\e[1;32m"
# define COL_YEL	"\e[0;33m"
# define COL_BLU	"\e[0;34m"
# define COL_PUR	"\e[0;35m"
# define COL_CYA	"\e[0;36m"
# define COL_GRN2	"\e[38:5:02m"
# define COL_BLG	"\e[38:5:74m"
# define COL_AUB	"\e[38:5:104m"
# define COL_ORANGE	"\e[38:5:214m"
# define COL_VIOL   "\e[38:5:198m"
# define COL_LRED  "\e[38:5:160m"
# define COL_RES	"\e[0m"


void	printVector(std::vector<int> &vec, int left, int right)
{
	//std::cout << COL_ORANGE << std::endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if (it == vec.begin() + left)
			std::cout << COL_GRN2;
		if (it == vec.begin() + right + 1)
			std::cout << COL_RES;
		std::cout << *it << " ";
	}
	std::cout << COL_RES << std::endl;
}

void	printTwoVectors(std::vector<int> &vec, int left, int mid, int right)
{
	std::cout << COL_BLG;
	for (std::vector<int>::iterator it = vec.begin() + left; 
		it != vec.begin() + mid + 1 ; ++it)
		std::cout << *it << " ";
	std::cout << COL_RES << COL_AUB;
	for (std::vector<int>::iterator it = vec.begin() + mid + 1; 
		it != vec.begin() + right + 1; ++it)
		std::cout << *it << " ";
	std::cout << COL_RES << std::endl;
	return;
}

//void	binaryInsertSort(std::vector<int> &vec, int left, int right)
// can be recursive : https://www.geeksforgeeks.org/insertion-sort/
void		insertionSort(std::vector<int> &vec, int left, int right)
{
	std::vector<int>::iterator		it;
	std::vector<int>::iterator		sel;
	int								key;

	//std::cout << "insert " << left << "-" << right; 
	for (sel = vec.begin() + left + 1; sel !=  vec.begin() + right + 1; ++sel)
	{
		key = *sel;
		//std::cout << COL_YEL << " " << (sel - vec.begin()) << ":" << key; 
		it = sel - 1;
		 while (it >= vec.begin() + left && *it > key)
		 {
			*(it + 1) = *it;
			//printVector(vec);
			it--;
		 }
		 *(it + 1) = key;
	}
	//std::cout << COL_RES << std::endl;
	return ;
}

/* each pair is sorted */
void	pairSort(std::vector<int> &vec, int left, int right )
{
	int		tmp;

	if (right -left == 1 && vec[left] > vec[right])
	{
		//std::cout << "sort" << left << "<>" << right << "\n";
		tmp = vec[right];
		vec[right] = vec[left];
		vec[left] = tmp;
	}
}


void	merge(std::vector<int> &vec, int left, int right)
{
	// Create L ← A[p..q] and M ← A[q+1..r]
	//std::vector < pair <int, int> >	vip;
	//std::vector<int>	rightarm;

	//printTwoVectors(vec, left, mid, right);
	insertionSort(vec, left, right);
	//printVector(vec, left, right);
	//std::cout << COL_RES << std::endl;
	return;
}

void	mergeSort(std::vector<int> &vec, int left, int right)
{
	// divide until size 2 or less 
	if (left < right)
	{
		// middle point = where to divide 
		int     mid = left + (right - left) / 2;
		//std::cout << left << "-" << mid << "  " << mid + 1 << "-" << right << std::endl;
		pairSort(vec, left, right);
		mergeSort(vec, left, mid);
		mergeSort(vec, mid + 1, right);
		// Merge the sorted vectors
		merge (vec, left, right);
	}
}

void	vecSort(std::vector<int> &vec)
{
	int     size = vec.size();
	mergeSort(vec, 0, size -1);
}

/* timed sort function */
void	algo_sort(int argc, char**argv)
{
	int		int_min = 0;
	int		int_max = std::numeric_limits<int>::max();
	std::vector< int >	vec;  // vec(argc - 1);

	//std::cout << "Pushed : ";
	for (int i = 1; i < argc; ++i)
	{
		char *pEnd;
		long ln = std::strtol (argv[i], &pEnd, 10);   // base 10
		// if pEnd
		if (ln < static_cast<long>(int_min) || ln > static_cast<long>(int_max))
		{
			std::cerr << "invalid input \n" << std::endl;
			return ;
		}
		std::cout << ln << " ";
		vec.push_back(static_cast<int>(ln));
	}
	std::cout << std::endl;
	// display vector content
	std::cout << "Before : ";
	for (std::vector<int>::iterator it = vec.begin(); 
			it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	clock_t		start, stop;
	double		delta_t_us = 0;
	start = std::clock();
	// sort function
	vecSort(vec);
	stop = std::clock();
	// display vector content
	std::cout << "After : ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << COL_ORANGE << "Time to process a range of " << (argc - 1) << " elements :  ";
	std::cout << delta_t_us << " microseconds." << COL_RES << std::endl;
}

int		main(int argc, char**argv)
{
	switch (argc)
	{
	case 1:
		std::cout << "arguments missing" << std::endl;
		return 0;
	case 2:
		std::cout << argv[1] << std::endl;
		return 0;
	default:
		algo_sort(argc, argv);
		break;
	}
	return 0;
}


/*
./a.out `shuf -i 1-3000 -n 3000 | tr "\n" " "`

merge sort hybrid not exactly Ford Johnson

Time to process a range of 100 elements  with mergeSort4 :    113 microseconds.
Time to process a range of 100 elements with std::sort   :     23 microseconds 

Time to process a range of 3000 elements with mergeSort4 :  65616 microseconds.
Time to process a range of 3000 elements with std::sort  :    870 microseconds 


*/