#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // sort

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
	std::sort(vec.begin(), vec.end());
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


/*

./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`

Time to process a range of 3000 elements with std::sort :  1.132 milliseconds 
Time to process a range of 3000 elements with std::sort :  1152 microseconds 

http://coliru.stacked-crooked.com/a/0d3de457f5ba48b9
average processor time to sort 1000000 integers: 95.3125 millisecs
*/