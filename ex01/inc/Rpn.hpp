/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
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

enum	e_which_char
{
	IS_SPACER = 0,
	IS_DIGIT,
	IS_OPERATOR,
	IS_INVALID,
};

enum	e_operation
{
	MULTIPLY = 52,
	ADD = 53,
	SUBSTRACT = 55,
	DIVIDE = 57,
};

class RPN
{
	private:
		std::stack<int>			*_mstack;
		std::string				_input;
		unsigned int			_operands;
		unsigned int			_operators;

		RPN(void);
		RPN(RPN &other);
		RPN						&operator=(RPN &rhs);

		int						whichInputChar(char &c);
		void					popTwo_calculate_push(char c);

	public:
		RPN(std::string &input_operation);
		~RPN(void);

		void					parseInput(void);

		class		RPNErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

