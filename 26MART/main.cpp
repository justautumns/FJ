/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:38 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/26 15:46:06 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main()
{
	try
	{
		std::vector<int> deneme;

		//deneme = {10, 2 , 21, 14, 8, 6, 27, 18, 9, 11 ,4 ,45, 26, 85, 24, 65, 44};
		deneme = {7, 14, 21, 22, 41, 5, 8, 18, 17, 11, 3, 9, 25, 36, 42, 55, 63, 72, 81, 90, 99};
		//deneme = {1 , 2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 11, 15, 26, 44, 66, 67, 74, 77, 97, 100};
		//deneme = {7, 14, 15, 22, 30, 18, 5, 27, 12, 31, 6, 19, 25, 8, 16, 33, 11, 20, 4, 29, 10};
		//deneme = {11 ,2, 29, 1, 14, 21, 12, 67, 58, 23, 20, 91, 78, 56, 25, 15, 0, 17, 36, 71, 99, 33};
		//deneme = {6, 19, 25, 8, 16, 33, 11, 20, 4, 29};
		//deneme = {17, 3, 29, 8, 21, 14, 5, 32, 11, 27, 6, 19, 2, 23, 9, 30, 1, 25, 13, 7, 31, 16, 4, 22};
		std::list<int> aa;
		aa = {};

		PmergeMe x(deneme, aa);
		x.passArgs();
	} catch(const std::exception &a)
	{
		std::cerr << a.what() << std::endl;
	}

	return (0);
}
