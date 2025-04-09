/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:05:37 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/04/09 17:19:02 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <exception>
#include <limits>

class BitcoinExchange
{
	std::map<std::string, float> exchangeRates;

	void loadDatabase();
	void parseInputFile(const std::string& filename);
	void processLine(const std::string& line);
	bool isValidDate(const std::string& date);
	bool isValidValue(const std::string& valueStr, float& value);
	float findExchangeRate(const std::string& date);

	public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	void process(const std::string& filename);
	~BitcoinExchange();
};

#endif
