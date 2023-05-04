

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

/*
https://stackoverflow.com/questions/11213326/how-to-convert-a-string-variable-containing-time-to-time-t-type-in-c

            when.tm_year = YY - 1900; //Years from 1900
            when.tm_mon = MM - 1; //0-based
            when.tm_mday = DD; //1 based

            when.tm_hour = hh;
            when.tm_min = mm;
            when.tm_sec = ss;

            //Make sure the daylight savings is same as current timezone.
            time_t now = time(0);
            when.tm_isdst = std::localtime(&now)->tm_isdst;

            //Convert the tm struct to the Linux epoch
            time_t converted;
            converted = mktime(&when);
*/

bool	checkExchangeRate(std::string &exchange)
{
	char	*end;
	double	value = strtod(exchange.c_str(), &end);
	std::cout << " val = " << value << " ";
	if (*end != '\0')
		return false;
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