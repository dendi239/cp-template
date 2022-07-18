#include "bits/stdc++.h"

using namespace std;

using Point = pair<int64_t, int64_t>;

int64_t gcd(int64_t x, int64_t y) {
  while (y) {
    x %= y;
    swap(x, y);
  }
  return x;
}

int64_t Count(const Point &lhs, const Point &rhs) {
  auto dx = abs(lhs.first - rhs.first);
  auto dy = abs(lhs.second - rhs.second);

  return gcd(dx, dy);
}

bool Lower(const Point &lhs, const Point &mhs, const Point &rhs) {
  return (lhs.first - mhs.first) * (rhs.second - mhs.second) -
         (lhs.second - mhs.second) * (rhs.first - mhs.first) > 0;
}

bool Upper(const Point &lhs, const Point &mhs, const Point &rhs) {
  return (lhs.first - mhs.first) * (rhs.second - mhs.second) -
         (lhs.second - mhs.second) * (rhs.first - mhs.first) < 0;
}

int main() {
  int n;
  cin >> n;

  vector<Point> points(n);
  for (auto &[x, y] : points) {
    cin >> x >> y;
  }

  sort(points.begin(), points.end());
  vector<Point> up, down;

  for (auto p : points) {
    while (up.size() >= 2 && !Upper(*++up.rbegin(), up.back(), p)) {
      up.pop_back();
    }

    while (down.size() >= 2 && !Lower(*++down.rbegin(), down.back(), p)) {
      down.pop_back();
    }

    up.push_back(p);
    down.push_back(p);
  }

  int64_t total = 0;
  for (auto &pps : {&up, &down}) {
    for (int i = 1; i < pps->size(); ++i) {
      total += Count((*pps)[i - 1], (*pps)[i]);
    }
  }

  cout << total << '\n';

  return 0;
}
