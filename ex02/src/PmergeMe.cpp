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
	std::cout << COL_YEL << "Arguments were pushed to two containers : vector and list " << COL_RES << std::endl;
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

/* not used 
void				PmergeMe::autosort(void)
{
	// std::sort function
	std::sort(this->_pvec->begin(), this->_pvec->end());
}
*/

void				PmergeMe::printVector(std::string color)
{
	std::cout << color;
	for (std::vector< int> ::iterator it = this->_pvec->begin();
			it != this->_pvec->end(); ++it)
		std::cout << *it << " ";
	std::cout << COL_RES << std::endl;
}

void				PmergeMe::timedSortVector(void)
{
	clock_t		start, stop;
	double		delta_t_us = 0;
	std::cout << COL_ORANGE << "Before : " << std::endl;
	printVector(COL_VIOL);
	start = std::clock();
	vecSort();
	stop = std::clock();
	std::cout << COL_ORANGE << "After : ";
	printVector(COL_BLG);
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << COL_ORANGE << "Time to process a range of " << ( _argc - 1 );
	std::cout << " elements with std::vector :  " << delta_t_us << " microseconds \n";
	std::cout << COL_RES << std::endl;
	return ;
}

void				PmergeMe::timedSortList(void)
{
	clock_t		start, stop;
	double		delta_t_us = 0;
	start = std::clock();
	listSort();
	stop = std::clock();
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << COL_ORANGE << "Time to process a range of " << ( _argc - 1 );
	std::cout << " elements with std::list :  " << delta_t_us << " microseconds \n";
	std::cout << COL_RES << std::endl;
	return ;
}

void				PmergeMe::timedSort(void)
{
	//print("Before:", this->_pvec);
	timedSortVector();
	timedSortList();
}

const char			*PmergeMe::PmergeMeErrorException::what(void) const throw()
{
	return ("Error");
}

int		PmergeMe::binarySearch(int item, std::vector<int> &vec, int left, int right)
{
	if (right - left > THRESHOLD)
	{
		int				mid = left + (right - left) / 2;
		unsigned int	index = static_cast<unsigned int>(mid);
		if (item < vec[index])
			binarySearch(item, vec, left, mid);
		else if (item > vec[index])
			binarySearch(item, vec, mid + 1, right);
		else if (item == vec[index])
			return mid;
	}
	return left;
}

void	PmergeMe::binarySearchInsert(std::vector<int> &elements_to_sort)
{
	// std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std::endl;
	// printOneVector(elements_to_sort, COL_GRN2);
	// printOneVector(vec, COL_VIOL);
	if (elements_to_sort.size() == 0)
		return;
	std::vector< int> ::iterator it = this->_pvec->begin();
	//std::cout << *it << std::endl;
	// it != vec.end() not needed max element is already at the end
	int	left = binarySearch(elements_to_sort.front(), *(this->_pvec), 0, static_cast<int>(this->_pvec->size()) - 1);
	it = it + left;
	while (elements_to_sort.front() > *it)
		++it;
	//std::cout << elements_to_sort.front() << " -> " << *it << std::endl;
	this->_pvec->insert(it, elements_to_sort.front());
	elements_to_sort.erase(elements_to_sort.begin());
	binarySearchInsert(elements_to_sort);
}

void	PmergeMe::pushRightElements(std::vector<int> &elements_to_sort,
							std::vector< std::pair<int, int> > &pairvec)
{
	std::vector< std::pair<int, int> >::iterator	it = pairvec.begin();

	this->_pvec->push_back(it->first);
	this->_pvec->push_back(it->second);
	it++;
	for(; it != pairvec.end(); ++it)
	{
		elements_to_sort.push_back(it->first);
		this->_pvec->push_back(it->second);
	}
}

void	PmergeMe::sortPairsByRightElement(std::vector< std::pair<int, int> > &sortvec,
								std::vector< std::pair<int, int> > &pairvec)
{
	while (pairvec.size())
	{
		std::vector< std::pair<int, int> >::iterator	it = pairvec.begin();
		std::vector< std::pair<int, int> >::iterator	min_right_element = it;

		for(; it != pairvec.end(); ++it)
			if (it->second < min_right_element->second)
				min_right_element = it;
		sortvec.push_back(std::make_pair(min_right_element->first, min_right_element->second));
		pairvec.erase(min_right_element);
		sortPairsByRightElement(sortvec, pairvec);

	}
}

void	PmergeMe::groupElementsBySortedPairs(std::vector< std::pair<int, int> > &pairvec,
									std::vector<int> &ending_singleton)
{
	std::vector<int>::iterator		elements_to_sort = this->_pvec->begin();
	std::vector<int>::iterator		right = this->_pvec->begin() + 1;

	for (unsigned long i = 0; i < this->_pvec->size() - 1; ++i)
	{
		if (i % 2 == 0)
		{
			if (*elements_to_sort > *right)
				pairvec.push_back(std::make_pair(*right, *elements_to_sort));
			else
				pairvec.push_back(std::make_pair(*elements_to_sort, *right));
		}
		elements_to_sort++;
		right++;
	}
	if (this->_pvec->size() % 2 == 1)
		ending_singleton.push_back(*(elements_to_sort));
	//vec.erase(vec.begin(), vec.end());
	this->_pvec->clear();
}

void	PmergeMe::vecSort(void)
{
	std::vector< std::pair<int, int> >	pairvec, sortvec;
	std::vector<int>					ending_singleton;
	std::vector<int>					elements_to_sort;
	
	groupElementsBySortedPairs(pairvec, ending_singleton);
	sortPairsByRightElement(sortvec, pairvec);
	pushRightElements(elements_to_sort, sortvec);
	if (ending_singleton.size())
		elements_to_sort.push_back(ending_singleton[0]);
	binarySearchInsert(elements_to_sort);
}

void	PmergeMe::listSort(void)
{
	return ;
}