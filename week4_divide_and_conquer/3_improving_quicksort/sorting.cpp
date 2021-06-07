#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>

using std::vector;
using std::swap;

int random_func(int low, int high)
{
  return rand() % high + low;
}
void print_result(vector<int> a)
{
  for (size_t i = 0; i < a.size(); ++i) 
  {
    std::cout << a[i] << ' ';
  }
    std::cout << std::endl;
}
int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
    // print_result(a);
  }
  swap(a[l], a[j]);
  return j;
}
vector<int> partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  int k = r;
  std::vector<int> b = a; 
  for (int i = l + 1; i <= r; i++) 
  {
    // print_result(a);
    if (b[i] < x) 
    {
      a[j]=b[i];
      j++;
    }
    else if (b[i] > x) 
    {
      a[k]=b[i];
      k--;
    }
  }
  for (int i = j; i <=k ; i++)
  {
    a[i] = x;
  }
  std::vector<int> m = {j,k};
  // print_result(a);
  // std::cout << "Return m1: " << m[0] << std::endl;
  // std::cout << "Return m2: " << m[1] << std::endl;
  return m;
}

void randomized_quick_sort_three(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  vector<int> m = partition3(a, l, r);

  randomized_quick_sort_three(a, l, m[0] - 1);
  randomized_quick_sort_three(a, m[1] + 1, r);
}
void randomized_quick_sort(vector<int> &a, int l, int r) 
{
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
}
void test_case_rand()
{
  vector<int> a;
  int n = random_func(1,std::pow(10,5));
  // int n = 10;
  for (int i = 0; i < n ; i++)
  {
    a.push_back(random_func(1,std::pow(10,9)));
  }
  vector<int> b=a;

  // randomized_quick_sort(a, 0, a.size()-1);
  
  std::sort(a.begin(), a.end());
  randomized_quick_sort_three(b, 0, b.size()-1);
  // std::cout<< "Sort:" <<std::endl;
  // print_result(a);
  // std::cout<< "partition 3: " << std::endl;
  // print_result(b);
  // std::cout<<std::endl;
  assert(a==b);
}
void test_solution()
{
  vector<int> a={2,3,9,2,2};
  vector<int> b={2,2,2,3,9};
  randomized_quick_sort(a, 0, a.size()-1);
  print_result(a);
  assert(a==b);

  a={2,3,9,2,2};
  b={2,2,2,3,9};
  randomized_quick_sort_three(a, 0, a.size()-1);
  print_result(a);
  assert(a==b);

  // a={2,3,9,2,2};
  // partition2(a, 0, a.size()-1);
  // std::cout << std::endl;
  // a={2,3,9,2,2};
  // partition3(a, 0, a.size()-1);
  // a={3,2,9,2,2};
  // partition3(a, 0, a.size()-1);
  // a={2,3,9,2,2};
  // partition3(a, 3, 4);
  // a={2,3,9,2,2};
  // partition3(a, 0, a.size()-1);

  // a.clear();
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  // randomized_quick_sort(a, 0, a.size() - 1);
  randomized_quick_sort_three(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
  // test_solution();

  // for (int i =0;i<100;i++)
  // {
  //   test_case_rand();
  // }
}
