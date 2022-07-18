#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> ls(n); for (auto &l : ls) cin >> l;
  vector<int> ws(n); for (auto &w : ws) cin >> w;

  vector<int> is(n); iota(is.begin(), is.end(), 0);
  sort(is.begin(), is.end(), [&](int i, int j) {
    return ls[i] * 1ll * ws[j] < ls[j] * 1ll * ws[i];
  });

  for (auto i : is) {
    cout << i+1 << " ";
  }
  cout << "\n";
}

/*

total:

l[p0] * w[p1] + (l[p0] + l[p1]) * w[p2] + ... + (l[p0] + l[p1] + ... + l[pn-1]) * w[pn]
l[p0] * (w[p1] + ... + w[pn]) + l[p1] * (w[p2] + ... + w[pn]) + ... + l[pn-1] * w[pn]
sum_l * sum_w - l[p0] * pref_w[p0] - l[p1] * pref_w[p1] - ... - l[pn] * pref_w[pn]

l[pi-1] * (w[pi] + ... + w[pn]) + l[pi] * (w[pi+1] + ... + w[pn]) = 
l[pi-1] * w[pi] + (l[pi-1] + l[pi]) * (w[pi+1] + ... + w[pn])

l[pi-1] * w[pi] < l[pi] * w[pi-1]
l[pi-1] / w[pi-1] < l[pi] / w[pi]

*/

