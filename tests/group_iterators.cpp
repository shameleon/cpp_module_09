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
	vecSort(lst);
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