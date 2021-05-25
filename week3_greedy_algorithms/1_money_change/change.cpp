#include <iostream>
#include <cassert>

int get_change(int m) {
  //write your code here
  int n;
  n=m/10;
  n=n+(m%10)/5;
  n=n+(m%10)%5;
  return n;
}

void test_solution()
{
  assert(get_change(2)==2);
  assert(get_change(28)==6);
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
  // test_solution();
}
