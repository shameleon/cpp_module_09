/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:15 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:25 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# define OUTPUT_VECTOR_CONTENT	1
# define OUTPUT_LIST_CONTENT	0
/* binary search range size */
# define THRESHOLD		10

# include <iostream>
# include <vector>			// std::vector
# include <list>			// std::list
# include <limits>			// std::numeric_limits<int>::max()
# include <cstdlib>			// std::strtol()
# include <ctime>			// std::clock
# include <algorithm>  		// std::sort (not used)
# include <stdexcept>		// std::exception
# include "colors.hpp"		// colors for std::cout

class PmergeMe
{
	private:
		int						_argc;
		std::vector<int>		*_pvec;
		std::list<int>			*_plist;


		PmergeMe(void);
		PmergeMe(PmergeMe &other);
		PmergeMe				&operator=(PmergeMe &rhs);

		/* vector sorted with Ford-Johnson*/
		int						binarySearch(int item, std::vector<int> &vec, int left, int right);
		void					binarySearchInsert(std::vector<int> &elements_to_sort);
		void					pushRightElements(std::vector<int> &elements_to_sort,
													std::vector< std::pair<int, int> > &pairvec);
		void					sortPairsByRightElement(std::vector< std::pair<int, int> > &sortvec,
														std::vector< std::pair<int, int> > &pairvec);
		void					groupElementsBySortedPairs( std::vector< std::pair<int, int> > &pairvec,
															std::vector<int> &ending_singleton);
		void					vecSort(void);
		
		/* list sorted with Ford-Johnson*/
		void					binarySearchInsert(std::list<int> &elements_to_sort, std::list<int> &lst);
		void					pushRightElements(std::list<int> &elements_to_sort, std::list<int> &lst,
													std::list< std::pair<int, int> > &pairlst);
		void					sortPairsByRightElement(std::list< std::pair<int, int> > &sortlst,
														std::list< std::pair<int, int> > &pairlst);
		void					groupElementsBySortedPairs(std::list<int> &lst,
															std::list< std::pair<int, int> > &pairlst,
															std::list<int> &ending_singleton);
		void					listSort(std::list<int> &lst);


		void					printVector(std::string color);
		void					printList(std::string color);
		void					timedSortVector(void);
		void					timedSortList(void);

	public:
		PmergeMe(int argc, char **argv);
		virtual ~PmergeMe(void);

		void					timedSort(void);

		class		DefaultConstructorErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
		class		NonDigitCharException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
		class		IntegerOverflowException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
		class		NegativeNumberException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

