/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:15 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:25 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

/* class Span */
# include <iostream>
# include <deque>
# include <iterator>			// std::iterator    std::distance
# include <algorithm>			// std::min_element std::max_element 
								// std::copy        std::sort
								// for_each
# include <stdexcept>			// std::except

/* main.cpp */
# include "colors.hpp"
# include <list>				//std::list<>
# include <iomanip>				// std::setw()
# include <cstdlib>				// std::rand()
# include <ctime>				// srand (time(NULL))


class Rpn
{
	private:
		std::deque<char>		*_mdeq;
		std::string				_input;
		unsigned int			_operands;
		unsigned int			_operators;

		Rpn(void);
		Rpn(Rpn &other);
		Rpn						&operator=(Rpn &rhs);

		bool				is_operation(char	&c);

	public:
		Rpn(std::string &input_operation);
		~Rpn(void);


		void					parseInput(void);
		void					validOperation(void);
		int						calculator(void);
		void					printStack(void) const;

		class		RpnErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

std::ostream			&operator<<(std::ostream& oss, Rpn &rhs);

#endif

