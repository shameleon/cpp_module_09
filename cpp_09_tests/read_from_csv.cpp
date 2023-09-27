

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

bool	checkDate(std::string &date)
{
	if (date.length() != 10)
		return false;
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7) 
		{
			if (date[i] != '-')
				return false;
		}
		else if (!isdigit(date[i]))
			return false; 
	}
	//int		year, month, day;
	//struct tm	when;
	//memset(&tm, 0, sizeof(tm));
	//int res = swscanf(date.c_str(), L"%d-%d-%d", &year, &month, &day);
	//In case datetime was in bad format, returns 0.
	//if (res == EOF || res == 0)
	//	return false;
	//when.tm_year = year -1900;
	//when.tm_mon = month - 1;
	//when.tm_mday = day;

	return true;
}

// precision issue 
bool	checkExchangeRate(std::string &exchange)
{
	char	*end;
	double	value = strtod(exchange.c_str(), &end);
	std::cout << " strtod=" << value << " ";
	if (*end != '\0')
		return false;
	if (value < 0 )  // inf nan 
		return false;
	return true;
}

bool	checkExchangeRate2(std::string &exchange)
{
	std::stringstream	ss;
	ss << exchange;
	double	value;
	ss >> value;
	std::cout << " ss=" << value << " ";
	if (value < 0 )  // inf nan 
		return false;
	return true;
}

int	main(void)
{
	std::ifstream					datafile("../cpp_09_tgz/datatest.csv");
	std::map <std::string, double>	bitcoin_db;
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
			std::stringstream				ss(line);
			if (ss.good())
			{
				std::string		date;
				std::getline(ss, date, ',');
				if (!checkDate(date))
					throw std::runtime_error("Error Date format");
				std::cout << date << "......"; 
				std::string		exchange;
				std::getline(ss, exchange);
				if (!checkExchangeRate(exchange))
					throw std::runtime_error("Error Exchange Rate format");
				if (!checkExchangeRate2(exchange))
					throw std::runtime_error("Error Exchange Rate format");
				std::cout << exchange << std::endl;
			
			}
		}
		datafile.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}