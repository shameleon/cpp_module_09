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

/* binary search range size */
# define THRESHOLD	10

# include <iostream>
# include <vector>
# include <list>
# include <limits>			// std::numeric_limits<int>::max()
# include <cstdlib>			// std::strtol()
# include <ctime>
# include <algorithm>  		// sort
# include <stdexcept>
# include "colors.hpp"

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
		void					listSort(void);

		void					printVector(std::string color);
		//void					autosort(void);
		void					timedSortVector(void);
		void					timedSortList(void);

	public:
		PmergeMe(int argc, char **argv);
		virtual ~PmergeMe(void);

		void					timedSort(void);

		class		PmergeMeErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

