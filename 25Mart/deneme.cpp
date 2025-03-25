#include <vector>
#include <iostream>

class PmergeMe {
public:
    static std::vector<std::vector<int>> denemeSort(std::vector<std::vector<int>>& temp);
    static void displayPairs(const std::vector<std::vector<int>>& vec2D);
};

std::vector<std::vector<int>> PmergeMe::denemeSort(std::vector<std::vector<int>>& temp) {
    std::vector<std::vector<int>> result;
    if (temp.size() <= 1) {
        return temp;
    } else {
        size_t mid = temp.size() / 2;
        std::vector<std::vector<int>> firstHalf(temp.begin(), temp.begin() + mid);
        std::vector<std::vector<int>> secondHalf(temp.begin() + mid, temp.end());

        displayPairs(firstHalf);
        displayPairs(secondHalf);

        if (firstHalf.size() + secondHalf.size() == 4)
        {
            result.insert(result.end(), firstHalf.begin(), firstHalf.end());
            result.insert(result.end(), secondHalf[1]);
            return result;
        }
        // Recursive olarak bölme işlemi
        std::vector<std::vector<int>> firstSplit = denemeSort(firstHalf);
        std::vector<std::vector<int>> secondSplit = denemeSort(secondHalf);

        std::cout << firstHalf.size() << std::endl;
        std::cout << secondHalf.size() << std::endl;
        // Sonuçları birleştir
    }
    return result;
}

void PmergeMe::displayPairs(const std::vector<std::vector<int>>& vec2D) {
    for (const auto& vec : vec2D) {
        for (int val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----" << std::endl;
}

int main() {
    std::vector<std::vector<int>> temp = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    };

    std::vector<std::vector<int>> result = PmergeMe::denemeSort(temp);

    std::cout << "Sorted 2D vector:" << std::endl;
    PmergeMe::displayPairs(result);

    return 0;
}
