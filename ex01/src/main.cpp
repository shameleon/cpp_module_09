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

#include "../inc/RPN.hpp"

/* *********************** */
/*  Ex01  RPN              */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		{
			std::string 	input_operation = static_cast <std::string>(argv[1]);
			RPN				to_stack(input_operation);

			try
			{
				to_stack.calculator();
			}
			catch(const std::exception &e)
			{
				std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
				
			}
		}
		break;
	default:
		std::cout << COL_AUB << "./RNP   \"operation\" " << COL_RES << std::endl;
		break;
	}
	return 0;
}

/*

https://wisdomsky.github.io/reverse-polish-notation-js-parser/

*/
