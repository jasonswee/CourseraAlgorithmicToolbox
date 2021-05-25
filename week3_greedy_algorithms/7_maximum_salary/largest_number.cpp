#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;

bool isGreater(string a, string b)
{
  for (int i = 0; i < a.size();i++)
  {
    
    if (a[i] > b[i])
    {
      
    // std::cout << "Greater index: " << i << " a: " << a[i] <<  " b: " << b[i] << std::endl;
      return true;
    }
    else if (a[i] < b[i])
    {
    // std::cout << "Lesser index: " << i << " a: " << a[i] <<  " b: " << b[i] << std::endl;
      return false;
    }
    else if (a[i] == b[i])
    {
      
    // std::cout << "Same index: " << i << " a: " << a[i] <<  " b: " << b[i] << std::endl;
      string aa=a;
      string bb=b;
      if (aa.size() == 1 && bb.size() == 1) return false;
      if (aa.size()==1) aa[0] = a[i];
      else aa.erase(aa.begin());
      if (bb.size()==1) bb[0] = b[i];
      else bb.erase(bb.begin());

      // return false;
      return isGreater(aa,bb);
    }
    return false;
  }
  return false;
}

string largest_number(vector<string> a) {
  //write your code here
  std::vector<string> a_copy = a;
  a.clear();
  while (a_copy.size()!=0)
  {
    string current = a_copy[0];
    int index=0;
    for (int i=1;i<a_copy.size();i++)
    {
      if (isGreater(a_copy[i],current)) 
      {
        current = a_copy[i];
        index = i;
      }
    }
    a.push_back(current);
    // std::cout << " current: "  << current;
    // std::cout << " a copy size: "  << a_copy.size();
    if (a_copy.size()==1) break;
    a_copy.erase(a_copy.begin() + index);
    // std::cout << " a copy size: "  << a_copy.size();
  }

    // std::cout << " a size: "  << a.size();
  // for (auto it:a)
  // {
  //   std::cout << " it: "  << it;
  // }


  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;

  
  std::cout << "Result: "  << result << std::endl;
  return result;
}


void test_solution()
{
  assert(largest_number({"21","2"}) == "221");
  assert(largest_number({"9","4","6","1","9"}) == "99641");
  assert(largest_number({"23","39","92"}) == "923923");
  assert(largest_number({"231","392","922"}) == "922392231");
  assert(largest_number({"11","10","1"}) == "11110");
  assert(largest_number({"11","101","1"}) == "111101");
}

int main() {
  // int n;
  // std::cin >> n;
  // vector<string> a(n);
  // for (size_t i = 0; i < a.size(); i++) {
  //   std::cin >> a[i];
  // }
  // std::cout << largest_number(a);
  test_solution();
}
