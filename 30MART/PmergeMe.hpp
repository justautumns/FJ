/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:03 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/30 21:17:50 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>

class PmergeMe
{
	int counter;
	std::vector<int> FirstVector;
	std::vector<std::vector<int> > geriKalan;
	std::vector<int> RestVector;
	std::vector<int> ss;
	std::vector<std::vector<int> > Groups;
	

	int counterD;
	std::deque<int> FirstDeque;
	std::deque<std::deque<int> > geriKaland;
	std::deque<int> RestDeque;
	std::deque<int> ssd;
	std::deque<std::deque<int> > Groupsd;
	
	public :
	PmergeMe();
	PmergeMe(const std::vector<int> &k, const std::deque<int> &m);
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
	
	void passArgs();
	
	std::vector<int> generateJacobInsertionSequence(std::vector<int> &pend);

	std::vector<std::vector<int> > divideArray(std::vector<int> &m);
	void splitAndUpdate(std::vector<std::vector<int> >& arr);
	void displayArray(std::vector<int> &a);
	void displayPairs(std::vector<std::vector<int>  > &temp);
	void displayPair(std::vector<std::vector<int> > &s);
	std::vector<int> generatePositions(std::vector<int> &pend);

	// DEQUE
	void pairMakeD(std::deque<int> &arr);
	size_t optimizedBinarySearchD(const std::deque<int>& arr, int value, size_t maxIndex);
	size_t binarySearchD(const std::deque<int>& arr, int value);
	int eeehD(int n);
	// ---------------------
	
	void swapPairsD(std::deque<std::deque<int> > &k, size_t level);
	void sortD(std::deque<std::deque<int> > &temp);
	void sortPairsD(std::deque<std::deque<int> > &bakalim);
	std::deque<std::deque<int> > mergeInsertPairsD(std::deque<int> & temp);
	
	size_t optimizedBinarySearch1D(std::deque<std::deque<int> >& arr, std::deque<int> value, size_t maxIndex);
	size_t binarySearch1D(const std::deque<std::deque<int> > & arr, std::deque<int> value);
	
	void passArgsD();
	
	std::deque<int> generateJacobInsertionSequenceD(std::deque<int> &pend);

	std::deque<std::deque<int> > divideArrayD(std::deque<int> &m);
	void splitAndUpdateD(std::deque<std::deque<int> >& arr);
	void displayArrayD(std::deque<int> &a);
	void displayPairsD(std::deque<std::deque<int>  > &temp);
	void displayPairD(std::deque<std::deque<int> > &s);
	std::deque<int> generatePositionsD(std::deque<int> &pend);
	
	~PmergeMe();
};

#endif
