#include <iostream>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {
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

int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
