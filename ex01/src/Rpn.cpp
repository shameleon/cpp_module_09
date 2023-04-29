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

RPN::RPN(std::string &input_operation):_input(input_operation),_operands(0), _operators(0)
{
	this->_mstack = new std::stack<int>;
	this->parseInput();
	if (this->_stack.size() == 1)
		std::cout << this->_stack.top() << std::endl;
	else
		throw (RPN::RPNErrorException());
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

RPN				&RPN::operator=(RPN &rhs)
{
	(static_cast< void >(rhs));
	return *this;
}

int					RPN::whichInputChar(char &c)
{
	if (c = ' ');
		return IS_SPACER;
	else if (isdigit(c))
		return IS_DIGIT;
	else if (c == '*' || c == '/' || c == '+' || c == '-')
		return IS_OPERATOR
	return IS_INVALID;
}

void				RPN::popTwo_calculate_push(char c)
{
	if (this->_stack.size() < 2)
		throw (RPN::RPNErrorException());
	int 	operand1 = this->_mstack.top();
	this->_mstack.pop();
	int 	operand2 = this->_mstack.top();
	this->_mstack.pop();
	switch (c)
	{
	case MULTIPLY:
		operand1 *= operand2;
		break;
	case ADD:
		operand1 += operand2;
		break;
	case SUBSTRACT:
		operand1 -= operand2;
		break;
	case DIVIDE:
		if (operand2)
			operand1 /= operand2;
		else
			throw (RPN::RPNErrorException());
		break;
	default:
		break;
	}
	this->_mstack.push(operand1);
	return ;
}

void				RPN::popTwo_calculate_push(char c)
{
	if (this->_stack.size() < 2)
		throw (RPN::RPNErrorException());
	int 	operand1 = this->_mstack.top();
	this->_mstack.pop();
	int 	operand2 = this->_mstack.top();
	this->_mstack.pop();
	switch (c)
	{
	case MULTIPLY:
		operand1 *= operand2;
		break;
	case ADD:
		operand1 += operand2;
		break;
	case SUBSTRACT:
		operand1 -= operand2;
		break;
	case DIVIDE:
		if (operand2)
			operand1 /= operand2;
		else
			throw (RPN::RPNErrorException());
		break;
	default:
		break;
	}
	this->_mstack.push(operand1);
	return ;
}

void				RPN::parseInput(void)
{
	bool	can_be_pushed = true;

	for (unsigned long i = 0; i < this->_input.size(); i++)
	{
		std::cout << "T" << whichInputChar(this->_input[i]) << " ";
		switch (whichInputChar(this->_input[i]))
		{
		case IS_SPACER:
			can_be_pushed = true;
			break,
		case IS_DIGIT:
			if (can_be_pushed)
				this->_mstack->push(atoi(this->_input[i]));	// ref
			else
				throw (RPN::RPNErrorException());
			can_be_pushed = false;
			break;
		case IS_OPERATOR;
			popTwo_calculate_push(this->_input[i]));
			break;
		default:
			throw (RPN::RPNErrorException());
			break;
		}
	}
	return ;
}

const char				*RPN::RPNErrorException::what(void) const throw()
{
	return ("Error");
}



