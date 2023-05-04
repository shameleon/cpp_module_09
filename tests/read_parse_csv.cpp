

#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>

typedef struct e_yyyymmdd
{
	int		y;
	int		m;
	int		d;
}					t_ymd;

int	main(void)
{
	std::ifstream					datafile("../cpp_09_tgz/data.csv");
	std::map <int, double>		bitcoin_db;
	std::string						line;

	try
	{
		if (!datafile.is_open())
			throw std::runtime_error("Error opening output file");
		std::getline(datafile, line);
		if (line.compare("date,exchange_rate") != 0)
			throw std::runtime_error("Error Invalid file header (line 0)");
		while (std::getline(datafile, line))
		{
			t_ymd	dt;
			int		date;
			double  val;
			int		res = std::sscanf (line.c_str(), "%4d-%2d-%2d,%lf", &dt.y, &dt.m, &dt.d, &val);
			if (res != 4)
				throw std::runtime_error("Error : database format");
			// checkValidDate(dt);
			// checkValidDate(dt);
			date = dt.y * 10000 + dt.m * 100 + dt.d;
			//std::cout << res << " | " << date << " | " << val << std::endl;
			bitcoin_db[date] = val;
		}
		datafile.close();
		std::cout << "DB size = " << bitcoin_db.size() << " entries" << std::endl;
		int		key1 = 20220326;
		if (key1 < 20090102)
			throw std::runtime_error("Error : bitcoin did not exist at that time");
		bool	found = false;
		while (!found || key1 < 20090102)
		{
			if (42)
			{
				//std::cout << key1 << "   " << key1 - (key1 / 100) * 100;
				//std::cout << " " << (key1 - (key1 / 10000) * 10000) << std::endl;
				std::map<int, double>::iterator it;
				it = bitcoin_db.find (key1);
				if (it != bitcoin_db.end())
				{
					found = true;
					std::cout << it->first << " : " << it->second << std::endl;
					// return second to get exchange value
					bitcoin_db.erase(it);
					return 0;
				}
			}
			if (key1 - (key1 / 100) * 100 == 1)   // day
			{
				if (key1 - (key1 / 10000) * 10000 == 101)   // jan01
					key1 -= 8870;  // 31-dec of previous year 20170101 --> 20161231
				else
					key1 -= 70;
			}
			else
				key1--;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}


/*
https://en.cppreference.com/w/cpp/io/c/fscanf
*/