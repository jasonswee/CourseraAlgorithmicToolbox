#include <iostream>
#include <vector>
#include <cassert>


using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  int remain_value=0;
  int test_value=1;
  while(n!=0)
  {
      // std::cout<< "test value: "<< test_value << std::endl; 
    remain_value = n - test_value;
    if (remain_value > test_value)
    {
      
      summands.push_back(test_value);
      n=remain_value;

      // std::cout<< "1 Pushing value: "<< test_value 
      // << " Size: " << summands.size() 
      // << " n left: " << n 
      // <<std::endl;
      test_value+=1;
    }
    else if (remain_value == 0)
    {
      summands.push_back(test_value);
      // std::cout<< "End Pushing value: "<< test_value << " Size: " << summands.size() <<std::endl;
      n=0;
    }
    else if (remain_value > 0 && remain_value <= test_value)
    {
      summands.push_back(test_value + remain_value);
      // std::cout<< "End Pushing value: "<< test_value << " Size: " << summands.size() <<std::endl;
      n=0;
    }
  }

  // for(auto it:summands)
  // {
  //   std::cout<< "it: "<< it <<std::endl;
  // }
  return summands;
}
void test_solution()
{
  std::vector<int> answer={1,2,3};
  assert(optimal_summands(6)==answer);
  answer={1,2,5};
  assert(optimal_summands(8)==answer);
  answer={2};
  assert(optimal_summands(2)==answer);
  answer={1,3};
  assert(optimal_summands(4)==answer);
}
int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
  // test_solution();
}
