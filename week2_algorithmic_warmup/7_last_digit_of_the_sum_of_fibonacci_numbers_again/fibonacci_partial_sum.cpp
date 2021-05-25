#include <iostream>
#include <vector>
#include <cassert>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) 
{
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) 
{
    std::vector<long long> path;
    int size_of_period = 0;
    int repeated_from = 0;
    int repeated_to = 0;
    int num_of_period = 0;

    long long sum = 0;
    long long period_sum = 1;
    long long rem = 0;

    long long current = 0;
    long long next  = 1;
    long long tmp  = 0;
    path.push_back(0);
    path.push_back(1);

    if (from < 2)
        sum = 1;
        
    if (to == 0)
        return 0;
    for (long long i = 2; i <= to; ++i) {
        tmp = next;
        next += current%10;
        current = tmp;
        
        if  (i >= from)
        {
            sum += next;
            // std::cout << "i: " << i  << " Sum: " << sum << " ";
        }
        if (i < 60) period_sum += next % 10;            
        path.push_back(next%10);
        // std::cout << "i: " << i << " Current: " << next << std::endl;
        if (path.back() == 1 && path.at(path.size()-2) == 0)
        {
            size_of_period = i-1;
            break;
        }
    }
    if (size_of_period != 0)
    {
        repeated_from = from % size_of_period;
        repeated_to = to % size_of_period;
        num_of_period = (int)(to - from)/ size_of_period;
        if (num_of_period > 0)
            num_of_period -= 1;
        // if ()
        //     repeated_from = 0;
        rem = (period_sum % 10 * num_of_period) % 10;
        sum=0;
        // std::cout << "\nSum of period: " << period_sum;
        for (int i = 0; i <= repeated_to; i++)
        {
            sum += path[i];
            sum%=10;
            // std::cout << "\ni: " << i;
            // std::cout << " Sum: " << sum;
            // std::cout << " path: " << path[i];
        }
        // std::cout << std::endl;
        for (int i = repeated_from; i <= 60; i++)
        {
            sum += path[i];
            sum%=10;
            // std::cout << "\ni: " << i;
            // std::cout << " Sum: " << sum;
            // std::cout << " path: " << path[i];
        }
        sum += rem;
        // std::cout << "\nSum of period: " << period_sum;
        // std::cout << "\nNumber of period: " << num_of_period;
        // std::cout << "\nSize of period: " << size_of_period;
        // std::cout << "\nRepeated from: " << repeated_from;
        // std::cout << "\nRepeated to: " << repeated_to;
    }
    sum %= 10;
    // std::cout << "\nResult: " << sum << "\n";
    return sum;
}

void test_solution()
{
    assert(get_fibonacci_partial_sum_fast(3,7)==1);
    assert(get_fibonacci_partial_sum_fast(10,10)==5);
    assert(get_fibonacci_partial_sum_fast(10,200)==2);
    assert(get_fibonacci_partial_sum_fast(0,239)==0);
    assert(get_fibonacci_partial_sum_fast(1,2)==2);
    assert(get_fibonacci_partial_sum_fast(0,0)==0);
    assert(get_fibonacci_partial_sum_fast(1234,12345)==8);
}

int main() {
    long long from = 0, to = 239;
    std::cin >> from >> to;
    // std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
    // test_solution();
}
