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
	this->_mstack = new std::stack<int>;
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
		throw (RPN::RPNErrorException());
	int 	operand1 = this->_mstack->top();
	this->_mstack->pop();
	int 	operand2 = this->_mstack->top();
	this->_mstack->pop();
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
			throw (RPN::RPNErrorException());
		break;
	default:
		break;
	}
	this->_mstack->push(operand2);
	return ;
}

/* parses input string :
digit is pushed to stack
operator token => pop two calculate the push result
 */
void				RPN::calculator(void)
{
	bool	can_be_pushed = true;

	for (unsigned long i = 0; i < this->_input.size(); i++)
	{
		switch (whichInputChar(this->_input[i]))
		{
		case IS_SPACER:
			can_be_pushed = true;
			break;
		case IS_DIGIT:
			if (can_be_pushed)
				this->_mstack->push((this->_input[i]) - '0');
			else
				throw (RPN::RPNErrorException());
			can_be_pushed = false;
			break;
		case IS_OPERATOR:
			this->popTwo_calculate_push(this->_input[i]);
			break;
		default:
			throw (RPN::RPNErrorException());
			break;
		}
	}
	if (this->_mstack->size() == 1)
		std::cout << COL_BGRN << this->_mstack->top() << COL_RES << std::endl;
	else
		throw (RPN::RPNErrorException());
	return ;
}


