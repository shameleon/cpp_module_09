/* sorted with list */
/**/

#include <iostream>
#include <list>
#include <list>
#include <limits>
#include <cstdlib> 	  //std::stdtol
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

void	printOneList(std::list< int>  &lst, std::string color)
{
	std::cout << COL_VIOL << std::endl;
	for (std::list< int> ::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << color << *it << " ";
	std::cout << COL_RES << std::endl;
}

void	printPairedList(std::list< std::pair <int, int> > &pairlst)
{
	std::cout << COL_VIOL << std::endl;
	for (std::list< std::pair <int, int> >::iterator it = pairlst.begin(); it != pairlst.end(); ++it)
	{
		std::cout << COL_GRN2 << it->first << " ";
		std::cout << COL_VIOL << it->second;
		std::cout << COL_YEL << " | ";
	}
	std::cout << COL_RES << std::endl;
}

// no subcript overload for lists Random access of elements not possible.
// as list is implemented as a double liked-list (access by traversing through iterators) 
/*
int		binarySearch(int item, std::list<int> &lst, int left, int right)
{
	if (right - left > THRESHOLD)
	{
		int		mid = left + (right - left) / 2;
		if (item < lst[mid])
			binarySearch(item, lst, left, mid);
		else if (item > lst[mid])
			binarySearch(item, lst, mid + 1, right);
		else if (item == lst[mid])
			return mid;
	}
	return left;
}
*/
void	binarySearchInsert(std::list<int> &elements_to_sort, std::list<int> &lst)
{
	// std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std::endl;
	// printOneList(elements_to_sort, COL_GRN2);
	// printOneList(lst, COL_VIOL);
	if (elements_to_sort.size() == 0)
		return;
	std::list< int> ::iterator it = lst.begin();
	//std::cout << *it << std::endl;
	// it != lst.end() not needed max element is already at the end
	//int	left = binarySearch(elements_to_sort.front(), lst, 0, lst.size() - 1);
	//it = it + left;
	while (elements_to_sort.front() > *it)
		++it;
	//std::cout << elements_to_sort.front() << " -> " << *it << std::endl;
	lst.insert(it, elements_to_sort.front());
	elements_to_sort.erase(elements_to_sort.begin());
	binarySearchInsert(elements_to_sort, lst);
}

void	pushRightElements(std::list<int> &elements_to_sort, std::list<int> &lst,
								std::list< std::pair<int, int> > &pairlst)
{
	std::list< std::pair<int, int> >::iterator	it = pairlst.begin();

	lst.push_back(it->first);
	lst.push_back(it->second);
	it++;
	for(; it != pairlst.end(); ++it)
	{
		elements_to_sort.push_back(it->first);
		lst.push_back(it->second);
	}
}

void	sortPairsByRightElement(std::list< std::pair<int, int> > &sortlst,
								std::list< std::pair<int, int> > &pairlst)
{
	while (pairlst.size())
	{
		std::list< std::pair<int, int> >::iterator	it = pairlst.begin();
		std::list< std::pair<int, int> >::iterator	min_right_element = it;

		for(; it != pairlst.end(); ++it)
			if (it->second < min_right_element->second)
				min_right_element = it;
		sortlst.push_back(std::make_pair(min_right_element->first, min_right_element->second));
		pairlst.erase(min_right_element);
		sortPairsByRightElement(sortlst, pairlst);

	}
}

void	groupElementsBySortedPairs(std::list<int> &lst,
								std::list< std::pair<int, int> > &pairlst,
								std::list<int> &ending_singleton)
{
	std::list<int>::iterator		it_left = lst.begin();
	std::list<int>::iterator		it_right = lst.begin();
	++it_right;

	for (unsigned long i = 0; i < lst.size() - 1; ++i)
	{
		if (i % 2 == 0)
		{
			if (*it_left > *it_right)
				pairlst.push_back(std::make_pair(*it_right, *it_left));
			else
				pairlst.push_back(std::make_pair(*it_left, *it_right));
		}
		it_left++;
		it_right++;
	}
	if (lst.size() % 2 == 1)
		ending_singleton.push_back(*(it_left));
	//lst.erase(lst.begin(), lst.end());
	lst.clear();
}

void	listSort(std::list<int> &lst)
{
	std::list< std::pair<int, int> >	pairlst, sortlst;
	std::list<int>					ending_singleton;
	std::list<int>					elements_to_sort;
	
	groupElementsBySortedPairs(lst, pairlst, ending_singleton);
	printPairedList(pairlst);
	sortPairsByRightElement(sortlst, pairlst);
	printPairedList(sortlst);
	pushRightElements(elements_to_sort, lst, sortlst);
	if (ending_singleton.size())
		elements_to_sort.push_back(ending_singleton.front());
	//std::cout << "# # # # # # # # # # # # # # " << std::endl;
	printOneList(elements_to_sort, COL_GRN2);
	printOneList(lst, COL_VIOL);
	binarySearchInsert(elements_to_sort, lst);
}

/* timed sort function */
void	algo_sort(int argc, char**argv)
{
	int					int_min = 0;
	int					int_max = std::numeric_limits<int>::max();
	std::list< int >	lst;

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
		lst.push_back(static_cast<int>(nb));
	}
	std::cout << std::endl;
	// display list content
	std::cout << "Before : " << std::endl;
	for (std::list<int>::iterator it = lst.begin(); 
			it != lst.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	clock_t		start, stop;
	double		delta_t_us = 0;
	start = std::clock();
	/************* sorting function *************/ 
	listSort(lst);
	stop = std::clock();
	// display list content
	std::cout << COL_ORANGE << "\nAfter : ";
	printOneList(lst, COL_BLG);
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


List in C++ stores the elements at the non-contiguous memory location.
 It is considered a doubly linked list internally.

 A list in C++ stores the elements at the contiguous memory location. 
 It is considered to be a type of dynamic array internally.
 
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