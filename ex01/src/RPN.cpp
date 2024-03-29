/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:47 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:53 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

RPN::RPN(void):_input("")
{
	this->_mstack = new std::deque<int>;
	return ;
}

RPN::RPN(std::string const &input_operation):_input(input_operation)
{
	this->_mstack = new std::deque<int>;
	return ;
}

RPN::RPN(RPN const &other)
{
	*this = other;
	return ;
}

RPN::~RPN(void)
{
	if (this->_mstack)
		delete this->_mstack;
	return ;
}

RPN					&RPN::operator=(RPN const &rhs)
{
	//(static_cast< void >(rhs));
	if (this != &rhs)
	{
		this->_mstack->clear();
		this->_mstack = rhs._mstack;
		this->_input = rhs._input;
	}
	return *this;
}

/* links a character to a functional table e_which_char	*/
int					RPN::whichInputChar(char const &c)
{
	if (c == ' ')
		return IS_SPACER;
	else if (isdigit(c))
		return IS_DIGIT;
	else if (c == ADD || c == SUBSTRACT || c == MULTIPLY || c == DIVIDE)
		return IS_OPERATOR;
	return IS_INVALID;
}

/* pops two operands from stack, calculates 
char c_operator should be a match in e_operation enum
*/
void				RPN::popTwo_calculate_push(char const &c_operator)
{
	bool	is_operator = true;

	if (this->_mstack->size() < 2)
		throw (RPN::OperandsMissingException());
	long 	operand1 = this->_mstack->back();
	this->_mstack->pop_back();
	long 	operand2 = this->_mstack->back();
	this->_mstack->pop_back();
	switch (static_cast< int >(c_operator))
	{
		case MULTIPLY:
			operand2 *= operand1;
			break;
		case ADD:
			operand2 += operand1;
			break;
		case SUBSTRACT:
			operand2 -= operand1;
			break;
		case DIVIDE:
			if (operand1)
				operand2 /= operand1;
			else
				throw (RPN::DivByZeroException());
			break;
		default:
			is_operator = false;
			break;
	}
	if (operand2 >= static_cast<long>(std::numeric_limits<int>::min())
		&& operand2 <= static_cast<long>(std::numeric_limits<int>::max()))
		this->_mstack->push_back(static_cast<int>(operand2));
	else
		throw (RPN::IntOverflowException());
	if (!is_operator)
		this->_mstack->push_back(static_cast<int>(operand1));
	return ;
}

/* Parses input string : 
	- encoutered single-digit number is pushed to stack
	- operator token triggers a popTwo_calculate_push operation
 */
void				RPN::calculator(void)
{
	bool	can_be_pushed = true;
	std::string::iterator		it;

	for (it = this->_input.begin() ; it < this->_input.end(); ++it)
	{
		switch (whichInputChar(*it))
		{
			case IS_SPACER:
				can_be_pushed = true;
				break;
			case IS_DIGIT:
				if (can_be_pushed)
					this->_mstack->push_back(static_cast<int>(*it - '0'));
				else
					throw (RPN::MissingSpaceErrorException());
				can_be_pushed = false;
				break;
			case IS_OPERATOR:
				this->popTwo_calculate_push(*it);
				can_be_pushed = false;
				break;
			default:
				throw (RPN::InvalidCharacterException());
				break;
		}
	}
	if (this->_mstack->size() == 1)
		std::cout << COL_BGRN << this->_mstack->back() << COL_RES << std::endl;
	else
		throw (RPN::OperatorsMissingException());
	return ;
}

const char				*RPN::MissingSpaceErrorException::what(void) const throw()
{
	return ("Error : no space before single-digit number");
}

const char				*RPN::InvalidCharacterException::what(void) const throw()
{
	return ("Error : invalid character(s).");
}

const char				*RPN::OperatorsMissingException::what(void) const throw()
{
	return ("Error : missing operator(s).");
}

const char				*RPN::OperandsMissingException::what(void) const throw()
{
	return ("Error : missing operand(s).");
}

const char				*RPN::DivByZeroException::what(void) const throw()
{
	return ("Error : Division by zero.");
}

const char				*RPN::IntOverflowException::what(void) const throw()
{
	return ("Error : integer overflow");
}

