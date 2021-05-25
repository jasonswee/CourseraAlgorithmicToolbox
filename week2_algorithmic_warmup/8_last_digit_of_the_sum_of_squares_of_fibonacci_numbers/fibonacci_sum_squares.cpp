#include <iostream>
#include <vector>
#include <cassert>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}
int fibonacci_sum_squares_fast(long long n) 
{
    if (n<2) return n;
    int size_of_period = 0, remainder=0, quotient =0;
    long long output = 0, sum_t = 1;
    std::vector<long long> path, path_s;
    path.push_back(0);
    path.push_back(1);
    path_s.push_back(0);
    path_s.push_back(1);
        // std::cout 
        // << "I: 0 normal: 0 " << std::endl;
        // std::cout 
        // << "I: 1 normal: 1 " << std::endl;
    for (int i=2;i<=n;i++)
    {
        path.push_back((path.back() + path.at(path.size()-2)) % 10);
        path_s.push_back((path.back()*path.back())%10);
        sum_t += path_s.back();
        output = sum_t;


        // std::cout 
        // << "I: " << i << " "
        // << "normal: " << path.back() << " "
        // << "square: " << path_s.back() << " "
        // << "sum_t: " << sum_t  << " "
        // << "output: " << output
        // << std::endl;

        // if (path.back() == 1 && path.at(path.size()-2) == 0)
        if (i==60)
        {
            size_of_period=i;
            break;
        }
    }
    if (size_of_period !=0)
    {
        output = 0;
        remainder = n % size_of_period;
        // quotient = n / size_of_period;
        // if (quotient >0) quotient -= 1;
        for (int i = 0; i <= remainder; i++)
        {
            output += path_s[i];
        }
        // output+=(sum_t*quotient);
    }
    output %=10;

    // std::cout << "Remaineder: " << remainder << std::endl;
    // std::cout << "Output: " << output << std::endl;
    return output;
}
void test_solution()
{
    assert(fibonacci_sum_squares_fast(7)==3);
    assert(fibonacci_sum_squares_fast(73)==1);
    assert(fibonacci_sum_squares_fast(1234567890)==0); 
    for (int i=0;i<30;i++)
    {
        assert(fibonacci_sum_squares_fast(i)==fibonacci_sum_squares_naive(i));
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    // std::cout << fibonacci_sum_squares_naive(n);
    std::cout << fibonacci_sum_squares_fast(n);
    test_solution();
}
