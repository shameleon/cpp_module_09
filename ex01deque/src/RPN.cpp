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

RPN::RPN(void)
{
	throw (RPN::RPNErrorException());
	return ;
}

RPN::RPN(std::string &input_operation):_input(input_operation)
{
	this->_mstack = new std::deque<int>;
	return ;
}

RPN::RPN(RPN &other)
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

RPN					&RPN::operator=(RPN &rhs)
{
	(static_cast< void >(rhs));
	return *this;
}

int					RPN::whichInputChar(char &c)
{
	if (c == ' ')
		return IS_SPACER;
	else if (isdigit(c))
		return IS_DIGIT;
	else if (c == '*' || c == '/' || c == '+' || c == '-')
		return IS_OPERATOR;
	return IS_INVALID;
}

void				RPN::popTwo_calculate_push(char &c)
{

	if (this->_mstack->size() < 2)
		throw (RPN::OperandsMissingException());
	long 	operand1 = static_cast< long >(this->_mstack->back());
	this->_mstack->pop_back();
	long 	operand2 = static_cast< long >(this->_mstack->back());
	this->_mstack->pop_back();
	switch (static_cast< int >(c))
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
		break;
	}
	if operans
	this->_mstack->push_back(operand2);
	return ;
}

/* parses input string :
digit is pushed to stack
operator token => pop two calculate the push result
 */
void				RPN::calculator(void)
{
	//is_negative = false;
	std::string::iterator		it;

	for (it = this->_input.begin() ; it < this->_input.end(); ++it)
	{
		switch (whichInputChar(*it))
		{
		case IS_SPACER:
			//can_be_pushed = true;
			break;
		case IS_DIGIT:
			//if (can_be_pushed)
			this->_mstack->push_back(static_cast<int>(*it - '0'));
			//else
			//	throw (RPN::RPNErrorException());
			//can_be_pushed = false;
			break;
		case IS_OPERATOR:
			this->popTwo_calculate_push(*it);
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

const char				*RPN::RPNErrorException::what(void) const throw()
{
	return ("Error");
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

