/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:47 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:53 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	this->_btc_db = new std::map<int, double>;
	_valid_db = loadDataBase();
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &other)
{
	*this = other;
	return ;
}

BitcoinExchange::~BitcoinExchange(void)
{
	if (this->_btc_db)
		delete this->_btc_db;
	return ;
}

BitcoinExchange				&BitcoinExchange::operator=(BitcoinExchange &rhs)
{
	(static_cast< void >(rhs));
	return *this;
}

void						BitcoinExchange::printDataBtc(bool full) const
{
	std::cout << "DB size : " << this->_btc_db->size() << " entries" << std::endl;
	if (!full)
		return ;
	std::cout.precision(2);
	std::cout << std::setiosflags(std::ios::fixed);
	for (std::map< int, double>::iterator it = this->_btc_db->begin();
			it != this->_btc_db->end(); ++it)
	{
		std::cout << COL_VIOL << it->first << " : ";
		std::cout << COL_ORANGE << it->second << COL_RES << std::endl;
	}
}

bool						BitcoinExchange::checkDate(int const date)
{
	int		yy = date / 10000;
	int		mm = (date - yy * 10000) / 100;
	int		dd = date - yy * 10000 - mm *100;

	if ( yy < 2009 || yy > 2030 || mm < 1 || mm > 12 || dd < 1 || dd > 31)
		return false;
	if ( mm == 2 && ((yy % 4 != 0 && dd > 28) || (yy % 4 == 0 && dd > 29)))
		return false;
	if ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd == 31 )
		return false;
	return true;
}


bool						BitcoinExchange::loadDataBase(void)
{
	std::ifstream			ifs;
	std::string				line;

	try
	{
		ifs.open(BITCOIN_DATABASE);
		if (!ifs || !ifs.is_open())
			throw std::runtime_error("Error : could not open data file.");
		std::getline(ifs, line);
		if (line.compare("date,exchange_rate") != 0)
			throw std::runtime_error("Error : invalid header line in data file.");
		while (ifs.good() && std::getline(ifs, line))
		{
			int			date, yy, mm, dd;
			double		value;

			int		res = std::sscanf (line.c_str(), "%4d-%2d-%2d,%lf", &yy, &mm, &dd, &value);
			if (res != 4)
				throw std::runtime_error("Error : invalid data format");
			date = yy * 10000 + mm * 100 + dd;
			if (checkDate(date))
				this->_btc_db->insert(std::pair<int, double>(date, value));
				//this->_btc_db[date] = value;
			else
				throw std::runtime_error("Error : date out of range");
		} 
		ifs.close();
		return true;
	}
	catch(const std::exception& e)
	{
		std::cerr << COL_PUR << e.what() << COL_RES << std::endl;
	}
	return false;
}

/* 
public 
 */
void				BitcoinExchange::monetaryValue(std::string const &input_file)
{
	std::ifstream			ifs(input_file.c_str());
	std::string				line;

	try
	{
		if (this->_valid_db == false)
			return ;
		if (!ifs.is_open())
			throw InvalidFileException();
		std::getline(ifs, line);
		if (line.compare("date | value") != 0)
			throw std::runtime_error("Error : invalid header line in input file.");
	}
	catch(const std::exception &e)
	{
		std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
	}
	while (ifs.good() && std::getline(ifs, line))
	{
		try
		{
			int					date, yy, mm, dd;
			double				assets;
			std::string			is_bad_input_format = "Error : bad input format => " + line;
			std::string			is_bad_input_date = "Error : bad input date   => " + line;

			int		res = std::sscanf (line.c_str(), "%4d-%2d-%2d | %lf", &yy, &mm, &dd, &assets);
			if (res != 4)
				throw std::runtime_error(is_bad_input_format);
			date = yy * 10000 + mm * 100 + dd;
			if (date < OLDEST_DATE)
				throw std::runtime_error("Error : bad input => date older than bitcoin");
				// 				std::cerr << "Error bad input => " << line;
			if (!checkDate(date))
				throw std::runtime_error(is_bad_input_date);
			if (assets < 0)
				throw NotPositiveNumberException();
			if (assets > ASSET_MAX)
				throw ToolargeNumberException();
			std::cout << COL_BGRN << line << COL_RES << " => ";
			std::cout << COL_ORANGE << searchKey(date, assets) << COL_RES<< std::endl;
		}
		catch(const std::exception &e)
		{
			std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
		}
	}
	ifs.close();
	return ;
}

double				BitcoinExchange::searchKey(int const &date, double const &assets)
{
	int									key = date;
	bool								found = false;
	int									i = 0;
	std::map<int, double>::iterator		it;

	while (!found && key >= OLDEST_DATE && i < 5)
	{
		it = this->_btc_db->find(key);
		if (it != this->_btc_db->end())
		{
			found = true;
			//this->_btc_db->erase(it);
			return (assets * it->second);
		}
		if (key - (key / 100) * 100 == 1)   // day
		{
			if (key - (key / 10000) * 10000 == 101)   // jan01
				key -= 8870;  // 31-dec of previous year : 20170101 --> 20161231
			else
				key -= 70;
		}
		else
			key--;
		i++;
	}
	return 0;
}

const char				*BitcoinExchange::InvalidFileException::what() const throw()
{
	//std::cerr << //std::string		error_mssg = "Error : bad input => ";
	//error_mssg += mssg;
	return ("Error : could not open input file.");
}

const char				*BitcoinExchange::NotPositiveNumberException::what(void) const throw()
{
	return ("Error : not a positive number.");
}

const char				*BitcoinExchange::ToolargeNumberException::what(void) const throw()
{
	return ("Error : too large a number.");
}

const char				*BitcoinExchange::BadInputException::what() const throw()
{
	//std::cerr << //std::string		error_mssg = "Error : bad input => ";
	//error_mssg += mssg;
	return ("Error : bad input format.");
}

