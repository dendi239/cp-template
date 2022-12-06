#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;

int &inc(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
  return x;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> cnts(m);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    if (x <= m) {
      ++cnts[x - 1];
    }
  }

  int ans = 0, curr = 1;
  for (int c : cnts) {
    curr = curr * 1ll * c % mod;
    inc(ans, curr);
  }

  cout << ans << '\n';

  return 0;
}
