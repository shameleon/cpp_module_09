/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 08:49:47 by jmouaike          #+#    #+#             */
/*   Updated: 2023/04/27 08:49:53 by jmouaike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Rpn.hpp"

Rpn::Rpn(void)
{
	throw (Rpn::RpnErrorException());
	return ;
}

Rpn::Rpn(std::string &input_operation):_input(input_operation),_operands(0), _operators(0)
{
	this->_mdeq = new std::deque<char>;
	this->parseInput();
	this->validOperation();
	this->printStack();
	return ;
}

Rpn::Rpn(Rpn &other)
{
	*this = other;
	return ;
}

Rpn::~Rpn(void)
{
	if (this->_mdeq)
		delete this->_mdeq;
	return ;
}

Rpn				&Rpn::operator=(Rpn &rhs)
{
	(static_cast< void >(rhs));
	return *this;
}

void				Rpn::parseInput(void)
{
	bool	be_pushed = true;

	for (unsigned long i = 0; i < _input.size(); i++)
	{
		if (be_pushed && (isdigit(_input[i]) || is_operation(_input[i])))
		{
			this->_mdeq->push_back(_input[i]);
			be_pushed = false;
		}
		else if (_input[i] == ' ')
			be_pushed = true;
		else
			throw (Rpn::RpnErrorException());
	}
	return ;
}

void				Rpn::validOperation(void)
{
	if (this->_operands + 1 != this ->_operators)
		throw (Rpn::RpnErrorException());
	return ;
}

int				Rpn::calculator(void)
{

	return 12345;
}

void					Rpn::printStack(void) const
{
	for (std::deque< char >::iterator it = this->_mdeq->begin();
		 it != this->_mdeq->end(); ++it )
		std::cout << *it << std::endl;
}

const char				*Rpn::RpnErrorException::what(void) const throw()
{
	return ("Error");
}


std::ostream			&operator<<(std::ostream& oss, Rpn &rhs)
{
	oss << COL_GRN << rhs.calculator() << "\n" << COL_RES;
	return oss;
}

bool					Rpn::is_operation(char	&c)
{
	return (c == '*' || c == '/' || c == '+' || c == '-');
}


