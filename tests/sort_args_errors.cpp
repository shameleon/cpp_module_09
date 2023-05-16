#include <iostream>
#include <sstream>
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

void	algo_sort(int argc, char**argv)
{
	//int		int_min = 0;
	//int		int_max = std::numeric_limits<int>::max();
	std::vector< int >	vec;  // vec(argc - 1);

	try
	{
		for (int i = 1; i < argc; ++i)
		{
			std::stringstream	ss;
			int					nb;

			ss << argv[i];
			ss >> nb;
			if (nb < 0)
				throw std::runtime_error("Error : negative number(s) not accepted.");

			vec.push_back(nb);
		}
		std::cout << std::endl;
		for (std::vector<int>::iterator it = vec.begin(); 
			it != vec.end(); ++it)
			std::cout << *it << " ";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

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