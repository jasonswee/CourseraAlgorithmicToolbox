#include <iostream>
#include <string>
#include <cassert>
#include <vector>
// Use iota
#include <numeric>
// std::max
#include <algorithm>

using std::string;

void print_this_vec2(std::vector<std::vector<int>> output)
{
  std::cout << "Start 2d vec: " << std::endl;
  for (auto row:output)
  {
    for(auto element:row)
    {
      std::cout << element << ", ";
    }
    std::cout << std::endl;
  }
}
void print_this_vec1(std::vector<int> output)
{
  std::cout << "Start Vec: " << std::endl;
  for (auto element:output)
  {
    std::cout << element << ", ";
  }
  std::cout << std::endl;
}

int edit_distance(const string &str1, const string &str2) {
  //write your code here
  std::vector<std::vector<int>> mapping;
  int vec_size = str1.size() + 1;
  int row_size = str2.size() + 1;
  // std::cout << "str1 value is: " << vec_size << std::endl;
  // std::cout << "str2 value is: " << row_size << std::endl;
  

  std::vector<int> current_row(row_size);
  std::iota(current_row.begin(), current_row.end(), 0);
  // print_this_vec1(current_row);
  mapping.push_back(current_row);
  for(int i=1;i<vec_size;i++)
  {
    current_row.clear();
    current_row.push_back(i);
    mapping.push_back(current_row);

    // print_this_vec2(mapping);
    // int min_val = std::max(vec_size, row_size);
    for (int j=1;j<row_size;j++)
    {
      // if(mapping[i][j - 1] + 1 < min_val)
      // {
      int  min_val = mapping[i][j - 1] + 1;
      // }
      if (mapping[i - 1][j] + 1 < min_val)
        min_val = mapping[i - 1][j] + 1;
      
      // std::cout << "str1: " << str1[i] << std::endl;
      // std::cout << "str2: " << str2[j] << std::endl;

      if (str1[i-1] != str2[j-1])
      {
        if (mapping[i - 1][j -1] + 1 < min_val)
          min_val = mapping[i - 1][j -1] + 1;
      }
      else
      {
        if (mapping[i - 1][j -1] < min_val)
        {
          min_val = mapping[i - 1][j -1];
        }
      }
      current_row.push_back(min_val);
      mapping[i].push_back(min_val);

      // print_this_vec1(current_row);

    }
  // print_this_vec2(mapping);
  }
  // std::cout << "Output value is: " << mapping[vec_size-1][row_size-1] << std::endl;
  return mapping[vec_size-1][row_size-1];
  return 0;
}

void test_solution()
{
  string str1;
  string str2;
  str1 = "ab";
  str2 = "ab";
  assert(edit_distance(str1, str2) == 0);
  str1 = "short";
  str2 = "ports";
  assert(edit_distance(str1, str2) == 3);
  str1 = "editing";
  str2 = "distance";
  
  assert(edit_distance(str1, str2) == 5);
}
int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
  // test_solution();
}
