/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:16:03 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/27 05:33:22 by mehmeyil         ###   ########.fr       */
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
	std::vector<int> FirstVector;
	std::vector<std::pair<int , int> > FirstVecPair;
	std::vector<std::vector<int> > geriKalan;
	std::vector<int> RestVector;
	std::vector<int> grupArtigi;
	std::vector<std::vector<std::pair<int, int>> > deneme;
	std::vector<int> final;
	std::vector<int> ss;
	std::vector<std::vector<int> > Groups;
	std::vector<int> pend;
	std::vector<int> jacobSequence;
	std::vector<int> positions;
	std::vector<int> indexMapping;
	std::vector<std::vector<int> > bakalimbakalim;


	bool flag;
	int level;
	int counter;
	int pairCount = 0;
	std::list<int> FirstList;
	std::list<std::pair<int , int> > FirstListPair;
	std::list<int> RestList;
	std::list<std::pair<int , int> >::iterator IteratorHolder;

	public :
	PmergeMe();
	PmergeMe(const std::vector<int> &k, const std::list<int> &m);
	PmergeMe(const PmergeMe &a);
	PmergeMe&operator=(PmergeMe const &a);
	~PmergeMe();
	void pairMake(std::vector<int> &arr);
	size_t optimizedBinarySearch(const std::vector<int>& arr, int value, size_t maxIndex);
	size_t binarySearch(const std::vector<int>& arr, int value);
	std::vector<int> checkGeriyeKalan(int level , int num);
	int eeeh(int n);
	std::vector<int> addPendtoMain(std::vector<int> &pend, std::vector<int> &main);
	// ---------------------
	std::vector<int> generateJacobInsertionSequence(int n);
	std::vector<int> generatPositions(std::vector<int> &k);
	void swapPairs(std::vector<std::vector<int>> &k, int level);
	std::vector<std::vector<int> > mergeInsert(std::vector<std::vector<int> > &temp);
	std::vector<std::vector<int>> mergeInsert2(std::vector<std::vector<int>>& left, std::vector<std::vector<int>>& right);

	void generateJakobSquence(size_t size);
	int optimizedInsertion(std::vector<int>& k, int low, int max, int num);
	std::vector<std::vector<int>> swapSmallPairs(std::vector<std::vector<int>>& k);
	void sort(std::vector<std::vector<int> > &temp);
	size_t optimizedBinarySearch(const std::vector<std::vector<int>>& arr, int value);
	std::vector<std::vector<int> >denemeSort(std::vector<std::vector<int> >& temp);
	void denemeSortPart2(std::vector<std::vector<int> > &bakalim);

	size_t optimizedBinarySearch1(std::vector<std::vector<int> >& arr, std::vector<int> value, size_t maxIndex);
	size_t binarySearch1(const std::vector<std::vector<int>> & arr, std::vector<int> value);
	void Mergethem(std::vector<std::vector<int> > &first, std::vector<std::vector<int> > &second);

	
	
	void sort();
	void passArgs();
	
	//26 MART
	std::vector<std::vector<std::vector<int> > > denemeSortPart3(std::vector<std::vector<std::vector<int> > >& temp);
	std::vector<int> generateJacobInsertionSequence(std::vector<int> &pend);
	std::vector<std::vector<int> > denemeSort2(std::vector<int> & temp);


	//27 MART
	std::vector<std::vector<int> > divideArray(std::vector<int> &m);
	void splitAndUpdate(std::vector<std::vector<int>>& arr);



	
};

#endif
