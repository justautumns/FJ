/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:09 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/25 14:48:02 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::vector<int> &k, const std::list<int> &m) : FirstVector(k), FirstList(m) {
	this->counter = 0;
	this->level = 1;
}

PmergeMe::PmergeMe(const PmergeMe &a) : FirstVector(a.FirstVector), FirstList(a.FirstList)
{}

PmergeMe &PmergeMe::operator=(PmergeMe const &a)
{
	if (this != &a)
	{
		this->FirstVector = a.FirstVector;
		this->FirstList = a.FirstList;
	}
	return (*this);
}


size_t PmergeMe::binarySearch(const std::vector<int>& arr, int value)
{
	size_t low = 0;
	size_t high = arr.size();
	while (low < high) {
		this->counter++;
		size_t mid = low + (high - low) / 2;
		if (arr[mid] < value) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}
	return low;
}
size_t PmergeMe::optimizedBinarySearch(const std::vector<int>& arr, int value, size_t maxIndex)
{
	size_t low = 0;
	size_t high = maxIndex;
	while (low < high)
	{
	this->counter++;
	size_t mid = low + (high - low) / 2;
	if (arr[mid] < value)
	{
		low = mid + 1;
	} else {
		high = mid;
	}
	}
	return low;
}
int PmergeMe::eeeh(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return eeeh(n - 1) + 2 * eeeh(n - 2);
}

std::vector<int> PmergeMe::generateJacobInsertionSequence(std::vector<int> &k)
{
	size_t size = k.size();
	size_t jcobstalIndex;
	int index = 2;
	std::vector<int> temp;

	while ((jcobstalIndex = eeeh(index)) < size)
	{
		temp.push_back(jcobstalIndex);
		index++;
	}
	return temp;
}

std::vector<int> PmergeMe::generatPositions(std::vector<int> &k)
{
	if (k.empty())
		throw std::runtime_error("the rest array is empty");

	std::vector<int> poses = generateJacobInsertionSequence(k);
	std::vector<int> fnpos;
	size_t lastPos = 0;
	size_t val = 1;
	size_t i = 0;

	while (i < poses.size())
	{
		val = poses.at(i);
		fnpos.push_back(val);

		size_t pos = val - 1;
		while (pos > lastPos)
		{
			fnpos.push_back(pos);
			pos--;
		}
		lastPos = val;
		i++;
	}

	while (val < k.size())
	{
		fnpos.push_back(val + 1);
		val++;
	}

	return fnpos;
}
std::vector<int> PmergeMe::addPendtoMain(std::vector<int> &pend, std::vector<int> &main)
{
	//Bu fonksiyonda jacobsthal indexlerine gore pendi maine yerlestiriyorum.
	std::vector<int> temp = generatPositions(pend);
	std::vector<int>::iterator it;
	int target;
	size_t maxpos;
	size_t eklenti;
	size_t currentpos;

	eklenti = 0;
	for (it = temp.begin(); it < temp.end(); it++)
	{
		target = pend.at(*it - 1);
		maxpos = *it + eklenti;
		currentpos = optimizedBinarySearch(main, target, maxpos);
		main.insert(main.begin() + currentpos, target);
		eklenti++;
	}
	return (main);
}

void displayArray(std::vector<int> &a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << " , ";
	}
	std::cout << std::endl;
}
void displayPairs(std::vector<std::vector<int>  > &temp)
{
	for (size_t i = 0; i < temp.size(); i++)
	{
		for(size_t m = 0; m < temp[i].size() - 1; m += 2)
			std::cout << "[ " << temp[i][m] << " , " << temp[i][m + 1] << " ]" << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::swapPairs(std::vector<std::vector<int>> &k, int level)
{
	if (level > k.size())
	{
		// Eğer k.size() level'a tam bölünmüyorsa, kalan elemanları geriKalan'a ekle unutma!!
		if (k.size() % (level / 2) != 0)
		{
			for (size_t i = k.size() - (k.size() % (level / 2)); i < k.size(); ++i)
			{
				geriKalan.push_back(k[i]);
			}
			k.erase(k.begin() + (k.size() - (k.size() % (level / 2))), k.end());
		}
		//displayPairs(geriKalan);
		std::cout << "Bunlar kalanlar ; " << std::endl;
		//displayPairs(k);
		pairCount = level / 2;
		return;
	}

	for (size_t i = 0; i < k.size(); i += level)
	{
		size_t end = std::min(i + level, k.size());
		for (size_t j = i; j < end; j += level / 2)
		{
			size_t nextGroupStart = j + level / 2;
			if (nextGroupStart >= end) continue;

			if (k[j][0] < k[nextGroupStart][0])
			{
				this->counter++;
				for (size_t m = 0; m < level / 2; ++m)
					std::swap(k[j + m], k[nextGroupStart + m]);
			}
		}
	}
	// displayPairs(k);
	// std::cout << "*******" << std::endl;
	swapPairs(k, level * 2);
}

void PmergeMe::pairMake(std::vector<int> &arr)
{
	if (arr.size() <= 1)
		throw std::runtime_error("Array is too short");
	int i = 0;
	while (i < arr.size() - 1)
	{
		this->counter++;
		std::vector<int> temp;
		if (arr[i] > arr[i + 1])
		{
			temp.push_back(arr[i]);
			temp.push_back(arr[i + 1]);
			this->Groups.push_back(temp);
			i += 2;
		}
		else
		{
			temp.push_back(arr[i + 1]);
			temp.push_back(arr[i]);
			this->Groups.push_back(temp);
			i += 2;
		}
	}
	if (i != arr.size())
		RestVector.push_back(arr[i]);
	//displayPairs(this->Groups);
	std::cout << "yukaridaki ilk hali" << std::endl;
	return (swapPairs(this->Groups, 2));
}

void PmergeMe::sort(std::vector<std::vector<int> > &temp)
{
	std::vector<int> main;
	std::vector<int> pend;
	for (size_t i = 0; i < temp.size(); i++)
	{
		main.push_back(temp[i][0]);
		pend.push_back(temp[i][1]);
	}

	for (size_t i = 0; i < RestVector.size(); i++)
	{
		int m = binarySearch(main, RestVector[i]);
		main.insert(main.begin()+ m, RestVector[i]);
	}
	
	displayArray(main);
	displayArray(pend);
	addPendtoMain(pend, main);
	displayArray(main);
}


size_t PmergeMe::optimizedBinarySearch1(std::vector<std::vector<int> >& arr, std::vector<int> value, size_t maxIndex)
{
	size_t low = 0;
	size_t high = maxIndex;
	while (low < high)
	{
		this->counter++;
		size_t mid = low + (high - low) / 2;
		
		if (arr[mid][0] < value[0]) 
			low = mid + 1;
		else
			high = mid;
	}
	arr.insert(arr.begin() + low, value);
	return low;
}
size_t PmergeMe::binarySearch1(const std::vector<std::vector<int>> & arr, std::vector<int> value)
{
	size_t low = 0;
	size_t high = arr.size();
	while (low < high)
	{
		this->counter++;
		size_t mid = low + (high - low) / 2;
		if (arr[mid][0] < value[0]) 
		{
			low = mid + 1;
		} else {
			high = mid;
		}
	}
	return low;
}

void displayPair(std::vector<std::vector<int>> &s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		for(size_t m = 0; m < s[i].size(); m++)
			std::cout << s[i][m] << " ,";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void display3DArray(const std::vector<std::vector<std::vector<int>>> &vec)
{
	std::cout << "[\n";
	for (const auto &matrix : vec) {
		std::cout << "  { ";
		for (const auto &pair : matrix) {
			std::cout << "[";
			for (size_t i = 0; i < pair.size(); i++) {
				std::cout << pair[i] << (i < pair.size() - 1 ? ", " : "");
			}
			std::cout << "] ";
		}
		std::cout << "},\n";
	}
	std::cout << "]\n";
}

void PmergeMe::denemeSortPart2(std::vector<std::vector<int> > &bakalim)
{
	if (bakalim.size() < 8)
		return;
	std::vector<std::vector<int> > main;
	std::vector<std::vector<int> > pend;
	for (size_t i = 0; i < bakalim.size() - 1; i += 2)
	{
		main.push_back(bakalim[i]);
		pend.push_back(bakalim[i + 1]);
	}
	std::vector<std::vector<int>> seniamk;
	// seniamk.push_back(pend[0]);
	// seniamk.push_back(main[0]);
	// pend.erase(pend.begin());
	// main.erase(main.begin());
	// displayPairs(main);
	// displayPairs(pend);
	std::vector<int> anan;
	main.insert(main.begin(), pend[0]);
	seniamk.push_back(main.back());
	main.pop_back();
	seniamk.push_back(main.back());
	main.pop_back();
	pend.erase(pend.begin());
	int a = 0;

	std::vector<int> minimain;
	std::vector<int> minipend;
	for (size_t i = 0; i < main.size(); i++)
		minimain.push_back(main[i][0]);
	for (size_t i = 0; i < pend.size(); i++)
		minipend.push_back(pend[i][0]);
	generatPositions(minipend);
	displayArray(minimain);
	displayArray(minipend);
	std::vector<int> temp = generatPositions(minipend);
	std::vector<int>::iterator it;
	int target;
	size_t maxpos;
	size_t eklenti;
	size_t currentpos;

	eklenti = 0;
	

	displayPair(main);
	for (it = temp.begin() ; it < temp.end(); it++)
	{
		target = minipend.at(*it - 1);
		std::cout << "hedef rakam" << target << std::endl;
		maxpos = *it + eklenti;
		currentpos = optimizedBinarySearch(minimain, target, maxpos);
		std::cout << "aranacak olan index ; " << maxpos << std::endl;
		std::cout << "index yerlestirilecek olan ; " << currentpos << std::endl;
		minimain.insert(minimain.begin() + currentpos, target);
		main.insert(main.begin() + currentpos, pend.at(*it - 1));
		eklenti++;
	}
	for (int i =seniamk.size() - 1; i >= 0; i--)
		main.insert(main.end(), seniamk[i]);
	bakalim.clear();
	bakalim = main;
	//displayPairs(main);
}
std::vector<std::vector<int> > PmergeMe::denemeSort(std::vector<std::vector<int> >& temp)
{
	std::cout << pairCount << std::endl;
	size_t m = temp.size() / 4;
	std::vector<int> a;
	int arama;
	std::vector<std::vector<int>> first(temp.begin(), temp.begin() + m);
    std::vector<std::vector<int>> pend(temp.begin() + m, temp.begin() + 2*m);
    std::vector<std::vector<int>> second(temp.begin() + 2*m, temp.begin() + 3*m);
    std::vector<std::vector<int>> last(temp.begin() + 3*m, temp.end());
	
	a.push_back(last[0][0]);
	a.push_back(second[0][0]);
	a.push_back(first[0][0]);
	arama = pend[0][0];
	// displayArray(a);
	//displayPairs(geriKalan);
	std::vector<std::vector<std::vector<int> > >bakalim;
	bakalim.push_back(last);
	bakalim.push_back(second);
	bakalim.push_back(first);
	if (geriKalan.size() >= first.size())
	{
		//displayPairs(geriKalan);
		std::vector<std::vector<int> > z;
		for (size_t i = 0; i < first.size(); i++)
			z.push_back(geriKalan[i]);
		int t = binarySearch(a, geriKalan[0][0]);
		bakalim.insert(bakalim.begin() + t, z);
		a.clear();
		for (size_t i = 0; i < bakalim.size(); i++)
			a.push_back(bakalim[i][0][0]);
	}
	int o = optimizedBinarySearch(a, pend[0][0], 3);
	bakalim.insert(bakalim.begin() + o, pend);
	Groups.clear();
	for (size_t i = 0; i < bakalim.size(); i++)
	{
		for (size_t m = 0; m < bakalim[i].size(); m++)
			Groups.push_back(bakalim[i][m]);
	}
	display3DArray(bakalim);
	return (Groups);
}

void PmergeMe::passArgs()
{
	pairMake(this->FirstVector);
	displayPairs(Groups);
	std::vector<std::vector<int> > sorted;
	sorted = denemeSort(Groups);
	denemeSortPart2(sorted);
	sort(sorted);
	std::cout << "Final count of comparison : "<<this->counter << std::endl;
}

PmergeMe::~PmergeMe() {}
