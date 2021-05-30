#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <map>

using std::vector;
int random_func(int low, int high)
{
  return rand() % high + low;
}
int get_majority_element(vector<int> &a, int left, int right) 
{
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here
  int current_element, count;
  for (int i = 0; i < right; i++)
  {
    current_element = a[i];
    count = 0;
    for (int j = 0; j < right; j++)
    {
      if (a[j] == current_element)
      {
        count++;
      }
    }
    if (count > right/2)
    {
      return a[i];
    }
  }

  return -1;
}
int get_majority_element_fast(vector<int> &a, int left, int right) 
{
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  
  std::map<int, int> m;
  for (int i = 0; i < right; i++)
  {
    m[a[i]]++;
    if (m[a[i]] > right/2)
      return a[i];
  }

  return -1;
}
int if_get_majority_element(vector<int> &a, int left, int right)
{
  int value = get_majority_element(a, 0, a.size());
  std::cout << "Naive Majority element: " << value << std::endl;
  return (value != -1);
}

int if_get_majority_element_fast(vector<int> &a, int left, int right)
{
  int value = get_majority_element_fast(a, 0, a.size());
  std::cout << "Fast Majority element: " << value << std::endl;
  return (value != -1);
}
void test_solution()
{
  std::vector<int> input = {2,3,9,2,2};
  auto start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element(input, 0, input.size()) == 1);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element_fast(input, 0, input.size()) == 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
  
  std::cout << "\n" << std::endl;
  input = {1,2,3,4};
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element(input, 0, input.size()) == 0);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element_fast(input, 0, input.size()) == 0);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

  std::cout << "\n" << std::endl;
  input = {1,2,3,1};
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element(input, 0, input.size()) == 0);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element_fast(input, 0, input.size()) == 0);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

  std::cout << "\n" << std::endl;
  input = {1,1,1,3,1,9,9,9,9,9,9,9};
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element(input, 0, input.size()) == 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  assert(if_get_majority_element_fast(input, 0, input.size()) == 1);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

  std::cout << "\n\n" << std::endl;
  input.clear();
  int n = random_func(1, std::pow(10,5));
  for (int i = 0; i < n ; i++)
  {
    input.push_back(random_func(1,std::pow(10,9)));
  }
  start = std::chrono::high_resolution_clock::now();
  int value_naive = if_get_majority_element(input, 0, input.size());
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Naive Time taken: " << duration.count() << " seconds" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  int value_fast = if_get_majority_element_fast(input, 0, input.size());
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  std::cout << "Fast Time taken: " << duration.count() << " seconds" << std::endl;
  assert(value_naive == value_fast);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  // std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
  std::cout << (get_majority_element_fast(a, 0, a.size()) != -1) << '\n';

  // int input = 5;
  // int value = (float)input/2;
  // std::cout <<value << '\n';

  // test_solution();
}
