#include "bits/stdc++.h"
#include <iomanip>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  vector<pair<int, int>> gates(n);
  for (auto &[l, r] : gates) {
    cin >> l >> r;
  }

  vector<int> points;
  for (auto &[l, r] : gates) {
    points.push_back(l);
    points.push_back(r);
  }

  sort(points.begin(), points.end());
  points.erase(unique(points.begin(), points.end()), points.end());

  double best = hypot<double>(x1 - points.front(), y1) +
                hypot<double>(x2 - points.back(), y2) +
                (points.back() - points.front());

  vector<vector<int>> who(points.size());
  for (int i = 0; i < n; ++i) {
    auto [l, r] = gates[i];
    for (int ix = 0; ix < points.size(); ++ix) {
      if (points[ix] >= l && points[ix] <= r) {
        who[ix].push_back(i);
      }
    }
  }

  for (int start = 0; start < points.size(); ++start) {
    set<int> seen;
    for (int i = start; i < points.size(); ++i) {
      for (auto is : who[i]) {
        seen.insert(is);
      }

      if (seen.size() >= k) {
        double possible = hypot<double>(x1 - points[start], y1) +
                          hypot<double>(x2 - points[i], y2) +
                          (points[i] - points[start]);

        best = min(best, possible);

        possible = hypot<double>(x1 - points[i], y1) +
                   hypot<double>(x2 - points[start], y2) +
                   (points[i] - points[start]);

        best = min(best, possible);
      }
    }
  }

  cout << setprecision(10) << best << "\n";

  return 0;
}
