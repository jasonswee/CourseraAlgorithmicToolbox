#include <iostream>
#include <vector>
#include <cassert>
// std::sort
#include <algorithm>
// std::greater
#include <functional>
//bitset
#include <bitset>
// std::pow
#include <cmath>

#include <iterator>

using std::vector;
void print_this(vector<int> value)
{ 
  // std::cout << "Start this: " << std::endl;
  for(auto i:value)
  {
    std::cout << i << ", ";
  }
  std::cout << std::endl;
}
int optimal_weight_fast(int W, const vector<int> &w, vector<int> *leftovers) 
{
  vector<int> wcopy = w;
  std::sort(wcopy.begin(), wcopy.end());

  vector<int> sum(W+1,0);
  vector<vector<int>> weights(sum.size(), wcopy);

  // print_this(sum);
  for (int irow = 1; irow <= wcopy.size(); irow++)
  {
    vector<int> prev_sum = sum;
    vector<vector<int>> prev_weights = weights;
    for (int ivet = 1; ivet < sum.size(); ivet++)
    {
      int max_sum = prev_sum[ivet];
      int weights_to_remove = -1;
      for (auto i:wcopy)
      {
        int check_index = ivet-i;
        if (check_index < 0) break;

        int check_new_sum = prev_sum[check_index] + i;
        if (check_new_sum > ivet) continue;

        // check if the weight exist, if don't exist continue
        if (std::find(prev_weights[check_index].begin(), prev_weights[check_index].end(), i) == prev_weights[check_index].end()) continue;

        if (check_new_sum == ivet)
        {
          max_sum = ivet;
          weights_to_remove = i;
          weights[ivet] = prev_weights[check_index];
          break;
        }
        else if (check_new_sum > max_sum)
        {
          max_sum = check_new_sum;
          weights_to_remove = i;
          weights[ivet] = prev_weights[check_index];
        }
      }

      // Finish checking all the weights
      // Now removing the weights accordingly
      if (weights_to_remove != -1)
      {
        sum[ivet] = max_sum;
        auto it = std::find(weights[ivet].begin(), weights[ivet].end(), weights_to_remove);
        int index = it - weights[ivet].begin();
        weights[ivet].erase(weights[ivet].begin() + index);
      }

    }
    // print_this(sum);
    if (sum[sum.size()-1] == W) break;
  }
  *leftovers = weights[weights.size()-1];
  // std::cout << "Print leftovers\n";
  // print_this(*leftovers);
  return sum[sum.size()-1];
}
int partition3(vector<int> &A) {
  //write your code here
  // If less than 3
  if (A.size() < 3) return 0;

  int sum = 0;
  for (auto i:A)
    sum+=i;
  // If not divisable by 3
  if (sum % 3 != 0) return 0; 
  int div3 = sum / 3;

  vector<int> A_copy = A;
  std::sort(A_copy.begin(), A_copy.end(), std::greater<int>());

  // If largest element bigger than div3, exit
  if (A_copy[A_copy.size() - 1] > div3) return 0;


  std::vector<int> part2;
  if (optimal_weight_fast(div3, A_copy, &part2) != div3) return 0;
  // std::cout<<"Left weights\n";
  // print_this(part2);
  std::vector<int> part3;
  if (optimal_weight_fast(div3, part2, &part3) != div3) return 0;
  // std::cout<<"this runned"<<std::endl;

  return 1;
}

void test_solution()
{
  std::vector<int> input;
  input={3,3,3,3};
  assert(partition3(input) == 0);
  input={40};
  assert(partition3(input) == 0);
  input={17,59,34,57,17,23,67,1,18,2,59};
  assert(partition3(input) == 1);
  input={1,2,3,4,5,5,7,7,8,10,12,19,25};
  assert(partition3(input) == 1);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
  // test_solution();
}
