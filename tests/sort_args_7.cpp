#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib> 	  //std::stdtol
#include <ctime>
#include <algorithm>  // sort

/* binary search range size */
# define THRESHOLD	10

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

void	printOneVector(std::vector< int>  &vec, std::string color)
{
	std::cout << COL_VIOL << std::endl;
	for (std::vector< int> ::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << color << *it << " ";
	std::cout << COL_RES << std::endl;
}

void	printPairedVector(std::vector< std::pair <int, int> > &pairvec)
{
	std::cout << COL_VIOL << std::endl;
	for (std::vector< std::pair <int, int> >::iterator it = pairvec.begin(); it != pairvec.end(); ++it)
	{
		std::cout << COL_GRN2 << it->first << " ";
		std::cout << COL_VIOL << it->second;
		std::cout << COL_YEL << " | ";
	}
	std::cout << COL_RES << std::endl;
}

int		binarySearch(int item, std::vector<int> &vec, int left, int right)
{
	if (right - left > THRESHOLD)
	{
		int		mid = left + (right - left) / 2;
		if (item < vec[mid])
			binarySearch(item, vec, left, mid);
		else if (item > vec[mid])
			binarySearch(item, vec, mid + 1, right);
		else if (item == vec[mid])
			return mid;
	}
	return left;
}

void	binarySearchInsert(std::vector<int> &elements_to_sort, std::vector<int> &vec)
{
	// std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std::endl;
	// printOneVector(elements_to_sort, COL_GRN2);
	// printOneVector(vec, COL_VIOL);
	if (elements_to_sort.size() == 0)
		return;
	std::vector< int> ::iterator it = vec.begin();
	//std::cout << *it << std::endl;
	// it != vec.end() not needed max element is already at the end
	int	left = binarySearch(elements_to_sort.front(), vec, 0, vec.size() - 1);
	it = it + left;
	while (elements_to_sort.front() > *it)
		++it;
	//std::cout << elements_to_sort.front() << " -> " << *it << std::endl;
	vec.insert(it, elements_to_sort.front());
	elements_to_sort.erase(elements_to_sort.begin());
	binarySearchInsert(elements_to_sort, vec);
}

void	pushRightElements(std::vector<int> &elements_to_sort, std::vector<int> &vec,
								std::vector< std::pair<int, int> > &pairvec)
{
	std::vector< std::pair<int, int> >::iterator	it = pairvec.begin();

	vec.push_back(it->first);
	vec.push_back(it->second);
	it++;
	for(; it != pairvec.end(); ++it)
	{
		elements_to_sort.push_back(it->first);
		vec.push_back(it->second);
	}
}

void	sortPairsByRightElement(std::vector< std::pair<int, int> > &sortvec,
								std::vector< std::pair<int, int> > &pairvec)
{
	while (pairvec.size())
	{
		std::vector< std::pair<int, int> >::iterator	it = pairvec.begin();
		std::vector< std::pair<int, int> >::iterator	min_right_element = it;

		for(; it != pairvec.end(); ++it)
			if (it->second < min_right_element->second)
				min_right_element = it;
		sortvec.push_back(std::make_pair(min_right_element->first, min_right_element->second));
		pairvec.erase(min_right_element);
		sortPairsByRightElement(sortvec, pairvec);

	}
}

void	groupElementsBySortedPairs(std::vector<int> &vec,
								std::vector< std::pair<int, int> > &pairvec,
								std::vector<int> &ending_singleton)
{
	std::vector<int>::iterator		elements_to_sort = vec.begin();
	std::vector<int>::iterator		right = vec.begin() + 1;

	for (unsigned long i = 0; i < vec.size() - 1; ++i)
	{
		if (i % 2 == 0)
		{
			if (*elements_to_sort > *right)
				pairvec.push_back(std::make_pair(*right, *elements_to_sort));
			else
				pairvec.push_back(std::make_pair(*elements_to_sort, *right));
		}
		elements_to_sort++;
		right++;
	}
	if (vec.size() % 2 == 1)
		ending_singleton.push_back(*(elements_to_sort));
	//vec.erase(vec.begin(), vec.end());
	vec.clear();
}

void	vecSort(std::vector<int> &vec)
{
	//int     size = vec.size();
	std::vector< std::pair<int, int> >	pairvec, sortvec;
	std::vector<int>					ending_singleton;
	std::vector<int>					elements_to_sort;
	
	groupElementsBySortedPairs(vec, pairvec, ending_singleton);
	//printPairedVector(pairvec);
	sortPairsByRightElement(sortvec, pairvec);
	//printPairedVector(sortvec);
	pushRightElements(elements_to_sort, vec, sortvec);
	if (ending_singleton.size())
		elements_to_sort.push_back(ending_singleton[0]);
	//std::cout << "# # # # # # # # # # # # # # " << std::endl;
	//printOneVector(elements_to_sort, COL_GRN2);
	//printOneVector(vec, COL_VIOL);
	binarySearchInsert(elements_to_sort, vec);
}

/* timed sort function */
void	algo_sort(int argc, char**argv)
{
	int					int_min = 0;
	int					int_max = std::numeric_limits<int>::max();
	std::vector< int >	vec;  // vec(argc - 1);

	//std::cout << "Pushed : ";
	for (int i = 1; i < argc; ++i)
	{
		char		*pEnd;
		long		nb = std::strtol (argv[i], &pEnd, 10);   // base 10
		if (*pEnd != '\0')
			throw std::runtime_error("Error : arguments contains non-digit characters.\n");
		else if (nb > static_cast<long>(int_max))
			throw std::runtime_error("Error : overflow.\n");
		else if (nb < static_cast<long>(int_min))
			throw std::runtime_error("Error : negative number(s) not accepted.\n");
		//std::cout << nb << " ";
		vec.push_back(static_cast<int>(nb));
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
	/************* sorting function *************/ 
	vecSort(vec);
	stop = std::clock();
	// display vector content
	std::cout << COL_ORANGE << "\nAfter : ";
	printOneVector(vec, COL_BLG);
	std::cout << std::endl;
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC;
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

include 0 or not ???

https://www.geeksforgeeks.org/binary-insertion-sort/


// Compare pairs of elements and put largest elements at the front of the array
// Sort the largest elements at the front recursively
// Merge the rest of the array into the front, one item at a time

➜  tests git:(M17m) ✗ ./a.out 9 12 4 0 6 14 7 1 5 2 8 10 13 11 3
Time to process a range of 15 elements :  14 microseconds


./a.out `shuf -i 1-3000 -n 3000 | tr "\n" " "`  
Time to process a range of 3000 elements :  30997 microseconds.  (without binary search)
Time to process a range of 3000 elements :  31319 microseconds.  (with binary search)


*/