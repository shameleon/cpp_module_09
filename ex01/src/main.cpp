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

#include "../inc/RNP.hpp"

/* *********************** */
/*  Ex01  RNP              */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		try
		{
			std::string  input_operation = static_cast <std::string>(argv[1]);
			RNP		my_RNP(input_operation);
		}
		catch(const RNP::RNPErrorException  &e)
		{
			std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
		}
		break;
	default:
		std::cout << COL_AUB << "./RNP \"operation\" " << COL_RES << std::endl;
		break;
	}
	return 0;
}

/*
https://wisdomsky.github.io/reverse-polish-notation-js-parser/

"z 3 3 +"      ===>invalid
"   3 5 + 4-"  ===> 4
"5 1 1 1---"   ===> 3 
"5    2 +7/"   ===> 1
"5 2 + 1 3 * +" ====> 10
"5 2 + 1 3 * *"  ===> 21
5 2 1 3 + * + === 13
*/
