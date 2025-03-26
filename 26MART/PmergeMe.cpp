/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:09 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/03/26 21:49:51 by mehmeyil         ###   ########.fr       */
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
	size_t mid = (low + (high)) / 2;
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
	if (n == 0) return 0;
	if (n == 1) return 1;

	int prev = 1;      // jacobsthal(1)
	int prev_prev = 0;  // jacobsthal(0)
	int current;

	for (int i = 2; i <= n; ++i) {
		current = prev + 2 * prev_prev;
		prev_prev = prev;
		prev = current;
	}
	return current;
}

std::vector<int> PmergeMe::generateJacobInsertionSequence(std::vector<int> &pend)
{
	std::vector<int> jacobs;
	int index = 3;
	int jcobstalIndex;

	while ((jcobstalIndex = eeeh(index)) <= pend.size()) { // <= kullan
		jacobs.push_back(jcobstalIndex);
		index++;
	}
	return jacobs;
}

void displayArray(std::vector<int> &a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << " , ";
	}
	std::cout << std::endl;
}
std::vector<int> PmergeMe::generatPositions(std::vector<int> &pend)
{
	std::vector<int> positions;
	std::vector<int> jacobNumbers = generateJacobInsertionSequence(pend);

	size_t lastPos = 1;

	for (size_t i = 0; i < jacobNumbers.size(); i++) {
		size_t val = jacobNumbers[i];
		positions.push_back(val);
		
		size_t pos = val - 1;
		while (pos > lastPos) {
			positions.push_back(pos);
			pos--;
		}
		lastPos = val;
	}

	size_t val = pend.size();
	while (val > lastPos) {
		positions.push_back(val);
		val--;
	}

	return positions;
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
	// 1. Base Case: Eğer level, k.size()'dan büyükse, kalanları işle
	if (level > k.size()) {
		// Kalan elemanların başlangıç indeksi
		size_t remaining_start = (k.size() / (level / 2)) * (level / 2);
		
		// Kalan elemanları geriKalan'a ekle
		for (size_t i = remaining_start; i < k.size(); ++i) {
			geriKalan.push_back(k[i]);
		}
		
		// Eklenen elemanları ana vektörden çıkar
		k.erase(k.begin() + remaining_start, k.end());
		
		pairCount = level / 2;  // Son işlenen pair boyutunu kaydet
		return;
	}

	// 2. Pair'leri karşılaştır ve swap et
	for (size_t i = 0; i < k.size(); i += level) {
		size_t group1_end = i + (level / 2);
		size_t group2_end = i + level;
		
		// Grup sınırlarını kontrol et
		if (group1_end >= k.size()) break;
		if (group2_end > k.size()) group2_end = k.size();
		
		// Sadece ilk elemanları karşılaştır
		if (k[i][0] < k[group1_end][0]) {
			this->counter++;
			// Swap işlemi
			for (size_t j = 0; j < (level / 2) && (group1_end + j) < k.size(); ++j) {
				std::swap(k[i + j], k[group1_end + j]);
			}
		}
	}

	// 3. Bir sonraki level için recursive çağrı
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
	displayPairs(this->Groups);
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
	main.insert(main.begin(), pend[0]);
	for (size_t i = 0; i < RestVector.size(); i++)
	{
		int m = binarySearch(main, RestVector[i]);
		main.insert(main.begin()+ m, RestVector[i]);
	}
	displayArray(main);
	displayArray(pend);
	// std::vector<int> poss = generatPositions(pend);
	// int target;
	std::vector<int> aa = generatPositions(pend);
	std::vector<int>::iterator it;
	int target;
	size_t maxpos;
	size_t eklenti;
	size_t currentpos;

	eklenti = 0;
	for (it = aa.begin(); it < aa.end(); it++)
	{
		target = pend.at(*it - 1);
		std::cout << "jacob index : " << *it << std::endl;
		maxpos = *it + eklenti;
		currentpos = optimizedBinarySearch(main, target, maxpos);
		main.insert(main.begin() + currentpos, target);
		eklenti++;
	}
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
	main.insert(main.begin(), pend[0]);

	std::vector<int> minimain;
	std::vector<int> minipend;
	for (size_t i = 0; i < main.size(); i++)
		minimain.push_back(main[i][0]);
	for (size_t i = 0; i < pend.size(); i++)
		minipend.push_back(pend[i][0]);
	//displayArray(minimain);
	displayArray(minipend);
	std::vector<int> aa = generatPositions(minipend);
	std::vector<int>::iterator it;
	int target;
	size_t maxpos;
	size_t eklenti;
	size_t currentpos;

	eklenti = 0;
	for (it = aa.begin(); it < aa.end(); it++)
	{
		target = minipend.at(*it - 1);
		std::cout << "jacob index : " << *it << std::endl;
		maxpos = *it + eklenti;
		currentpos = optimizedBinarySearch(minimain, target, maxpos);
		minimain.insert(minimain.begin() + currentpos, target);
		main.insert(main.begin() + currentpos, pend[*it - 1]);
		eklenti++;
	}
	displayPairs(main);
	bakalim.clear();
	bakalim = main;
}
// std::vector<std::vector<std::vector<int> > > PmergeMe::denemeSortPart3(std::vector<std::vector<std::vector<int> > >& temp)
// {
// 	std::vector<std::vector<std::vector<int> main;
// 	std::vector<std::vector<std::vector<int> pend;

// 	for (size_t i = 0; i < temp.size() - 1; i += 2)
// 	{
// 		main.push_back(temp[i]);
// 		pend.push_back(temp[i + 1]);
// 	}
// 	if ()
// }

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
		// for (size_t i = 0; i < first.size(); i++)
		// {
		// 	z.push_back(geriKalan[i]);
		// }
		std::cout << "Ben ilk geri kalan : ";
		displayPairs(geriKalan);
		int i = 0;
		while (i < first.size())
		{
			z.push_back(geriKalan[i]);
			i++;
		}
		std::vector<std::vector<int> > y;
		for (int s = i; s < geriKalan.size(); s++)
		{
			y.push_back(geriKalan[s]);
		}
		geriKalan.clear();
		geriKalan = y;
		y.clear();
		std::cout << "Geri kalan assadakiler : "; 
		displayPairs(y);
		int t = binarySearch(a, z[0][0]);
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

// std::vector<std::vector<int> > PmergeMe::denemeSort2(std::vector<int> & array)
// {

// 	std::vector<std::vector<int> > main;
// 	size_t mid = array.size() / 2;
// 	std::vector<int> left(array.begin(), array.begin() + mid);
// 	std::vector<int> right(array.begin() + mid, array.end());
	

// 	// while (mid > 1)
// 	// {
		
// 	// }
// 	return (main);
// }


void PmergeMe::passArgs()
{
	pairMake(this->FirstVector);
	displayPairs(Groups);
	// std::vector<int> mm;
	// for (size_t i = 0; i < Groups.size(); i++)
	// {
	// 	for (size_t m = 0; m < Groups[i].size(); m++)
	// 		mm.push_back(Groups[i][m]);
	// }
	// displayArray(mm);
	// for (size_t i = 0; i < geriKalan.size(); i++)
	// {
	// 	for (size_t m = 0; m < geriKalan[i].size(); m++)
	// 		std::cout << geriKalan[i][m] << " ";
	// 	std::cout << std::endl;
	// }
	std::vector<std::vector<int> > sorted;
	sorted = denemeSort(Groups);
	//denemeSortPart2(sorted);
	//displayPairs(sorted);
	//sort(sorted);
	std::cout << "Final count of comparison : "<<this->counter << std::endl;
}

PmergeMe::~PmergeMe() {}
