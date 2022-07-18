#include "bits/stdc++.h"

using namespace std;

int main() {
  int n;
  cin >> n;

  int64_t sum = 0, g = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    sum += x;
    g = gcd(g, x);
  }

  cout << sum / g << '\n';

  return 0;
}
