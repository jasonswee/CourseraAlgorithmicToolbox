#include <iostream>
#include <cassert>
#include <vector>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}
int gcd_fast(int a, int b) 
{
  int large = (a > b) ? a : b;
  int current_gcd = (a < b) ? a : b;
  int remainder=-1;
  while (true)
  {
    remainder = large % current_gcd;
    large = current_gcd;
    if (remainder == 0)
      break;
    current_gcd = remainder;
  }
  return current_gcd;
}
long long lcm_fast(int a, int b) 
{
  int gcd = gcd_fast(a,b);
  return  (((long long)a*(long long)b)/(long long)gcd);
}
void test_solution() 
{
  std::cout << lcm_fast(714552,374513) << std::endl;
  assert(lcm_fast(714552,374513) == 170777928);
  for (int n = 0; n < 20; ++n)
  {
    int a = std::rand();
    int b = std::rand();
      assert(lcm_naive(a,b) == lcm_fast(a,b));
  }
}
int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  //test_solution();
  return 0;
}
