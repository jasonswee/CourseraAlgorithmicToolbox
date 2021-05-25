#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b) {
  // write your code here
  long long result = 0;
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[i]) * b[i];
  // std::cout << "Result: " << result << " a: " << a[i] << " b: "<< b[i] << std::endl;
  }
  return result;
}
void test_solution()
{
  std::cout << max_dot_product({23},{39}) << std::endl;
  assert(max_dot_product({23},{39}) == 897);
  std::cout << max_dot_product({1,3,-5},{-2,4,1}) << std::endl;
  assert(max_dot_product({1,3,-5},{-2,4,1}) == 23);
  std::cout << max_dot_product({1,3,5},{2,4,1}) << std::endl;
  assert(max_dot_product({1,3,5},{2,4,1}) == 27);
}
int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
  // test_solution();
}
