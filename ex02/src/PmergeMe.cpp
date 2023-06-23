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
	throw DefaultConstructorErrorException();
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
		{
			delete this->_pvec;
			delete this->_plist;
			throw NonDigitCharException();
		}
		else if (nb > static_cast<long>(int_max))
		{
			delete this->_pvec;
			delete this->_plist;
			throw IntegerOverflowException();
		}
		else if (nb < static_cast<long>(int_min))
		{
			delete this->_pvec;
			delete this->_plist;
			throw NegativeNumberException();
		}
		this->_pvec->push_back(static_cast<int>(nb));
		this->_plist->push_back(static_cast<int>(nb));
	}
	std::cout << COL_YEL << "Positive integer sequence entered and pushed into two containers : vector and list ";
	std::cout << std::endl;
	std::cout << COL_AUB << "PmergeMe is implementing merge-insert sort algorithm to sort the given sequence " << std::endl;
	std::cout << COL_RES << std::endl;
	return ;
}

PmergeMe::PmergeMe(PmergeMe const &other)
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

PmergeMe			&PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		this->_pvec->clear();
		this->_plist->clear();
		this->_pvec = rhs._pvec;
		this->_plist = rhs._plist;
		this->_argc = rhs._argc;
	}
	return *this;
}

void				PmergeMe::printVector(std::string color) const
{
	std::cout << color;
	for (std::vector< int> ::iterator it = this->_pvec->begin();
			it != this->_pvec->end(); ++it)
		std::cout << *it << " ";
	std::cout << COL_RES << std::endl;
}


void				PmergeMe::printList(std::string color) const
{
	std::cout << color;
	for (std::list< int> ::iterator it = this->_plist->begin();
			it != this->_plist->end(); ++it)
		std::cout << *it << " ";
	std::cout << COL_RES << std::endl;
}

void				PmergeMe::timedSortVector(void)
{
	clock_t		start, stop;
	double		delta_t_us = 0;

	if (OUTPUT_VECTOR_CONTENT)
	{
		std::cout << COL_ORANGE << "Before : " << std::endl;
		printVector(COL_VIOL);
	}
	start = std::clock();
	vecSort();
	stop = std::clock();
	if (OUTPUT_VECTOR_CONTENT)
	{
		std::cout << COL_ORANGE << "Vector After : " << std::endl;
		printVector(COL_BLG);
	}
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << COL_ORANGE << "Time to process a range of " << ( _argc - 1 );
	std::cout << " elements with a vector container:  " << delta_t_us << " microseconds \n";
	std::cout << COL_RES << std::endl;
	return ;
}

void				PmergeMe::timedSortList(void)
{
	clock_t		start, stop;
	double		delta_t_us = 0;

	start = std::clock();
	listSort(*(this->_plist));
	stop = std::clock();
	if (OUTPUT_LIST_CONTENT)
	{
		std::cout << COL_ORANGE << "List After : " << std::endl;
		printList(COL_BLG);
	}
	delta_t_us += ( static_cast< double >(stop - start) * 1E6 ) / CLOCKS_PER_SEC ;
	std::cout << COL_ORANGE << "\nTime to process a range of " << ( _argc - 1 );
	std::cout << " elements with a list container :  " << delta_t_us << " microseconds \n";
	std::cout << COL_RES << std::endl;
	return ;
}

void				PmergeMe::timedSort(void)
{
	timedSortVector();
	timedSortList();
}

/************** Vector merge-insert **********************************************/
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

void				PmergeMe::binarySearchInsert(std::vector<int> &elements_to_sort)
{
	if (elements_to_sort.size() == 0)
		return;
	std::vector< int> ::iterator it = this->_pvec->begin();
	int	left = binarySearch(elements_to_sort.front(), *(this->_pvec), 0, static_cast<int>(this->_pvec->size()) - 1);
	it = it + left;
	while (elements_to_sort.front() > *it)
		++it;
	this->_pvec->insert(it, elements_to_sort.front());
	elements_to_sort.erase(elements_to_sort.begin());
	binarySearchInsert(elements_to_sort);
}

void				PmergeMe::pushRightElements(std::vector<int> &elements_to_sort,
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

void				PmergeMe::sortPairsByRightElement(std::vector< std::pair<int, int> > &sortvec,
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

void				PmergeMe::groupElementsBySortedPairs(std::vector< std::pair<int, int> > &pairvec,
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

void				PmergeMe::vecSort(void)
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


/************** List merge-insert **********************************************/

/* no subcript overload for lists : Random access of elements not possible.
	As list is implemented as a double liked-list,
	access by traversing through with iterators 
*/
void				PmergeMe::binarySearchInsert(std::list<int> &elements_to_sort, std::list<int> &lst)
{
	if (elements_to_sort.size() == 0)
		return;
	std::list< int> ::iterator it = lst.begin();
	while (elements_to_sort.front() > *it)
		++it;
	lst.insert(it, elements_to_sort.front());
	elements_to_sort.erase(elements_to_sort.begin());
	binarySearchInsert(elements_to_sort, lst);
}

void				PmergeMe::pushRightElements(std::list<int> &elements_to_sort, std::list<int> &lst,
								std::list< std::pair<int, int> > &pairlst)
{
	std::list< std::pair<int, int> >::iterator	it = pairlst.begin();

	lst.push_back(it->first);
	lst.push_back(it->second);
	it++;
	for(; it != pairlst.end(); ++it)
	{
		elements_to_sort.push_back(it->first);
		lst.push_back(it->second);
	}
}

void				PmergeMe::sortPairsByRightElement(std::list< std::pair<int, int> > &sortlst,
								std::list< std::pair<int, int> > &pairlst)
{
	while (pairlst.size())
	{
		std::list< std::pair<int, int> >::iterator	it = pairlst.begin();
		std::list< std::pair<int, int> >::iterator	min_right_element = it;

		for(; it != pairlst.end(); ++it)
			if (it->second < min_right_element->second)
				min_right_element = it;
		sortlst.push_back(std::make_pair(min_right_element->first, min_right_element->second));
		pairlst.erase(min_right_element);
		sortPairsByRightElement(sortlst, pairlst);

	}
}

void				PmergeMe::groupElementsBySortedPairs(std::list<int> &lst,
								std::list< std::pair<int, int> > &pairlst,
								std::list<int> &ending_singleton)
{
	std::list<int>::iterator		it_left = lst.begin();
	std::list<int>::iterator		it_right = lst.begin();
	++it_right;

	for (unsigned long i = 0; i < lst.size() - 1; ++i)
	{
		if (i % 2 == 0)
		{
			if (*it_left > *it_right)
				pairlst.push_back(std::make_pair(*it_right, *it_left));
			else
				pairlst.push_back(std::make_pair(*it_left, *it_right));
		}
		it_left++;
		it_right++;
	}
	if (lst.size() % 2 == 1)
		ending_singleton.push_back(*(it_left));
	lst.clear();
}

void				PmergeMe::listSort(std::list<int> &lst)
{
	std::list< std::pair<int, int> >	pairlst, sortlst;
	std::list<int>						ending_singleton;
	std::list<int>						elements_to_sort;
	
	groupElementsBySortedPairs(lst, pairlst, ending_singleton);
	sortPairsByRightElement(sortlst, pairlst);
	pushRightElements(elements_to_sort, lst, sortlst);
	if (ending_singleton.size())
		elements_to_sort.push_back(ending_singleton.front());
	binarySearchInsert(elements_to_sort, lst);
}

const char			*PmergeMe::DefaultConstructorErrorException::what(void) const throw()
{
	return ("Error : arguments missing. Default constructor called\n");
}


const char			*PmergeMe::NonDigitCharException::what() const throw()
{
	return ("Error : arguments contain non-digit characters.\n");
}

const char			*PmergeMe::IntegerOverflowException::what() const throw()
{
	return ("Error : integer overflow.\n");
}

const char			*PmergeMe::NegativeNumberException::what() const throw()
{
	return ("Error : negative number(s) not accepted.\n");
}