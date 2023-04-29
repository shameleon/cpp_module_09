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
# include <stack>
# include <stdexcept>			// std::except
# include "colors.hpp"

enum	e_which_char
{
	IS_SPACER = 0,
	IS_DIGIT,
	IS_OPERATOR,
	IS_INVALID,
};

enum	e_operation
{
	MULTIPLY = 42,
	ADD = 43,
	SUBSTRACT = 45,
	DIVIDE = 47,
};

class RPN
{
	private:
		std::stack<int>			*_mstack;
		std::string				_input;

		RPN(void);
		RPN(RPN &other);
		RPN						&operator=(RPN &rhs);

		int						whichInputChar(char &c);
		void					popTwo_calculate_push(char &c);

	public:
		RPN(std::string &input_operation);
		~RPN(void);

		void					calculator(void);

		class		RPNErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

