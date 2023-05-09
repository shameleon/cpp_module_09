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
	this->_btc_bd = new std::map<const int, double>;
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &other)
{
	*this = other;
	return ;
}

BitcoinExchange::~BitcoinExchange(void)
{
	if (this->_mstack)
		delete this->_mstack;
	return ;
}

BitcoinExchange				&BitcoinExchange::operator=(BitcoinExchange &rhs)
{
	(static_cast< void >(rhs));
	return *this;
}

// precision issue 
bool						BitcoinExchange::checkExchangeRate(std::string &exchange)
{
	char					*end;
	double					value = strtod(exchange.c_str(), &end);

	std::cout << " strtod=" << value << " ";
	if (*end != '\0')
		return false;
	if (value < 0 )  // inf nan 
		return false;
	return true;
}

bool						BitcoinExchange::checkExchangeRate2(std::string &exchange)
{
	std::stringstream		ss;

	ss << exchange;
	double	value;
	ss >> value;
	std::cout << " ss=" << value << " ";
	if (value < 0 )  // inf nan 
		return false;
	return true;
}


bool						BitcoinExchange::loadDataBase(void)
{
	std::ifstream			datafile("../cpp_09_tgz/data.csv");
	std::string				line;

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
				std::string			exchange;
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
	return true;
}

void						BitcoinExchange::popTwo_calculate_push(char &c)
{
	if (this->_mstack->size() < 2)
		throw (BitcoinExchange::BitcoinExchangeErrorException());
	int 	operand1 = this->_mstack->top();
	this->_mstack->pop();
	int 	operand2 = this->_mstack->top();
	this->_mstack->pop();
	switch (static_cast< int >(c))
	{
	case MULTIPLY:
		operand2 *= operand1;
		break;
	case ADD:
		operand2 += operand1;
		break;
	case SUBSTRACT:
		operand2 -= operand1;
		break;
	case DIVIDE:
		if (operand1)
			operand2 /= operand1;
		else
			throw (BitcoinExchange::BitcoinExchangeErrorException());
		break;
	default:
		break;
	}
	this->_mstack->push(operand2);
	return ;
}

/* parses input string :
digit is pushed to stack
operator token => pop two calculate the push result
 */
void				BitcoinExchange::monetaryValue(void)
{
	return ;
}

const char				*BitcoinExchange::NotPositiveNumberException::what(void) const throw()
{
	return ("Error : not a positive number.");
}

const char				*BitcoinExchange::ToolargeNumberException::what(void) const throw()
{
	return ("Error : too large a number.");
}

const char				*BitcoinExchange::BadInputException::what(std::string &date) const throw()
{
	std::string		error_mssg;
	error_mssg = "Error : bad input => ";
	return (error_mssg + date);
}

