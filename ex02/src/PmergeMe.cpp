/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:47 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:53 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	throw PmergeMeErrorException();
	return ;
}

PmergeMe::PmergeMe(int argc, char ** argv)  //:_length(argc - 1)
{
	this->_pvec = new std::vector<int>;

	long		int_min = static_cast<long>(0);
	long		int_max = static_cast<long>(std::numeric_limits<int>::max());
	std::cout << "Pushed : ";
	for (int i = 1; i < argc; ++i)
	{
		char *pEnd;
		long ln = std::strtol (argv[i], &pEnd, 10);   // base 10
		// if pEnd
		if (ln < int_min || ln > int_max)
		{
			std::cerr << "invalid input" << std::endl;
			return ;
		}
		std::cout << ln << " ";
		this->_pvec->push_back(static_cast<int>(ln));
	}
	return ;
}

PmergeMe::PmergeMe(PmergeMe &other)
{
	*this = other;
	return ;
}

PmergeMe::~PmergeMe(void)
{
	if (this->_pvec)
		delete this->_pvec;
	return ;
}

PmergeMe			&PmergeMe::operator=(PmergeMe &rhs)
{
	(static_cast< void >(rhs));
	return *this;
}

/* parses input args : 
 */
void				PmergeMe::sort(void)
{

	return ;
}

const char			*PmergeMe::PmergeMeErrorException::what(void) const throw()
{
	return ("Error");
}

