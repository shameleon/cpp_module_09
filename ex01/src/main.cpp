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
/*  Ex01  RNP              */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		{
			std::string  input_operation = static_cast <std::string>(argv[1]);
			RPN		to_stack(input_operation);
			try
			{
				to_stack.calculator();
			}
			catch(const RPN::RPNErrorException  &e)
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

"8 9 * 9 - 9 - 9 - 4 - 1 +"  ===> 42
"  1 "    ====> 1 ?
"7 6 3 *-" ====> -11
"  6 2 / 2 4 + 5 - +" ==> 4
"z 3 3 +"      ===>invalid
"   3 5 + 4-"  ===> 4
"5 1 1 1---"   ===> 3 
"5    2 +7/"   ===> 1
"5 2 + 1 3 * +" ====> 10
"5 2 + 1 3 * *"  ===> 21
5 2 1 3 + * + === 13
*/
