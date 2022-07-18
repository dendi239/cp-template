#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> as(n);
  for (auto &a : as) cin >> a;

  vector<int> is(n); iota(is.begin(), is.end(), 0);
  sort(is.begin(), is.end(), [&](int i, int j) {
    return as[i] < as[j];
  });

  for (auto i : is) {
    cout << i+1 << " ";
  }
  cout << '\n';
}
