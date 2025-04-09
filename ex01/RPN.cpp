/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:07:38 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/04/09 17:44:33 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other)
{
	this->operands = other.operands;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other) {
		this->operands = other.operands;
	}
	return *this;
}

bool RPN::isOperator(char c) const 
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void RPN::validateInput(const std::string& input)
{
	if (input.empty())
		throw std::runtime_error("Error: Empty input");

	int digitCount = 0;
	int opCount = 0;
	std::istringstream iss(input);
	std::string token;

	while (iss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error: Invalid token length");
		
		char c = token[0];
		if (isdigit(c))
			digitCount++;
		else if (isOperator(c))
			opCount++;
		else
			throw std::runtime_error("Error: Invalid character");
	}

	if (digitCount != opCount + 1)
		throw std::runtime_error("Error: Invalid expression format");
}

void RPN::performOperation(char op)
{
	if (operands.size() < 2)
		throw std::runtime_error("Error: Not enough operands");

	int a = operands.top(); operands.pop();
	int b = operands.top(); operands.pop();
	int result;

	switch (op)
	{
		case '+':
			if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
				(b < 0 && a < std::numeric_limits<int>::min() - b))
			{
				throw std::runtime_error("Error: Overflow detected!");
			}
			result = b + a;
			break;
		case '-':
			if ((a > 0 && b < std::numeric_limits<int>::min() + a) ||
				(a < 0 && b > std::numeric_limits<int>::max() + a))
			{
				throw std::runtime_error("Error: Overflow detected!");
			}
			result = b - a;
			break;
		case '*':
			if (a != 0 && b > std::numeric_limits<int>::max() / a)
			{
				throw std::runtime_error("Error: Overflow detected!");
			}
			if (a != 0 && b < std::numeric_limits<int>::min() / a)
			{
				throw std::runtime_error("Error: Underflow detected!");
			}
			result = b * a;
			break;
		case '/':
			if (a == 0) throw std::runtime_error("Error: Division by zero");
			// Bölme işlemi için overflow sadece INT_MIN / -1 durumunda olabilir
			if (a == -1 && b == std::numeric_limits<int>::min())
			{
				throw std::runtime_error("Error: Overflow detected!");
			}
			result = b / a;
			break;
		default:
			throw std::runtime_error("Error: Unknown operator");
	}
	operands.push(result);
}
void RPN::processToken(const std::string& token)
{
	char c = token[0];
	if (isdigit(c))
		operands.push(c - '0');
	else if (isOperator(c))
		performOperation(c);
}

void RPN::evaluate(const std::string &expression)
{
	try
	{
		validateInput(expression);
		
		while (!operands.empty()) operands.pop();

		std::istringstream iss(expression);
		std::string token;
		
		while (iss >> token)
			processToken(token);

		if (operands.size() != 1)
			throw std::runtime_error("Error: Calculation error");

		std::cout << operands.top() << std::endl;
	} catch (const std::exception& e)
	{
		throw std::runtime_error(e.what());
	}
}

RPN::~RPN() {}
