#include "bits/stdc++.h"

using namespace std;

int main() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  int v = 0, k = 0, vs = 0, ks = 0;
  for (int i = 0; i < n; ++i) {
    ++(s[i] == 'V' ? v : k);
    if (abs(v - k) > 1 && max(v, k) >= 11) {
      ++(v > k ? vs : ks);
      v = k = 0;
    }
  }

  cout << ks << ":" << vs << "\n";
  if (v + k) {
    cout << k << ":" << v << "\n";
  }

  return 0;
}
