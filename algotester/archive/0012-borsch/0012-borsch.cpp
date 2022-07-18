#include "bits/stdc++.h"

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> as(n), bs(n), cs(n);
  for (int i = 0; i < n; ++i) {
    cin >> as[i] >> bs[i] >> cs[i];
  }

  sort(as.begin(), as.end());
  sort(bs.begin(), bs.end());
  sort(cs.begin(), cs.end());

  int64_t ans = 0;
  for (auto &ps : {&as, &bs, &cs}) {
    auto &xs = *ps;
    auto mx = xs[xs.size() / 2];

    for (auto x : xs) {
      ans += abs(x - mx);
    }
  }

  cout << ans << '\n';
}