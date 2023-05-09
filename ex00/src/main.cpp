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
	case 2:
		{
			std::string			input_file = static_cast <std::string>(argv[1]);
			BitcoinExchange		mbtc;

			try
			{
				mbtc.printDataBtc(false);
				mbtc.monetaryValue(input_file);
			}
			catch(const std::exception  &e)
			{
				std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
				
			}
		}
		break;
	default:
		std::cout << COL_AUB << "Error: could not open file" << COL_RES << std::endl;
		break;
	}
	return 0;
}

/*
./btc ../cpp_09_tgz/input.txt 

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

*/
