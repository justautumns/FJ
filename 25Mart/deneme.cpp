#include <iostream>
#include <vector>

void displayArray(std::vector<int> &a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << " , ";
	}
	std::cout << std::endl;
}

int eeeh(int n)
{if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long prev2 = 0, prev1 = 1, current;
    for (int i = 2; i <= n; ++i) {
        current = prev1 + (prev2 << 1);  // Use bitwise shift instead of multiplication by 2
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}


std::vector<int> generateJacobsthalSequence(int n) {
    std::vector<int> jacobsthal;
    if (n == 0) return jacobsthal;
    jacobsthal.push_back(0);
    if (n == 1) return jacobsthal;
    jacobsthal.push_back(1);
    
    for (int i = 2; i < n; ++i) {
        jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
    }
    return jacobsthal;
}


// std::vector<int> generateJacobInsertionSequence(std::vector<int> &k)
// {
// 	size_t size = k.size();
// 	size_t jcobstalIndex;
// 	int index = 3;
// 	std::vector<int> temp;

// 	while ((jcobstalIndex = eeeh(index)) < size)
// 	{
// 		temp.push_back(jcobstalIndex);
// 		index++;
// 	}
// 	return temp;
// }
// std::vector<int> generatPositions(std::vector<int> &k)
// {
// 	if (k.empty())
// 		throw std::runtime_error("the rest array is empty");
//         std::vector<int> poses = generateJacobsthalSequence(k.size());
//         displayArray(poses);
//         std::vector<int> fnpos;
//        size_t i = 3;
//        int val = 0;

//        while (i < poses.size())
//        {
//             fnpos.push_back(poses[i]);
//             int value = poses[i] - 1; 
//             fnpos.push_back(value);
//             int pos = i - 1;
//             while (value > poses[i - 3])
//             {
//                 if (value != poses[i - 2] || value != poses[i - 1])
//                     fnpos.push_back(value);
//                 value--;
//             }
//         i++;
//        }
//        return fnpos;
// }


// Pozisyonları üreten fonksiyon
std::vector<int> generatePositions(std::vector<int> &k) {
    if (k.empty())
        throw std::runtime_error("the rest array is empty");

    std::vector<int> poses = generateJacobsthalSequence(k.size());
    std::vector<int> fnpos;

    for (size_t i = 3; i < poses.size(); ++i) {
        fnpos.push_back(poses[i]);
        int value = poses[i] - 1;

        // Önceki Jacobsthal değerine kadar ekle
        int lower_bound = (i > 0) ? poses[i - 1] : 2;
        while (value > lower_bound) {
            fnpos.push_back(value);
            value--;
        }
    }
    return fnpos;
}
int main()
{
    std::vector<int> k = {5, 2, 3, 12, 15, 21 ,3, 23};
    std::vector<int> jacobs = generatePositions(k);
    displayArray(jacobs);
}