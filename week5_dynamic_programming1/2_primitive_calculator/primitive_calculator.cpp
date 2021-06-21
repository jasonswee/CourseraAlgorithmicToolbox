#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;

void print_this(vector<int> output)
{
  std::cout << "Start print num of operation used: "<< output.size() - 1 << std::endl;
  for (auto i:output)
  {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> optimal_sequence_fast(int n) {
  std::vector<int> min_list;
  std::vector<int> sequence;
  std::vector<std::vector<int>> sequence_cache;
  min_list.push_back(0);
  sequence.push_back(1);
  sequence_cache.push_back({1});

  for (int i=1;i<n;i++)
  {
    int min_operations = n;
    if ((i+1) % 3 == 0)
    { 
      if (min_list[(i+1)/3 - 1] < min_operations)
      {
        min_operations = min_list[(i+1)/3 - 1] + 1;
        sequence = sequence_cache[(i+1)/3 - 1];
        sequence.push_back(sequence.back() * 3);
      }
    }
    if ((i+1) % 2 == 0)
    { 
      if (min_list[(i+1)/2 -1 ]  < min_operations)
      {
        min_operations = min_list[(i+1)/2 - 1] + 1;
        sequence = sequence_cache[(i+1)/2 - 1];
        sequence.push_back(sequence.back() * 2);
      }
    }
    if (i-1 >=0)
    {
      if (min_list[i-1] + 1 < min_operations)
      {
        min_operations = min_list[i-1] + 1;
        sequence = sequence_cache[i-1];
        sequence.push_back(sequence.back() + 1);
      }
    }
    min_list.push_back(min_operations);
    sequence_cache.push_back(sequence);
  }
  return sequence;
}
void test_solution()
{
  // May fail due to multiple answers
  // for (int i=0;i<10;i++)
  // {
  //   assert(optimal_sequence(i)==optimal_sequence_fast(i));
  // }

  std::vector<int> result;
  result = {1};
  assert(optimal_sequence_fast(1)==result);
  result = {1,2};
  assert(optimal_sequence_fast(2)==result);
  result = {1,3};
  assert(optimal_sequence_fast(3)==result);
  result = {1,2,4};
  assert(optimal_sequence_fast(4)==result);
  result = {1,2,4,5};
  assert(optimal_sequence_fast(5)==result);

  print_this(optimal_sequence_fast(96234));
  print_this(optimal_sequence_fast(3));
  print_this(optimal_sequence_fast(5));
  print_this(optimal_sequence_fast(9));
  print_this(optimal_sequence_fast(10));
  print_this(optimal_sequence_fast(11));
}

int main() {
  int n;
  std::cin >> n;
  // vector<int> sequence = optimal_sequence(n);
  vector<int> sequence = optimal_sequence_fast(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
  // test_solution();
}
