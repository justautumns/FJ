/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:16:12 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/04/09 19:25:56 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	loadDatabase();
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	this->exchangeRates = other.exchangeRates;
}

// Copy assignment operator
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->exchangeRates = other.exchangeRates;
	}
	return *this;
}

void BitcoinExchange::loadDatabase()
{
	std::ifstream dbFile("data.csv");
	if (!dbFile.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	while (std::getline(dbFile, line))
	{
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos || line.substr(0, commaPos) == "date")
			continue;
		std::string date = line.substr(0, commaPos);
		float rate = static_cast<float>(std::atof(line.substr(commaPos + 1).c_str()));
		exchangeRates[date] = rate;
	}
	dbFile.close();
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	for (size_t i = 0; i < yearStr.size(); ++i)
	{
		if (!isdigit(yearStr[i]))
			return false;
	}
	for (size_t i = 0; i < monthStr.size(); ++i)
	{
		if (!isdigit(monthStr[i]))
			return false;
	}
	for (size_t i = 0; i < dayStr.size(); ++i)
	{
		if (!isdigit(dayStr[i])) 
			return false;
	}

	int year = std::atoi(yearStr.c_str());
	int month = std::atoi(monthStr.c_str());
	int day = std::atoi(dayStr.c_str());

	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	// Ay bazında gün kontrolü
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return false;
	} else if (month == 2)
	{
		// Şubat ayı için artık yıl kontrolü
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear)
		{
			if (day > 29)
				return false;
		} else
		{
			if (day > 28)
				return false;
		}
	}
	return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value)
{
	int m = 0;
	bool flag = false;
	if (valueStr[m] == '+')
	{
		m++;
		flag = true;
	}
	while (valueStr[m])
	{
		if (valueStr[m] == '.')
		{
			if (flag)
			{
				if (m == 5)
				{
					int k = m;
					k++;
					while (valueStr[k])
					{
						if (valueStr[k] != '0')
							return false;
						k++;
					}
				}
			}
			else
			{
				if (m == 4)
				{
					int k = m;
					k++;
					while (valueStr[k])
					{
						if (valueStr[k] != '0')
							return false;
						k++;
					}
					
				}
			}
			
		}
		m++;
	}
	std::istringstream iss(valueStr);
	if (!(iss >> value))
		return false;

	// Check if there's remaining characters
	char c;
	if (iss >> c)
		return false;

	if (value < 0)
		return false;

	if (value > 1000)
		return false;

	return true;
}

float BitcoinExchange::findExchangeRate(const std::string& date)
{
	std::map<std::string, float>::iterator it = exchangeRates.lower_bound(date);

	// Esleme varsa
	if (it != exchangeRates.end() && it->first == date)
		return it->second;

	// bi onceki tarih
	if (it != exchangeRates.begin())
		--it;

	return it->second;
}

void BitcoinExchange::processLine(const std::string& line) 
{
	size_t pipePos = line.find(" | ");
	if (pipePos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}

	std::string date = line.substr(0, pipePos);
	std::string valueStr = line.substr(pipePos + 3);

	if (!isValidDate(date))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return;
	}

	float value;
	if (!isValidValue(valueStr, value))
	{
		if (value < 0)
			std::cout << "Error: not a positive number." << std::endl;
		else if (value > 1000)
			std::cout << "Error: too large a number." << std::endl;
		else
			std::cout << "Error: bad input => " << valueStr << std::endl;
		return;
	}

	float rate = findExchangeRate(date);
	float result = value * rate;
	if (result > std::numeric_limits<float>::max())
		throw std::runtime_error("Error : Overflow detected for the result!");
	std::cout << date << " => " << value << " = " << result << std::endl;
}

void BitcoinExchange::parseInputFile(const std::string& filename)
{
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;
	std::getline(inputFile, line); // Basligi gec cok can skt
	if (line == "date | value")
	{
		while (std::getline(inputFile, line))
			processLine(line);
	}
	else
		throw std::runtime_error("The input has to start with date | value");
	inputFile.close();
}

void BitcoinExchange::process(const std::string& filename)
{
	parseInputFile(filename);
}
BitcoinExchange::~BitcoinExchange() {}
