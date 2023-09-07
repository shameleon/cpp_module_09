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

# include <iostream>
# include <deque>
# include <stdexcept>
# include "colors.hpp"
# include <limits>

enum	e_which_char
{
	IS_SPACER	= 0,
	IS_DIGIT,
	IS_OPERATOR,
	IS_INVALID,
};

enum	e_operation
{
	MULTIPLY	= 42,
	ADD			= 43,
	SUBSTRACT	= 45,
	DIVIDE		= 47,
};

class RPN
{
	private:
		std::deque<int>			*_mstack;
		std::string				_input;

		RPN(void);
		RPN(RPN const &other);
		RPN						&operator=(RPN const &rhs);

		int						whichInputChar(char const &c);
		void					popTwo_calculate_push(char const &c_operator);

	public:
		RPN(std::string const &input_operation);
		~RPN(void);

		void					calculator(void);

		class		MissingSpaceErrorException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

		class		InvalidCharacterException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

		class		OperatorsMissingException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

		class		OperandsMissingException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};

		class		DivByZeroException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
		class		IntOverflowException : public std::exception
		{
			public:
				virtual const char		*what(void) const throw();
		};
};

#endif

