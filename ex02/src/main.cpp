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
		std::cerr << COL_BRED << "Error : arguments missing" << COL_RES << std::endl;
		break;
	case 2:
		std::cout << argv[1] << std::endl;
		return 0;
	default:
		PmergeMe		pmerge(argc, argv);
		break;
	}
	return 0;
}

/*
issues :
1- constructor by copy and copy assignement operator=
2 - if (ln < int_min || ln > int_max)
throw exception 
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
