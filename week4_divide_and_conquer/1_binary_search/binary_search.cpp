#include <iostream>
#include <cassert>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

using std::vector;

int random_func(int low, int high)
{
  return rand() % high + low;
}
int check_previous(const vector<int> &a, int index, int x)
{
  index-=1;
  if (a[index] == x)
    return check_previous(a,index,x);
  else
    return index+1;
}
int binary_search_it(const vector<int> &a, int low, int high, int x) 
{
  // int left = low, right = high;
  //write your code here
  // std::cout << "low: " << low << " high: " << high << std::endl;
  if (high < low)
    return -1; //low - 1; // Return -1
  int mid = low + ((high - low) / 2);
  if (x == a[mid])
  {
    return check_previous(a,mid,x);
    // return mid;
  }
  else if (x < a[mid])
    return binary_search_it(a, low, mid - 1, x);
  else
    return binary_search_it(a, mid + 1, high, x);
}
int binary_search(const vector<int> &a, int x) 
{
  int left = 0, right = (int)a.size(); 
  //write your code here
  vector<int> b = a;
  std::sort(b.begin(),b.end());
  return binary_search_it(b, left, right, x);
}
int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}


void test_solution()
{
  // assert(linear_search({1,5,8,12,13}) == {2,0,-1,0,-1});
  // std::cout << linear_search({1,5,8,12,13},8) << std::endl;
  // std::cout << 15/2 << std::endl;
  assert(linear_search({1,5,8,12,13},8) == binary_search({1,5,8,12,13},8));
  assert(linear_search({1,5,8,12,13},1) == binary_search({1,5,8,12,13},1));
  // std::cout << linear_search({1,5,8,12,13},23) << std::endl;
  // std::cout << binary_search({1,5,8,12,13},23) << std::endl;
  assert(linear_search({1,5,8,12,13},23) == binary_search({1,5,8,12,13},23));
  assert(linear_search({1,5,8,12,13},11) == binary_search({1,5,8,12,13},11));
  assert(linear_search({1,8,8,12,13},8) == binary_search({1,8,8,12,13},8));

  // assert(linear_search({1,5,8,12,13},8) == 2);
}

void test_rand()
{
  int n = random_func(1, 3*std::pow(10,4));
  std::vector<int> a;
  for (int i = 0; i < n ; i++)
  {
    a.push_back(random_func(1,std::pow(10,9)));
  }
  std::sort(a.begin(),a.end());

  int k = random_func(1, std::pow(10,5));
  std::vector<int> b;
  for (int i = 0; i < k ; i++)
  {
    b.push_back(random_func(1,std::pow(10,9)));
  }

  for (int i = 0; i < k ; i++)
  {
    // assert(linear_search(a,b[i]) == binary_search(a,b[i]));
    if (linear_search(a,b[i]) != binary_search(a,b[i]))
    {
      std::cerr << "Index: " << i << " Unmatched key value: " << b[i] << std::endl;
      std::cerr << "Linear search index: " << linear_search(a,b[i]) << std::endl;
      std::cerr << "Binary search index: " << binary_search(a,b[i]) << std::endl;
      break;
    }
    
  }
  // for (int i = 0; i < k ; i++)
  // {
  //   // std::cout << " Testing key value: " << b[i] << std::endl;
  //   try
  //   {
  //     /* code */
  //     assert(linear_search(a,b[i]) == binary_search(a,b[i]));
  //   }
  //   catch(const std::exception& e)
  //   {
  //     std::cerr << e.what() << '\n';
  //     for (int j=0;j<n;j++)
  //     {
  //       std::cerr << a[j] << " ";
        
  //       std::cerr << "\n key value " << b[i];
  //     }
  //     throw "Error";
  //   }
  // }
}
void print_multiple_2(int n, int low)
{
  low-=1;
  for (int i=2;i<(low+n);i*=2)
  {
    std::cout << (i+low) << std::endl;
  }
}
int main() {
  // int n;
  // std::cin >> n;
  // vector<int> a(n);
  // for (size_t i = 0; i < a.size(); i++) {
  //   std::cin >> a[i];
  // }
  // int m;
  // std::cin >> m;
  // vector<int> b(m);
  // for (int i = 0; i < m; ++i) {
  //   std::cin >> b[i];
  // }
  // for (int i = 0; i < m; ++i) {
  //   //replace with the call to binary_search when implemented
  //   // std::cout << linear_search(a, b[i]) << ' ';
  //   std::cout << binary_search(a, b[i]) << ' ';
  // }

  // test_solution();
  // for (int i = 0; i < 10; i++)
  // {
  //   test_rand();
  // }
  print_multiple_2(1048576,1048567);
}
