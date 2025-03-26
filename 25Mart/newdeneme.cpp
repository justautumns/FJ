#include <vector>
#include <iostream>

int jacobsthal(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

std::vector<int> generateJacobInsertionSequence(std::vector<int> &pend) {
    std::vector<int> jacobs;
    int index = 3;
    int jcobstalIndex;
    
    while ((jcobstalIndex = jacobsthal(index)) <= pend.size()) { // <= kullan
        jacobs.push_back(jcobstalIndex);
        index++;
    }
    return jacobs;
}

std::vector<int> generatPositions(std::vector<int> &pend) {
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
    
    // Kalan sayıları ekleyin (azalan sırada)
    size_t val = pend.size();
    while (val > lastPos) {
        positions.push_back(val);
        val--;
    }
    
    return positions;
}

void displayArray(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (i != 0) std::cout << " , ";
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> k = {14, 20, 27, 19, 2, 76, 66, 234, 35, 13, 99, 212312 ,1, 2,4 ,18, 11, 199, 19, 30, 21, 89, 4, 12312, 1616,16, 16}; // 11 eleman
    std::vector<int> jacobs = generatPositions(k);
    displayArray(jacobs);
    return 0;
}
