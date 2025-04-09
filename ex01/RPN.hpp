/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:57:16 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/04/09 17:24:45 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <list>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <limits>

class RPN
{
	std::stack<int, std::list<int> > operands;

	void validateInput(const std::string& input);
	void processToken(const std::string& token);
	void performOperation(char op);
	bool isOperator(char c) const;

	public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	void evaluate(const std::string& expression);
};

#endif
