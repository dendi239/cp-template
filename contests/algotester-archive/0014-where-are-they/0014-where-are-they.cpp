#include "bits/stdc++.h"
#include <ctime>

using namespace std;

using Point = complex<int>;

void read(std::istream &is, Point &p) {
  int x, y;
  is >> x >> y;
  p.real(x), p.imag(y);
}

vector<double> get_sides(const vector<Point> &ps) {
  vector<double> sides;
  for (int i = 0; i < ps.size(); ++i) {
    auto diff = (ps[i] - ps[(i + 1) % ps.size()]);
    int x = diff.real(), y = diff.imag();
    sides.push_back(hypot<double>(x, y));
  }
  return sides;
}

int64_t scalar(const Point &lhs, const Point &rhs) {
  return lhs.real() * 1ll * rhs.real() + lhs.imag() * 1ll * rhs.imag();
}

struct Checker {
  vector<int> order;
  const vector<Point> &as, &bs;

  Checker(const vector<Point> &as, const vector<Point> &bs) : as(as), bs(bs) {
    order.resize(as.size());
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), default_random_engine(time(0)));
  }

  bool operator()(int ica, int icb) {
    Point ca = as[ica], cb = bs[icb];
    Point ax = as[(ica + 1) % as.size()] - ca,
          bx = bs[(icb + 1) % bs.size()] - cb;
    Point ay = as[(ica + 2) % as.size()] - ca,
          by = bs[(icb + 2) % bs.size()] - cb;

    for (auto shift : order) {
      const int ia = (ica + shift) % as.size(), ib = (icb + shift) % bs.size();

      if (scalar(as[ia] - ca, ax) != scalar(bs[ib] - cb, bx)) {
        return false;
      }
      if (scalar(as[ia] - ca, ay) != scalar(bs[ib] - cb, by)) {
        return false;
      }
    }

    return true;
  }
};

map<double, double> get_unique(vector<double> sides) {
  sort(sides.begin(), sides.end());
  map<double, double> unique;

  for (int i = 0; i < sides.size(); ++i) {
    if (i == 0 || sides[i] > sides[i - 1] + 1e-6) {
      unique[sides[i]] = sides[i];
    } else {
      unique[sides[i]] = unique[sides[i - 1]];
    }
  }

  return unique;
}

pair<double, int> get_least(const map<double, double> &unique) {
  map<double, int> counted;
  for (auto [_, v] : unique) {
    ++counted[v];
  }

  return *min_element(
      begin(counted), end(counted),
      [](const pair<double, int> &lhs, const pair<double, int> &rhs) {
        return lhs.second < rhs.second;
      });
}

int main() {
  int n;
  cin >> n;

  vector<Point> from(n), to(n);
  for (auto ps : {&from, &to}) {
    for (auto &p : *ps) {
      read(cin, p);
    }
  }

  Checker check(from, to);

  vector<double> sides_from = get_sides(from), sides_to = get_sides(to);
  auto un_from = get_unique(sides_from), un_to = get_unique(sides_to);

  auto [to_find, cnt_find] = get_least(un_from);
  auto ifrom = 0;
  for (; ifrom < n; ++ifrom) {
    if (abs(sides_from[ifrom] - to_find) < 2e-6) {
      break;
    }
  }

  int answer = n;
  for (int ito = ifrom, is = 0; is < n; ++is, ito += n - 1, ito %= n) {
    if (abs(sides_to[ito] - to_find) < 2e-6 && check(ifrom, ito)) {
      answer = min(answer, (n + ifrom - ito) % n);
      break;
    }
    // if (clock() > 1.9 * CLOCKS_PER_SEC) {
    //   break;
    // }
  }

  cout << answer + 1 << '\n';

  return 0;
}
