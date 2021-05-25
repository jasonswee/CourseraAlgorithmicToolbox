#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>

long long MaxPairwiseProduct(const std::vector<int>& const_numbers) {
    long long max_product = 0;
    std::vector<int> numbers = const_numbers;
    std::sort((numbers).begin(), numbers.end(), std::greater<int>());

    max_product = static_cast<long long>(numbers[0]) * static_cast<long long>(numbers[1]);
    /*int n = numbers.size();
    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                static_cast<long long>(numbers[first]) * static_cast<long long>(numbers[second]));
        }
    }*/
    return max_product;
}

int main() {
    int n;
    
    /*
    std::vector<int> numbers={100000,90000};
    
    std::cout << numbers[0] << "\n" << numbers[1];
    */
    
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        
        std::cin >> numbers[i];
    }
    
    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
  