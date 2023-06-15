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
	this->_plist = new std::list<int>;

	long		int_min = 0;
	long		int_max = static_cast<long>(std::numeric_limits<int>::max());

	for (int i = 1; i < argc; ++i)
	{
		char 	*pEnd;
		long	nb = std::strtol (argv[i], &pEnd, 10);
		if (*pEnd != '\0')
			throw std::runtime_error("Error : arguments contain non-digit characters.\n");
		else if (nb > static_cast<long>(int_max))
			throw std::runtime_error("Error : integer overflow.\n");
		else if (nb < static_cast<long>(int_min))
			throw std::runtime_error("Error : negative number(s) not accepted.\n");
		this->_pvec->push_back(static_cast<int>(nb));
		this->_plist->push_back(static_cast<int>(nb));
	}
	std::cout << COL_YEL << "Arguments pushed to vector and list containers " << COL_RES << std::endl;
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
	if (this->_plist)
		delete this->_plist;
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
	std::cout << "Before : " << std::endl;
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

void				PmergeMe::timedSort(void)
{
	//print("Before:", this->_pvec);
	clock_t		start, stop;
	double		delta_t_us = 0;
	start = std::clock();
	std::sort(this->_pvec->begin(), this->_pvec->end());
	stop = std::clock();
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << COL_ORANGE << "Time to process a range of " << ( _argc - 1 ) << " elements with std::sort :  ";
	std::cout << delta_t_us << " microseconds" << COL_RES << std::endl;
}

const char			*PmergeMe::PmergeMeErrorException::what(void) const throw()
{
	return ("Error");
}

