#include "bits/stdc++.h"

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  string digits;
  cin >> digits;

  int rem = 0;
  for (char d_char : digits) {
    int d = d_char - '0';
  
    rem += d;
    rem %= n - 1;
  }

  if (rem == 0) {
    rem = n - 1;
  }

  cout << rem << '\n';

  return 0;
}
