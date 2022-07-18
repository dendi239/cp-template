#include "bits/stdc++.h"

using namespace std;

template <class F> double bin_search(double l, double r, F f) {
  while (r - l > 1e-6) {
    double m = (l + r) / 2;
    if (f(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> ls(n);
  for (auto &l : ls) {
    cin >> l;
  }

  cout << setprecision(10) << fixed
       << bin_search(0.5 / m, *max_element(begin(ls), end(ls)),
                     [&](double x) {
                       int total = 0;
                       for (auto l : ls) {
                         total += static_cast<int>(l / x);
                       }
                       return total >= m;
                     })
       << '\n';

  return 0;
}
