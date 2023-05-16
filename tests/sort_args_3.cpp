#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // sort


void	printVector(std::vector<int> &vec)
{
	for (std::vector<int>::iterator it = vec.begin(); 
		it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
//void	binaryInsertSort(std::vector<int> &vec, int left, int right)

void		insertionSort(std::vector<int> &vec, int left, int right)
{
	std::vector<int>::iterator		ileft = vec.begin() + left;
	std::vector<int>::iterator		it;
	std::vector<int>::iterator		sel;
	int								key;

	for (sel = ileft + 1; sel <=  ileft + right; ++sel)
	{
		key = *sel;
		it = sel - 1;
		 while (it >= ileft && *it > key)
		 {
			*(it + 1) = *it;
			printVector(vec);
			it--;
		 }
		 *(it + 1) = key;
	}
	return ;
}

void	mergeInsertSort(std::vector<int> &vec, int left, int right,  int threshold)
{
	// use insertion sort for small subvectors
	if (right - left + 1 <= threshold)
		insertionSort(vec, left, right);
		//BinaryInsertionSort(vec, left, right);
	else
	{
		int     mid = left + (right - left) / 2;
		mergeInsertSort(vec, left, mid, threshold);
		//printVector(vec);
		mergeInsertSort(vec, mid + 1, right, threshold);
		mergeInsertSort(vec, left, mid, right);
	}
}

void	vecSort(std::vector<int> &vec)
{
	int     threshold = 10;
	int     size = vec.size();
	mergeInsertSort(vec, 0, size -1, threshold);
}

/* timed sort function */
void	algo_sort(int argc, char**argv)
{
	int		int_min = 0;
	int		int_max = std::numeric_limits<int>::max();
	std::vector< int >	vec;  // vec(argc - 1);

	std::cout << "Pushed : ";
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
	for (std::vector<int>::iterator it = vec.begin(); 
			it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << "Time to process a range of " << (argc - 1) << " elements with std::sort :  ";
	std::cout << delta_t_us << " microseconds \n";
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
