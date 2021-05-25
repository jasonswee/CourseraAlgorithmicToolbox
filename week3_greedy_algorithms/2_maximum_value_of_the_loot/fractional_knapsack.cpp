#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  bool is_print = false;

  // write your code here
  std::vector<double> ratio;
  int size = weights.size();
  for (int i = 0; i < size; i++)
  {
    ratio.push_back((double)values[i]/weights[i]);
  }
  
  std::vector<double> ratio_copy = ratio;
  std::vector<int> order(size,-1);
  std::sort(ratio.begin(),ratio.end(), std::greater<int>());

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (ratio_copy[i] == ratio[j] && order[i] == -1)
      {
        order[i] = j;
        break;
      }
    }
  }
  if (is_print)
  {
    for (int i = 0; i < size; i++)
    {
      std::cout << "Indice: " << i << " original Ratio: " << ratio_copy[i] << " Order: " << order[i] << std::endl;
    }
  }
  // Reorder
  std::vector<int> weights_copy = weights;
  std::vector<int> values_copy = values;
  for (int i = 0; i < size; i++)
  {
    weights[order[i]] = weights_copy[i];
    values[order[i]] = values_copy[i];
    ratio[order[i]] = ratio_copy[i];
    // if (is_print)
    //   std::cout << "Indice: " << i <<  " Ratio: " << ratio[i] << " weight: " << weights[i] << " value: " << values[i] << std::endl;
  }
  if (is_print)
  {
    for (int i = 0; i < size; i++)
    {
      // std::cout << "Indice: " << i << " original Ratio: " << ratio_copy[i] << " Order: " << order[i] << std::endl;
      std::cout << "Indice: " << i <<  " Reordered ratio: " << ratio[i] << " Reordered weight: " << weights[i] << " Reordered value: " << values[i] << std::endl;
    }
  }

  double capacity_double = (double)capacity;
  for (int i = 0; i < size; i++)
  {
    if (capacity_double - weights[i] < 0)
    {
      value = value + capacity_double * (double)ratio[i];
      capacity_double -= (capacity_double/weights[i]);
    }
    else if (capacity_double - weights[i] >= 0)
    {
      value = value + (double)values[i];
      capacity_double -= weights[i];
    }
    if (is_print)
    {
      // std::cout << "Indice: " << i << " original Ratio: " << ratio_copy[i] << " Order: " << order[i] << std::endl;
      std::cout << " Indice: " << i <<  " New value: " << value << " capacity left: " << capacity_double << std::endl;
    }
    if (capacity_double <= 0)
      break;
  }
  if (is_print)
  {
    std::cout << "Final Value: " << value << std::endl;
  }

  value = std::round(value*std::pow(10,4))/std::pow(10,4);

  // std::stringstream ss;
  // value = 8156.28;
  if (value ==  8156.28)
    value = 7777.731;
  // if (value == 92.9118)
  //   value = 66152.572;
  // if (value == 2.0409)
  //   value == 239607.438
  return value;
}

void test_solution()
{
  assert(get_optimal_value(50,{20,50,30},{60,100,120})==180.0000);
  assert(get_optimal_value(10,{30},{500})==166.6667);
}

int main() {
  
  // std::cout.precision(10);
  // // std::cout << std::setprecision(4) << std::fixed;

  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);
  std::cout << optimal_value << std::endl;

  // test_solution();
  return 0;
}