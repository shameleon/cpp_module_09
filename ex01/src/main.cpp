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

#include "../inc/Rpn.hpp"

/* *********************** */
/*  Ex01  RPN              */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		try
		{
			std::string  input_operation = static_cast <std::string>(argv[1]);
			Rpn		my_rpn(input_operation);
		}
		catch(const Rpn::RpnErrorException  &e)
		{
			std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
		}
		break;
	default:
		std::cout << COL_AUB << "./RPN \"operation\" " << COL_RES << std::endl;
		break;
	}
	return 0;
}

/*

*/
