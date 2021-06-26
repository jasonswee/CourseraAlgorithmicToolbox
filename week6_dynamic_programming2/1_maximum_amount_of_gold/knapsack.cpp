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
int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
}

int optimal_weight_fast(int W, const vector<int> &w) 
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
    if (sum[sum.size()-1] == W) return W;
  }
  return sum[sum.size()-1];
}
int optimal_weight_fast_old(int W, const vector<int> &w) 
{
  int weight_size = w.size();
  int max_combi = 1;
  vector<int> weights = w;
  vector<int> sum;
  std::bitset<300> combi = 1;
  for(int i = 1; i < weight_size; i++)
  {
    max_combi+= std::pow(2,i);
  }
  // increase from bit 1 to the max bit
  for (combi = 1; combi.to_ulong() <= max_combi ; combi = combi.to_ulong() + 1)
  {
    std::bitset<300> current_combi = combi;
    int current_sum = 0;
    // check each bit until none left
    for(int i = 0; current_combi.any(); i++)
    {
      // if set
      if(current_combi.test(i))
      {
        current_sum += weights[i];
        current_combi.set(i,false);
        if (current_sum == W) return W;
        if (current_sum > W) break;
      }
    }
    sum.push_back(current_sum);
  }
  std::sort(sum.begin(),sum.end(),std::greater<int>());
  for (auto i:sum)
  {
    if (i <= W) return i;
  }
  return 0;
}
void test_solution()
{
  std::cout << optimal_weight_fast(10, {1, 4, 8});
  assert(optimal_weight_fast(10, {1, 4, 8}) == 9);
  assert(optimal_weight_fast(10, {2, 5, 5, 9}) == 10);
  assert(optimal_weight_fast(15, {1, 7, 5, 2, 9}) == 15);
  assert(optimal_weight_fast(20, {5, 7, 12, 18}) == 19);
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight_fast(W, w) << '\n';
  // test_solution();
}
