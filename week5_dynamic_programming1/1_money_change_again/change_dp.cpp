#include <iostream>
#include <cassert>
#include <vector>

// Power
#include <cmath>

void print_this(std::vector<int> input)
{
  for (auto i:input)
  {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}

int get_change(int m) {
  //write your code here
  std::vector<int> change;
  std::vector<int> coins = {1,3,4};
  int max_m;
  change.push_back(0); // 0
  // for (int i=1;i<=std::pow(10,3);i++)
  for (int i=1;i<=m;i++)
  {
    max_m=std::pow(10,3);
    for (int coin_ind=0; coin_ind<coins.size();coin_ind++)
    {
      int last_change = i-coins[coin_ind];
      // If last change is above 0 means valud
      if (last_change >= 0)
      {
        int new_change = change[last_change] + 1;
        if (new_change < max_m) max_m = new_change;
      }
    }

    change.push_back(max_m);
  }
  // print_this(change);
  return change[m];
}
void test_solution()
{
  assert(get_change(0)==0);
  assert(get_change(1)==1);
  assert(get_change(2)==2);
  assert(get_change(3)==1);
  assert(get_change(4)==1);
  assert(get_change(5)==2);
  assert(get_change(6)==2);
  assert(get_change(7)==2);
  assert(get_change(8)==2);
  assert(get_change(34)==9);
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';

  // test_solution();
}
