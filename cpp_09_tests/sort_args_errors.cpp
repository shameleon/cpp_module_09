#include <iostream>
//#include <iomanip>
//#include <sstream>
#include <vector>
#include <limits>
#include <cstdlib>			//std::stdtol
#include <ctime>
//#include <algorithm>  // sort

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

void	parse_sequence(int argc, char**argv)
{
	// parse arguments to vector
	int		int_min = 0;
	int		int_max = std::numeric_limits<int>::max();
	std::vector< int >	vec;  // vec(argc - 1);

	for (int i = 1; i < argc; ++i)
	{
		std::string			str1 = argv[i];
		char 				*pEnd;
		long nb = std::strtol (argv[i], &pEnd, 10);
		if (*pEnd != '\0')
			throw std::runtime_error("Error : arguments contains non-digit characters.");
		else if (nb > static_cast<long>(int_max))
			throw std::runtime_error("Error : overflow.");
		else if (nb < static_cast<long>(int_min))
			throw std::runtime_error("Error : negative number(s) not accepted.");
		vec.push_back(nb);
	}
	// display vector content
	std::cout << "Before : ";
	for (std::vector<int>::iterator it = vec.begin(); 
		it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// copy from vector to ...

	clock_t		start, stop;
	double		delta_t_us = 0;
	start = std::clock();
	// sort function
	//vecSort(vec);
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
	default:
		try
		{
			parse_sequence(argc, argv);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		break;
	}
	return 0;
}