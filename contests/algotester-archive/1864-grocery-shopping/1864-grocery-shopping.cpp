#include "bits/stdc++.h"

using namespace std;

vector<int> best_two(const vector<int> &xs) {
  int neg = numeric_limits<int>::min(), pos = numeric_limits<int>::max();
  for (int x : xs) {
    if (x < 0) {
      neg = max(neg, x);
    }
    if (x > 0) {
      pos = min(pos, x);
    }
  }
  vector<int> ans;
  if (neg != numeric_limits<int>::min()) {
    ans.push_back(neg);
  }
  if (pos != numeric_limits<int>::max()) {
    ans.push_back(pos);
  }
  return ans;
}

int64_t solve(array<int64_t, 4> xs) {
  int minx = xs[0], maxx = xs[0];
  for (int x : xs) {
    minx = min(minx, x);
    maxx = max(maxx, x);
  }
  return 2ll * (maxx - minx);
}

int main() {
  int n;
  cin >> n;

  vector<int> xs(n), ys(n), cs(n), ds(n);
  for (auto &x : xs) 
    cin >> x;  
  for (auto &y : ys)
    cin >> y;
  for (auto &c : cs)
    cin >> c;
  for (auto &d : ds) 
    cin >> d;

  int64_t best = 2ll * abs(ds[0]);
  for (int d : ds) {
    best = min(best, int64_t(2) * abs(d));
  }

  xs = best_two(xs), ys = best_two(ys), cs = best_two(cs);
  for (int x : xs) {
    for (int y : ys) {
      for (int c : cs) {
        auto plan = array<int64_t, 4>{
          0, x, y, c,
        };
        best = min(best, solve(plan));
      }
    }
  }

  cout << best << '\n';

  return 0;
}
