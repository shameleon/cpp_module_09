/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:15 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:25 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <iostream>
# include <iomanip>
# include <string>
# include <fstream>
# include <sstream>
# include <iterator>
# include <stdexcept>
# include <ctime>
# include <stdio.h>
# include <cstdlib>

# include "colors.hpp"

class BitcoinExchange
{
	private:
		std::map<int, double>			*_btc_db;
		bool							_valid_db;
		//std::string				_input;

		BitcoinExchange(BitcoinExchange &other);
		BitcoinExchange					&operator=(BitcoinExchange &rhs);

		bool							checkDate(int const date);
		bool							loadDataBase(void);

	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);

		void							printDataBtc(bool full) const;
		void							monetaryValue(std::string const &input_file);

		class		NotPositiveNumberException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

		class		ToolargeNumberException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

		class		BadInputException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

