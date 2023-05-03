

#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>

bool	checkDate(std::string &date)
{
	if (date.length() != 10)
		return false;
	
	return true;
}

bool	checkExchangeRate(std::string &exchange)
{
	//char	*end;
	//double	value = strtod(exchange, &end);
	if (exchange.compare(" ") != 0)
		return true;
	return false;
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