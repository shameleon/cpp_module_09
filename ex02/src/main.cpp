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

#include "../inc/PmergeMe.hpp"

/* *********************** */
/*  Ex02 PMergeMe          */
/* *********************** */

int					main(int argc, char **argv)
{
	switch (argc)
	{
	case 1:
		std::cerr << COL_BRED << "Error : arguments missing. No positive integer arguments to sort" << COL_RES << std::endl;
		break;
	case 2:
		std::cerr << COL_BRED << "Error : only a one-integer argument was provided, nothing to be sorted" << COL_RES << std::endl;
		break;
	default:
		try
		{
			PmergeMe		pmerge(argc, argv);
			pmerge.timedSort();
		}
		catch(const std::exception &e)
		{
			std::cerr << COL_BRED << e.what() << COL_RES << std::endl;
			
		}
		break;
	}
	return 0;
}

/*
./PmergeMe `shuf -i 1-3000 -n 3000 | tr "\n" " "`

Subject
The name of the program is PmergeMe.
• Your program must be able to use a positive integer sequence as argument.
• Your program must use a merge-insert sort algorithm to sort the positive integer
sequence.
• If an error occurs during program execution, an error message should be displayed
on the standard output.
You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.
It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.

*/
