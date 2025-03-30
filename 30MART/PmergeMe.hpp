/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:03 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/30 19:48:11 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include <algorithm>
#include <cmath>

class PmergeMe
{
	int counter;
	std::vector<int> FirstVector;
	std::vector<std::vector<int> > geriKalan;
	std::vector<int> RestVector;
	std::vector<int> ss;
	std::vector<std::vector<int> > Groups;
	

	std::list<int> FirstList;
	std::list<std::pair<int , int> > FirstListPair;
	std::list<int> RestList;
	std::list<std::pair<int , int> >::iterator IteratorHolder;

	public :
	PmergeMe();
	PmergeMe(const std::vector<int> &k, const std::list<int> &m);
	PmergeMe(const PmergeMe &a);
	PmergeMe&operator=(PmergeMe const &a);
	void pairMake(std::vector<int> &arr);
	size_t optimizedBinarySearch(const std::vector<int>& arr, int value, size_t maxIndex);
	size_t binarySearch(const std::vector<int>& arr, int value);
	int eeeh(int n);
	// ---------------------
	
	void swapPairs(std::vector<std::vector<int> > &k, size_t level);
	void sort(std::vector<std::vector<int> > &temp);
	void sortPairs(std::vector<std::vector<int> > &bakalim);
	std::vector<std::vector<int> > mergeInsertPairs(std::vector<int> & temp);
	
	size_t optimizedBinarySearch1(std::vector<std::vector<int> >& arr, std::vector<int> value, size_t maxIndex);
	size_t binarySearch1(const std::vector<std::vector<int> > & arr, std::vector<int> value);
	
	void sort();
	void passArgs();
	
	std::vector<int> generateJacobInsertionSequence(std::vector<int> &pend);

	std::vector<std::vector<int> > divideArray(std::vector<int> &m);
	void splitAndUpdate(std::vector<std::vector<int> >& arr);
	void displayArray(std::vector<int> &a);
	void displayPairs(std::vector<std::vector<int>  > &temp);
	void displayPair(std::vector<std::vector<int> > &s);
	std::vector<int> generatePositions(std::vector<int> &pend);
	
	~PmergeMe();
};

#endif
