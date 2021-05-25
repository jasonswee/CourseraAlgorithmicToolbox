#include <iostream>
#include <vector>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
        std::cout << sum % 10 << " ";
    }

    return sum % 10;
}
int fibonacci_sum_fast(long long n) 
{
    std::vector<long long> path;
    int size_of_period = 0;
    int repeated_position = 0;
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    // std::cout << "0 1 ";
    path.push_back(0);
    path.push_back(1);
    
    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous % 10;
        previous = current;
        current = tmp_previous + current;
        sum += current % 10;
        sum = sum % 10;
        // std::cout << sum << " ";
        
        path.push_back(sum);
        if (path.back() == 1 && path.at(path.size()-2) == 0)
        {
            size_of_period = i + 1;
            break;
        }
    }
    if (size_of_period != 0)
    {
        repeated_position = n % size_of_period;
        sum = path[repeated_position];
    }
    
    // std::cout << "\nSum: " << sum << "\n";
    return sum;
}
void test_solution()
{
    //assert(fibonacci_sum_fast(832564823476));
}
int main() {
    long long n = 832564823476;
    std::cin >> n;
    // std::cout << fibonacci_sum_naive(n);
    std::cout << fibonacci_sum_fast(n);
}
