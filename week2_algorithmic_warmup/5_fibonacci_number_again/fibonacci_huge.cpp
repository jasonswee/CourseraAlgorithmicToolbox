#include <iostream>
#include <cassert>
#include <vector>
#include <climits>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}
long long get_fibonacci_huge_fast(long long n, long long m) {
    std::vector<long long> path;
    
    int size_of_period = 0;
    bool is_finish_period = false;
    int result;
    int tmp = 0, remainder = 0;
    if (n <= 1)
        return n;

    long long previous = 0;
    std::vector<long long> current;
    bool store_last = false;
        path.push_back(0);
        path.push_back(1);
    for (long long i = 0; i < n - 1; ++i) 
    {
        tmp = path.back() + path.at(path.size() - 2);    
        path.push_back(tmp % m);
        if (path.back() == 1 && path.at(path.size() - 2) == 0)
        {
            size_of_period = i + 1;
            break;
        }
    }
    if (size_of_period != 0)
    {
        remainder = n % size_of_period;
        result =  path[remainder];
    }
    else
        result = path.back();
    // std::cout << "Result: " << result << '\n';
    return result;
}

void test_solution() 
{
    
    assert(get_fibonacci_huge_fast(10, 2) == 1);
    assert(get_fibonacci_huge_fast(14, 3) == 2);
    assert(get_fibonacci_huge_fast(100, 100) == 75);
    assert(get_fibonacci_huge_fast(1000, 100) == 75);
    assert(get_fibonacci_huge_fast(2816213588,239) == 151);
}

int main() {
    long long n, m;
    // n = 100;
    // m = 100;
    std::cin >> n >> m;
    // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
    // std::cout << get_fibonacci_huge_fast(100, 4) << '\n'; 
    // std::cout << get_fibonacci_huge_fast(100, 5) << '\n';
    // std::cout << get_fibonacci_huge_fast(1000, 100) << '\n';
    // test_solution();
} 
