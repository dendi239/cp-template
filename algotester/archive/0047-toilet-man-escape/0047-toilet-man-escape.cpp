#include "bits/stdc++.h"

using namespace std;

using Point = pair<int, int>;

Point operator-(const Point &lhs, const Point &rhs) {
  return {lhs.first - rhs.first, lhs.second - rhs.second};
}

int64_t Cross(const Point &lhs, const Point &rhs) {
  return lhs.first * 1ll * rhs.second - lhs.second * 1ll * rhs.first;
}

int main() {
  int n;
  cin >> n;

  vector<Point> ps(n);
  for (auto &[x, y] : ps) {
    cin >> x >> y;
  }

  int left = 0, right = 0;
  for (int i = 1; i + 1 < n; ++i) {
    auto cross = Cross(ps[i] - ps[i-1], ps[i + 1] - ps[i]);
    if (cross > 0) {
      ++left;
    } else if (cross < 0) {
      ++right;
    }
  }

  cout << left << " " << right << "\n";

  return 0;
}
