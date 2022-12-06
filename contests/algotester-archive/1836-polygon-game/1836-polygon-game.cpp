#include "bits/stdc++.h"

using namespace std;

#define D for (bool _flag = false; _flag; _flag = false)

using Point = pair<int, int>;

ostream &operator<<(ostream &os, const Point &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

Point operator-(const Point &lhs, const Point &rhs) {
  return {lhs.first - rhs.first, lhs.second - rhs.second};
}

int64_t Cross(const Point &lhs, const Point &rhs) {
  D cerr << "cross(" << lhs << ", " << rhs << ")" << endl;
  return int64_t(lhs.first) * rhs.second - int64_t(lhs.second) * rhs.first;
}

int64_t Area(Point a, Point b, Point c) {
  D cerr << "area(" << a << ", " << b << ", " << c << ")" << endl;
  return abs(Cross(b - a, c - a));
}

int main() {
  int n;
  cin >> n;

  vector<Point> points(n);
  for (auto &[x, y] : points) {
    cin >> x >> y;
  }

  int64_t best = 0;
  for (int i = 0; i < n; ++i) {
    const int pi = (i + n - 1) % n;
    const int ni = (i + 1) % n;

    const int64_t area = Area(points[i], points[pi], points[ni]);
    D cerr << "area: " << area << endl;

    best = max(best, area);
  }

  cout << best << endl;

  return 0;
}
