
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

# define BITCOIN_DATABASE	"./cpp_09/data.csv"
# define OLDEST_DATE		20090102
# define ASSET_MIN 			0
# define ASSET_MAX 			1000

# include <map>
# include <iostream>			// std::cout
# include <iomanip>				// std::setiosflags std::setprecision
# include <fstream>				// std::ifstream
# include <limits>  			//  std::numeric_limits
# include <stdexcept>			//  std::exception
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
		double							searchKey(int const &date, double const &assets);
		bool							loadDataBase(void);

	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);

		//std::map<int, double>  			&getDatabase(void) const;
		void							printDataBtc(bool full) const;
		void							monetaryValue(std::string const &input_file);

		class		InvalidFileException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

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

