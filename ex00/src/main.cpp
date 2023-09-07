/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:34 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:37 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

/* *********************** */
/*  Ex00 Bitcoin exchange  */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
		case 1:
			std::cout << COL_LRED << "Argument missing : ./btc filename " << COL_RES << std::endl;
			return 1;
		case 2:
			try
			{
				std::string			input_file = static_cast <std::string>(argv[1]);
				BitcoinExchange		mbtc;

				mbtc.printDataBtc(0);
				mbtc.showMonetaryValues(input_file);			
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		default:
			std::cout << COL_LRED << "Error : too many arguments" << COL_RES << std::endl;
			return 1;
	}
	return 0;
}

/*

Subject :

You have to create a program which outputs the value of a certain amount of bitcoin
on a certain date.
This program must use a database in csv format which will represent bitcoin price
over time. This database is provided with this subject.
The program will take as input a second database, storing the different prices/dates
to evaluate.
Your program must respect these rules:
• The program name is btc.
• Your program must take a file as argument.
• Each line in this file must use the following format: "date | value".
• A valid date will always be in the following format: Year-Month-Day.
• A valid value must be either a float or a positive integer between 0 and 1000.
You must use at least one container in your code to validate this
exercise. You should handle possible errors with an appropriate
error message



std::map

Associative
    Elements in associative containers are referenced by their key and not by their absolute position in the container.
Ordered
    The elements in the container follow a strict order at all times. All inserted elements are given a position in this order.
Map
    Each element associates a key to a mapped value: Keys are meant to identify the elements whose main content is the mapped value.
Unique keys
    No two elements in the container can have equivalent keys.
Allocator-aware
    The container uses an allocator object to dynamically handle its storage needs. 



input.txt

date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648
2008-12-14 | 1.42
2022-12-14 | 3.21
2018/02-03 | 1
2018-02-30 | 1
2018-02-03 | 0
2018-02-03 | 1002
2022-03-29 | 0.1
2022-04-01 | 0.1
2022-04-03 | 0.1

*/
