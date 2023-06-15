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

		void					autosort(void);
		void					sort(void);

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

