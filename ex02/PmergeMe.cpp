/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:09 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/04/09 22:39:37 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehmeyil <mehmeyil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:09 by mehmeyil          #+#    #+#             */
/*   Updated: 2025/04/10 20:38:55 by mehmeyil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const std::vector<int> &k, const std::deque<int> &m) : FirstVector(k), FirstDeque(m)
{
	this->counter = 0;
	this->counterD = 0;
}

PmergeMe::PmergeMe(const PmergeMe &a) : FirstVector(a.FirstVector), FirstDeque(a.FirstDeque)
{}

PmergeMe &PmergeMe::operator=(PmergeMe const &a)
{
	if (this != &a)
	{
		this->FirstVector = a.FirstVector;
		this->FirstDeque = a.FirstDeque;
	}
	return (*this);
}


size_t PmergeMe::binarySearch(const std::vector<int>& arr, int value)
{
	size_t low = 0;
	size_t high = arr.size();
	while (low < high)
	{
		this->counter++;
		size_t mid = low + (high - low) / 2;
		if (arr[mid] < value)
			low = mid + 1;
		 else
			high = mid;
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
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}
int PmergeMe::eeeh(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	int prev = 1;	//	jacobsthal(1)
	int prev_prev = 0;	//jacobsthal(0)
	int current;

	for (int i = 2; i <= n; ++i)
	{
		current = prev + 2 * prev_prev;
		prev_prev = prev;
		prev = current;
	}
	return current;
}

std::vector<int> PmergeMe::generateJacobInsertionSequence(std::vector<int> &pend)
{
	std::vector<int> jacobs;
	size_t index = 3;
	size_t jcobstalIndex;

	while ((jcobstalIndex = eeeh(index)) <= pend.size())
	{
		jacobs.push_back(jcobstalIndex);
		index++;
	}
	return jacobs;
}

void PmergeMe::displayArray(std::vector<int> &a)
{
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}
std::vector<int> PmergeMe::generatePositions(std::vector<int> &pend)
{
	std::vector<int> positions;
	std::vector<int> jacobNumbers = generateJacobInsertionSequence(pend);

	size_t sonposition = 1;

	for (size_t i = 0; i < jacobNumbers.size(); i++)
	{
		size_t val = jacobNumbers[i];
		positions.push_back(val);
		
		size_t pos = val - 1;
		while (pos > sonposition) {
			positions.push_back(pos);
			pos--;
		}
		sonposition = val;
	}

	size_t val = pend.size();
	while (val > sonposition)
	{
		positions.push_back(val);
		val--;
	}

	return positions;
}

void PmergeMe::displayPairs(std::vector<std::vector<int>  > &temp)
{
	for (size_t i = 0; i < temp.size(); i++)
	{
		for(size_t m = 0; m < temp[i].size() - 1; m += 2)
			std::cout << "[ " << temp[i][m] << " , " << temp[i][m + 1] << " ]" << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::swapPairs(std::vector<std::vector<int> > &k, size_t level)
{
	// 1. Base Case: Eğer level, k.size()'dan büyükse, kalanları işle
	if (level > k.size()) {
		// Kalan elemanların başlangıç indeksi
		size_t remaining_start = (k.size() / (level / 2)) * (level / 2);
		
		// Kalan elemanları geriKalan'a ekle
		for (size_t i = remaining_start; i < k.size(); ++i)
			geriKalan.push_back(k[i]);
		
		// Eklenen elemanları ana vektörden çıkar
		k.erase(k.begin() + remaining_start, k.end());
		return;
	}

	// 2. Pair'leri karşılaştır ve swap et
	for (size_t i = 0; i < k.size(); i += level)
	{
		size_t group1_end = i + (level / 2);
		size_t group2_end = i + level;
		
		// Grup sınırlarını kontrol et
		if (group1_end >= k.size()) break;
		if (group2_end > k.size()) group2_end = k.size();
		
		// Sadece ilk elemanları karşılaştır
		this->counter++;
		if (k[i][0] < k[group1_end][0])
		{
			// Swap işlemi
			for (size_t j = 0; j < (level / 2) && (group1_end + j) < k.size(); ++j)
				std::swap(k[i + j], k[group1_end + j]);
		}
	}
	// 3. Bir sonraki level için recursive çağrı
	swapPairs(k, level * 2);
}

void PmergeMe::pairMake(std::vector<int> &arr)
{
	if (arr.size() <= 1)
		return ;
	size_t i = 0;
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
	//std::cout << "yukaridaki ilk hali" << std::endl;
	return (swapPairs(this->Groups, 2));
}

std::vector<int> PmergeMe::sort(std::vector<std::vector<int> > &temp)
{
	std::vector<int> main;
	std::vector<int> pend;
	for (size_t i = 0; i < temp.size(); i++)
	{
		main.push_back(temp[i][0]);
		pend.push_back(temp[i][1]);
	}
	
	size_t eklenti;
	eklenti = 0;
	main.insert(main.begin(), pend[0]);
	eklenti++;
	
	// displayArray(main);
	// displayArray(pend);
	std::vector<int> aa = generatePositions(pend);
	std::vector<int>::iterator it;
	int target;
	size_t maxpos;
	size_t currentpos;
	for (it = aa.begin(); it != aa.end(); it++)
	{
		target = pend.at(*it - 1);
		//std::cout << "jacob index : " << *it << std::endl;
		maxpos = *it - 1 + eklenti;
		if (maxpos >= main.size())
			maxpos  = main.size();
		//std::cout << "MAX index : " << maxpos << std::endl;
		currentpos = optimizedBinarySearch(main, target, maxpos);
		//std::cout << "inserting in  main index : " << currentpos << " the number " << target << std::endl;
		main.insert(main.begin() + currentpos, target);
		eklenti++;
	}
	for (size_t i = 0; i < RestVector.size(); i++)
	{
		int m = binarySearch(main, RestVector[i]);
		main.insert(main.begin()+ m, RestVector[i]);
	}
	return (main);
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
size_t PmergeMe::binarySearch1(const std::vector<std::vector<int> > & arr, std::vector<int> value)
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

void PmergeMe::displayPair(std::vector<std::vector<int> > &s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		for(size_t m = 0; m < s[i].size(); m++)
			std::cout << s[i][m] << " ,";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::sortPairs(std::vector<std::vector<int> > &bakalim)
{
	std::vector<std::vector<int> > main;
	std::vector<std::vector<int> > pend;
	for (size_t i = 0; i < bakalim.size() - 1; i += 2)
	{
		main.push_back(bakalim[i]);
		pend.push_back(bakalim[i + 1]);
	}
	size_t eklenti;
	eklenti = 0;
	main.insert(main.begin(), pend[0]);
	eklenti++;
	std::vector<int> minimain;
	std::vector<int> minipend;
	for (size_t i = 0; i < main.size(); i++)
		minimain.push_back(main[i][0]);
	for (size_t i = 0; i < pend.size(); i++)
		minipend.push_back(pend[i][0]);
		// //displayArray(minimain);
		// displayArray(minipend);
	std::vector<int> aa = generatePositions(minipend);
	std::vector<int>::iterator it;
	int target;
	size_t maxpos;
	size_t currentpos;
		
	for (it = aa.begin(); it != aa.end(); it++)
	{
		target = minipend.at(*it - 1);
			//std::cout << "jacob index : " << *it << std::endl;
		maxpos = *it + eklenti;
		if (maxpos >= main.size())
			maxpos  = main.size();
		currentpos = optimizedBinarySearch(minimain, target, maxpos);
		minimain.insert(minimain.begin() + currentpos, target);
		main.insert(main.begin() + currentpos, pend[*it - 1]);
		eklenti++;
	}
	//displayPairs(main);
	bakalim.clear();
	bakalim = main;
}


std::vector<std::vector<int> > PmergeMe::divideArray(std::vector<int> &m)
{
	size_t mid = m.size() / 2;
	std::vector<int> a(m.begin(), m.begin() + mid);
	std::vector<int> b(m.begin() + mid, m.end());
	std::vector<std::vector<int> > result;
	result.push_back(a);
	result.push_back(b);
	return result;
}

void PmergeMe::splitAndUpdate(std::vector<std::vector<int> >& arr)
{
	std::vector<std::vector<int> > newArr;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i].size() >= 2) {
			// İlk yarıyı al
			std::vector<int> firstHalf(arr[i].begin(), arr[i].begin() + arr[i].size()/2);
			// İkinci yarıyı al
			std::vector<int> secondHalf(arr[i].begin() + arr[i].size()/2, arr[i].end());
			
			newArr.push_back(firstHalf);
			newArr.push_back(secondHalf);
		} else {
			// Eğer tek elemanlıysa olduğu gibi ekle
			newArr.push_back(arr[i]);
		}
	}
	arr = newArr;
}
std::vector<std::vector<int> > PmergeMe::mergeInsertPairs(std::vector<int> & temp)
{
	std::vector<std::vector<int> > main;
	if (temp.size() < 4)
	{
			main.push_back(temp);
			return (main);
	}
	std::vector<std::vector<int> > karisik = divideArray(temp);
	if (temp.size() < 8)
	{
		main.push_back(karisik[1]);
		main.push_back(karisik[0]);
		if (ss.size() >= main[0].size())
		{
			int m = binarySearch1(main, ss);
			main.insert(main.begin() + m, ss);
		}
		return (main);
	}
	std::vector<std::vector<int> > a = divideArray(karisik[0]);
	std::vector<std::vector<int> > b = divideArray(karisik[1]);
	displayPair(a);
	displayPair(b);
	if (a.size() + b.size() >= 4)
	{
		main.push_back(b[1]);
		main.push_back(b[0]);
		main.push_back(a[0]);
		std::vector<std::vector<int> > pend;
		for (size_t i = 2; i < b.size(); i++)
			pend.push_back(b[i]);
		for (size_t i = 1; i < a.size(); i++)
			pend.push_back(a[i]);
		while (ss.size() >= a[0].size())
		{
			std::vector<int> z;
			size_t elements_to_take = a[0].size(); // Take exactly the pair size
			z.insert(z.end(), ss.begin(), ss.begin() + elements_to_take);
			ss.erase(ss.begin(), ss.begin() + elements_to_take);
			pend.insert(pend.begin(), z);
		}
		for (size_t i = 0; i < pend[0].size(); i++)
			RestVector.insert(RestVector.begin(), pend[0][i]);
		// std::cout << "Pend : ";
		// displayPair(pend);
		// std::cout << "main : ";
		// displayPair(main);
		std::vector<int> minipend;
		std::vector<int> minimain;
		for (size_t i = 0; i < pend.size(); i++)
		{
			minipend.push_back(pend[i][0]);
		}
		for (size_t i = 0; i < main.size(); i++)
		{
			minimain.push_back(main[i][0]);
		}
		std::vector<int> aa = generatePositions(minipend);
		std::vector<int>::iterator it;
		int target;
		size_t maxpos;
		size_t currentpos;
		size_t eklenti = 0;
		// aa.insert(aa.begin(), 1);
		for (it = aa.begin(); it != aa.end(); it++)
		{
			target = minipend.at(*it - 1);
				//std::cout << "jacob index : " << *it << std::endl;
			maxpos = *it + eklenti;
			if (maxpos >= main.size())
				maxpos  = main.size();
			currentpos = optimizedBinarySearch(minimain, target, maxpos);
			minimain.insert(minimain.begin() + currentpos, target);
			main.insert(main.begin() + currentpos, pend[*it - 1]);
			eklenti++;
		}
	}
	while (main[0].size() != 1)
	{
		splitAndUpdate(main);
		sortPairs(main);
	}
	//displayPair(main);
	return (main);
}

bool PmergeMe::isSorted(std::vector<int> k)
{
	size_t i = 0;
	while (i < k.size() - 1)
	{
		if (!(k[i] < k[i + 1]))
			return false;
		i++;
	}
	return true;
}
void PmergeMe::passArgs()
{
	std::vector<int> cikti;
	if (this->FirstVector.size() == 1)
		cikti = FirstVector;
	else
	{
		pairMake(this->FirstVector);
		// displayPairs(Groups);
		std::vector<int> mm;
		for (size_t i = 0; i < Groups.size(); i++)
		{
			for (size_t m = 0; m < Groups[i].size(); m++)
				mm.push_back(Groups[i][m]);
		}
		//displayArray(mm);
		for (size_t i = 0; i < geriKalan.size(); i++)
		{
			for (size_t m = 0; m < geriKalan[i].size(); m++)
			{
				//std::cout << geriKalan[i][m] << " ";
				ss.push_back(geriKalan[i][m]);
			}
			//std::cout << std::endl;
		}
		std::vector<std::vector<int> > sorted;
		sorted = mergeInsertPairs(mm);
		displayPair(sorted);
		return;
	}
	if (isSorted(cikti) == false)
	{
		std::cout << "Array is not sorted!" << std::endl;
		return ;
	}
	displayArray(cikti);
	std::cout << "Final count of comparison : "<<this->counter << std::endl;
}
// DEQUE

size_t PmergeMe::binarySearchD(const std::deque<int>& arr, int value)
{
	size_t low = 0;
	size_t high = arr.size();
	while (low < high)
	{
		this->counterD++;
		size_t mid = low + (high - low) / 2;
		if (arr[mid] < value)
			low = mid + 1;
		 else
			high = mid;
	}
	return low;
}
size_t PmergeMe::optimizedBinarySearchD(const std::deque<int>& arr, int value, size_t maxIndex)
{
	size_t low = 0;
	size_t high = maxIndex;
	while (low < high)
	{
		this->counterD++;
		size_t mid = (low + (high)) / 2;
		if (arr[mid] < value)
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}
int PmergeMe::eeehD(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	int prev = 1;	//	jacobsthal(1)
	int prev_prev = 0;	//jacobsthal(0)
	int current;

	for (int i = 2; i <= n; ++i)
	{
		current = prev + 2 * prev_prev;
		prev_prev = prev;
		prev = current;
	}
	return current;
}

std::deque<int> PmergeMe::generateJacobInsertionSequenceD(std::deque<int> &pend)
{
	std::deque<int> jacobs;
	size_t index = 3;
	size_t jcobstalIndex;

	while ((jcobstalIndex = eeehD(index)) <= pend.size())
	{
		jacobs.push_back(jcobstalIndex);
		index++;
	}
	return jacobs;
}

void PmergeMe::displayArrayD(std::deque<int> &a)
{
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}
std::deque<int> PmergeMe::generatePositionsD(std::deque<int> &pend)
{
	std::deque<int> positions;
	std::deque<int> jacobNumbers = generateJacobInsertionSequenceD(pend);

	size_t sonposition = 1;

	for (size_t i = 0; i < jacobNumbers.size(); i++)
	{
		size_t val = jacobNumbers[i];
		positions.push_back(val);
		
		size_t pos = val - 1;
		while (pos > sonposition) {
			positions.push_back(pos);
			pos--;
		}
		sonposition = val;
	}

	size_t val = pend.size();
	while (val > sonposition)
	{
		positions.push_back(val);
		val--;
	}

	return positions;
}

void PmergeMe::displayPairsD(std::deque<std::deque<int>  > &temp)
{
	for (size_t i = 0; i < temp.size(); i++)
	{
		for(size_t m = 0; m < temp[i].size() - 1; m += 2)
			std::cout << "[ " << temp[i][m] << " , " << temp[i][m + 1] << " ]" << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::swapPairsD(std::deque<std::deque<int> > &k, size_t level)
{
	// 1. Base Case: Eğer level, k.size()'dan büyükse, kalanları işle
	if (level > k.size()) {
		// Kalan elemanların başlangıç indeksi
		size_t remaining_start = (k.size() / (level / 2)) * (level / 2);
		
		// Kalan elemanları geriKalan'a ekle
		for (size_t i = remaining_start; i < k.size(); ++i)
			geriKaland.push_back(k[i]);
		
		// Eklenen elemanları ana vektörden çıkar
		k.erase(k.begin() + remaining_start, k.end());
		return;
	}

	// 2. Pair'leri karşılaştır ve swap et
	for (size_t i = 0; i < k.size(); i += level)
	{
		size_t group1_end = i + (level / 2);
		size_t group2_end = i + level;
		
		// Grup sınırlarını kontrol et
		if (group1_end >= k.size()) break;
		if (group2_end > k.size()) group2_end = k.size();
		
		// Sadece ilk elemanları karşılaştır
		this->counterD++;
		if (k[i][0] < k[group1_end][0])
		{
			// Swap işlemi
			for (size_t j = 0; j < (level / 2) && (group1_end + j) < k.size(); ++j)
				std::swap(k[i + j], k[group1_end + j]);
		}
	}
	// 3. Bir sonraki level için recursive çağrı
	swapPairsD(k, level * 2);
}

void PmergeMe::pairMakeD(std::deque<int> &arr)
{
	if (arr.size() <= 1)
		return ;
	size_t i = 0;
	while (i < arr.size() - 1)
	{
		this->counterD++;
		std::deque<int> temp;
		if (arr[i] > arr[i + 1])
		{
			temp.push_back(arr[i]);
			temp.push_back(arr[i + 1]);
			this->Groupsd.push_back(temp);
			i += 2;
		}
		else
		{
			temp.push_back(arr[i + 1]);
			temp.push_back(arr[i]);
			this->Groupsd.push_back(temp);
			i += 2;
		}
	}
	if (i != arr.size())
		RestDeque.push_back(arr[i]);
	//displayPairsD(this->Groupsd);
	//std::cout << "yukaridaki ilk hali" << std::endl;
	return (swapPairsD(this->Groupsd, 2));
}

std::deque<int> PmergeMe::sortD(std::deque<std::deque<int> > &temp)
{
	std::deque<int> main;
	std::deque<int> pend;
	for (size_t i = 0; i < temp.size(); i++)
	{
		main.push_back(temp[i][0]);
		pend.push_back(temp[i][1]);
	}
	
	size_t eklenti;
	eklenti = 0;
	main.insert(main.begin(), pend[0]);
	eklenti++;
	// displayArray(main);
	// displayArray(pend);
	std::deque<int> aa = generatePositionsD(pend);
	std::deque<int>::iterator it;
	int target;
	size_t maxpos;
	size_t currentpos;
	for (it = aa.begin(); it != aa.end(); it++)
	{
		target = pend.at(*it - 1);
		//std::cout << "jacob index : " << *it << std::endl;
		maxpos = *it - 1 + eklenti;
		if (maxpos >= main.size())
			maxpos  = main.size();
		//std::cout << "MAX index : " << maxpos << std::endl;
		currentpos = optimizedBinarySearchD(main, target, maxpos);
		//std::cout << "inserting in  main index : " << currentpos << " the number " << target << std::endl;
		main.insert(main.begin() + currentpos, target);
		eklenti++;
	}
	for (size_t i = 0; i < RestDeque.size(); i++)
	{
		int m = binarySearchD(main, RestDeque[i]);
		main.insert(main.begin()+ m, RestDeque[i]);
	}
	return (main);
}


size_t PmergeMe::optimizedBinarySearch1D(std::deque<std::deque<int> >& arr, std::deque<int> value, size_t maxIndex)
{
	size_t low = 0;
	size_t high = maxIndex;
	while (low < high)
	{
		this->counterD++;
		size_t mid = low + (high - low) / 2;
		
		if (arr[mid][0] < value[0]) 
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}
size_t PmergeMe::binarySearch1D(const std::deque<std::deque<int> > & arr, std::deque<int> value)
{
	size_t low = 0;
	size_t high = arr.size();
	while (low < high)
	{
		this->counterD++;
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

void PmergeMe::displayPairD(std::deque<std::deque<int> > &s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		for(size_t m = 0; m < s[i].size(); m++)
			std::cout << s[i][m] << " ,";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::sortPairsD(std::deque<std::deque<int> > &bakalim)
{
	// if (bakalim.size() < 8)
	// 	return;
	std::deque<std::deque<int> > main;
	std::deque<std::deque<int> > pend;
	for (size_t i = 0; i < bakalim.size() - 1; i += 2)
	{
		main.push_back(bakalim[i]);
		pend.push_back(bakalim[i + 1]);
	}
	size_t eklenti;
	eklenti = 0;
	main.insert(main.begin(), pend[0]);
	// eklenti++;
	if (ssd.size() >= bakalim[0].size())
		{
			std::deque<int> z;
			size_t elements_to_take = std::min(ssd.size(), bakalim[0].size());
			z.insert(z.end(), ssd.begin(), ssd.begin() + elements_to_take);
			ssd.erase(ssd.begin(), ssd.begin() + elements_to_take);
			
			size_t insert_pos = binarySearch1D(main, z);
			main.insert(main.begin() + insert_pos, z);
			if (ssd.size() >= bakalim[0].size())
			{
			std::deque<int> z;
			size_t elements_to_take = std::min(ssd.size(), bakalim[0].size());
			z.insert(z.end(), ssd.begin(), ssd.begin() + elements_to_take);
			ssd.erase(ssd.begin(), ssd.begin() + elements_to_take);
			
			size_t insert_pos = binarySearch1D(main, z);
			main.insert(main.begin() + insert_pos, z);
			}
			// eklenti++;
		}
	
	std::deque<int> minimain;
	std::deque<int> minipend;
	for (size_t i = 0; i < main.size(); i++)
		minimain.push_back(main[i][0]);
	for (size_t i = 0; i < pend.size(); i++)
		minipend.push_back(pend[i][0]);
		// //displayArray(minimain);
		// displayArray(minipend);
	std::deque<int> aa = generatePositionsD(minipend);
	std::deque<int>::iterator it;
	int target;
	size_t maxpos;
	size_t currentpos;
		
	for (it = aa.begin(); it != aa.end(); it++)
	{
		target = minipend.at(*it - 1);
			//std::cout << "jacob index : " << *it << std::endl;
		maxpos = *it + eklenti;
		if (maxpos >= main.size() - 1)
			maxpos  = main.size() - 1;
		currentpos = optimizedBinarySearchD(minimain, target, maxpos);
		minimain.insert(minimain.begin() + currentpos, target);
		main.insert(main.begin() + currentpos, pend[*it - 1]);
		eklenti++;
	}
	//displayPairs(main);
	bakalim.clear();
	bakalim = main;
}


std::deque<std::deque<int> > PmergeMe::divideArrayD(std::deque<int> &m)
{
	size_t mid = m.size() / 2;
	std::deque<int> a(m.begin(), m.begin() + mid);
	std::deque<int> b(m.begin() + mid, m.end());
	std::deque<std::deque<int> > result;
	result.push_back(a);
	result.push_back(b);
	return result;
}

void PmergeMe::splitAndUpdateD(std::deque<std::deque<int> >& arr)
{
	std::deque<std::deque<int> > newArr;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i].size() >= 2) {
			// İlk yarıyı al
			std::deque<int> firstHalf(arr[i].begin(), arr[i].begin() + arr[i].size()/2);
			// İkinci yarıyı al
			std::deque<int> secondHalf(arr[i].begin() + arr[i].size()/2, arr[i].end());
			
			newArr.push_back(firstHalf);
			newArr.push_back(secondHalf);
		} else {
			// Eğer tek elemanlıysa olduğu gibi ekle
			newArr.push_back(arr[i]);
		}
	}
	arr = newArr;
}
std::deque<std::deque<int> > PmergeMe::mergeInsertPairsD(std::deque<int> & temp)
{
	std::deque<std::deque<int> > main;
	if (temp.size() < 4)
	{
			main.push_back(temp);
			//displayPairD(main);
			return (main);
	}
	std::deque<std::deque<int> > karisik = divideArrayD(temp);
	if (temp.size() < 8)
	{
		main.push_back(karisik[1]);
		main.push_back(karisik[0]);
		if (ssd.size() >= main[0].size())
		{
			int m = binarySearch1D(main, ssd);
			main.insert(main.begin() + m, ssd);
		}
		return (main);
	}
	std::deque<std::deque<int> > a = divideArrayD(karisik[0]);
	std::deque<std::deque<int> > b = divideArrayD(karisik[1]);
	if (a.size() + b.size() == 4)
	{
		main.push_back(b[1]);
		main.push_back(b[0]);
		main.push_back(a[0]);
		if (ssd.size() >= a[0].size())
		{
			std::deque<int> z;
			size_t elements_to_take = std::min(ssd.size(), a[0].size());
			z.insert(z.end(), ssd.begin(), ssd.begin() + elements_to_take);
			ssd.erase(ssd.begin(), ssd.begin() + elements_to_take);
			
			size_t insert_pos = binarySearch1D(main, z);
			main.insert(main.begin() + insert_pos, z);
			if (ssd.size() >= a[0].size())
			{
			std::deque<int> z;
			size_t elements_to_take = std::min(ssd.size(), a[0].size());
			z.insert(z.end(), ssd.begin(), ssd.begin() + elements_to_take);
			ssd.erase(ssd.begin(), ssd.begin() + elements_to_take);
			
			size_t insert_pos = binarySearch1D(main, z);
			main.insert(main.begin() + insert_pos, z);
			}
		}
		int k = optimizedBinarySearch1D(main, a[1], 3);
		main.insert(main.begin() + k , a[1]);
		//displayPairs(main);
	}
	while (main[0].size() != 2)
	{
		splitAndUpdateD(main);
		sortPairsD(main);
	}
	return (main);
}
void PmergeMe::passArgsD()
{
	std::deque<int> cikti;
	if (this->FirstDeque.size() == 1)
		cikti = FirstDeque;
	else
	{
		pairMakeD(this->FirstDeque);
		//displayPairsD(Groupsd);
		std::deque<int> mm;
		for (size_t i = 0; i < Groupsd.size(); i++)
		{
			for (size_t m = 0; m < Groupsd[i].size(); m++)
				mm.push_back(Groupsd[i][m]);
		}
		//displayArray(mm);
		for (size_t i = 0; i < geriKaland.size(); i++)
		{
			for (size_t m = 0; m < geriKaland[i].size(); m++)
			{
				//std::cout << geriKaland[i][m] << " ";
				ssd.push_back(geriKaland[i][m]);
			}
		}
		std::deque<std::deque<int> > sorted;
		sorted = mergeInsertPairsD(mm);
		cikti = sortD(sorted);
	}
	//displayArrayD(cikti);
	//std::cout << "Final count of comparison : "<<this->counterD << std::endl;
}


PmergeMe::~PmergeMe() {}
