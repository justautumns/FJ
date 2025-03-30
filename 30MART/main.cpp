/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:38 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/30 21:31:39 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool isPositiveInteger(const std::string& str)
{
	if (str.empty()) return false;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			return false; // Rakam değilse geçersiz
	}

	return true;
}

bool safeStringToInt(const std::string &str, int &result)
{
	if (!isPositiveInteger(str))
	{
		std::cerr << "Error: String must contain only digits and be positive.\n";
		return false;
	}

	std::stringstream ss(str);
	long long temp; // Geçici olarak long long'a çevirip overflow kontrolü yapacağız
	ss >> temp;

	if (ss.fail() || !ss.eof()) { 
		std::cerr << "Error: Conversion failed.\n";
		return false;
	}

	// `temp` int sınırları içinde mi?
	if (temp > std::numeric_limits<int>::max())
	{
		std::cerr << "Error: Overflow detected.\n";
		return false;
	}

	result = static_cast<int>(temp);
	return true;
}
template <typename T>
bool hasDuplicate(T &container)
{
	std::sort(container.begin(), container.end()); // O(N log N) I had to check this before I start.
	return std::adjacent_find(container.begin(), container.end()) != container.end();
}
int main(int ac, char **av)
{
	try
	{
		if (ac < 2)
			throw std::runtime_error("You've entered no input");
		std::vector<int> deneme;
		std::deque<int> aa;
		int m = 1;
		while (av[m])
		{
			int temp;
			if (!safeStringToInt(av[m], temp))
				return (-1);
			else
			{
				deneme.push_back(temp);
				aa.push_back(temp);
			}
			m++;
		}
		if (hasDuplicate(deneme) || hasDuplicate(aa))
			throw std::runtime_error("The sequence you've provided has duplicates please re check and run");
		PmergeMe x(deneme, aa);
		x.passArgs();
		x.passArgsD();
	} catch(const std::exception &a)
	{
		std::cerr << a.what() << std::endl;
	}

	return (0);
}
