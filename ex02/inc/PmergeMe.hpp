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
# include <limits>
# include <cstdlib>
# include <ctime>
# include <algorithm>  // sort
# include <stdexcept>
# include "colors.hpp"

class PmergeMe
{
	private:
		int						_argc;
		std::vector<int>		*_pvec;


		PmergeMe(void);
		PmergeMe(PmergeMe &other);
		PmergeMe				&operator=(PmergeMe &rhs);

		void					autosort(void);
		void					sort(void);

	public:
		PmergeMe(int argc, char **argv);
		~PmergeMe(void);

		class		PmergeMeErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

