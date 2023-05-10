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

PmergeMe::PmergeMe(int argc, char ** argv):_argc(argc)
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
	std::cout << std::endl;
	sort();
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

void				PmergeMe::autosort(void)
{
	// sort function
	std::sort(this->_pvec->begin(), this->_pvec->end());
}


/*  
 */
void				PmergeMe::sort(void)
{
	// display vector content
	std::cout << "Before : ";
	for (std::vector<int>::iterator it = this->_pvec->begin();
			it != this->_pvec->end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	clock_t		start, stop;
	double		delta_t_us = 0;
	start = std::clock();
	// auto sort function
	autosort();
	stop = std::clock();
	// display vector content
	std::cout << "After : ";
	for (std::vector<int>::iterator it = this->_pvec->begin(); 
			it != this->_pvec->end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << "Time to process a range of " << ( _argc - 1 ) << " elements with std::sort :  ";
	std::cout << delta_t_us << " microseconds \n";
	return ;
}

const char			*PmergeMe::PmergeMeErrorException::what(void) const throw()
{
	return ("Error");
}

