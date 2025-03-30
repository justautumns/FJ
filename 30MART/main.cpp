/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:38 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/30 20:34:44 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main()
{
	try
	{
		std::vector<int> deneme;
		deneme.push_back(1);
		deneme.push_back(3);
		deneme.push_back(2);
		deneme.push_back(18);
		std::deque<int> aa;
		aa.push_back(1);
		aa.push_back(3);
		aa.push_back(2);
		aa.push_back(18);

		PmergeMe x(deneme, aa);
		x.passArgs();
		x.passArgsD();
		std::cout << deneme.size() << std::endl;
	} catch(const std::exception &a)
	{
		std::cerr << a.what() << std::endl;
	}

	return (0);
}
