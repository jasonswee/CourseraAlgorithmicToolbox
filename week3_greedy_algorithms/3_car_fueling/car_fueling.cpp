#include <iostream>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int>& stops) {
    // write your code here
    int current_location = 0, required_refill=0;
    std::vector<int> stops_copy;
    std::copy(stops.begin(), stops.end(), std::back_inserter(stops_copy));
    stops_copy.push_back(dist);
    bool is_passed = false;

    // Check 1st furthest refill stop the tank can take
    for (int i=0;i<stops_copy.size(); i++)
    {
        if (i != 0)
        {
            if ((stops_copy[i] - stops_copy[i-1] )> tank)
            return -1;
        }

        // std::cout << "checking distance: " << stops_copy[i] << std::endl;
        // Check destination is within reach from current location
        if (tank > (dist-current_location))
        {
            // std::cout << "Returning refill: " << required_refill << std::endl;
            return required_refill;
        }
        // if passed update
        if (is_passed)
        {
            current_location = stops_copy[i];
            required_refill += 1;
            is_passed =false;
            
            // std::cout << "Saving Current location : " << current_location << std::endl;
            continue;
        }
        // Check if tank can cover this distance
        if ((tank > (stops_copy[i] - current_location)) && !is_passed)
            continue;
        else if (tank < (stops_copy[i] - current_location)) // If tank is less go back to previous
        {
            is_passed = true;
            // std::cout << "Exited location: " << stops_copy[i] << std::endl;
            i-=2;
            // std::cout << "Current location 1: " << current_location << std::endl;
        }
        // std::cout << "Current location 2: " << current_location << std::endl;

        
    }
    return -1;
}

void test_solution()
{
    std::vector<int> test = {200,375, 550, 750};
    std::cout << compute_min_refills(950,400,test) << std::endl;
    assert(compute_min_refills(950,400,test)== 2);
    test ={1,2,5,9};
    std::cout << compute_min_refills(10,3,test) << std::endl;
    assert(compute_min_refills(10,3,test)== -1);
    test ={100,150};
    std::cout << compute_min_refills(200,250,test) << std::endl;
    assert(compute_min_refills(200,250,test)== 0);
}

int main() {
    // int d = 0;
    // cin >> d;
    // int m = 0;
    // cin >> m;
    // int n = 0;
    // cin >> n;

    // vector<int> stops(n);
    // for (size_t i = 0; i < n; ++i)
    //     cin >> stops.at(i);

    // cout << compute_min_refills(d, m, stops) << "\n";

    test_solution();
    return 0;
}
