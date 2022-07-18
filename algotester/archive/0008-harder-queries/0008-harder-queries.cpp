#include <bits/stdc++.h>

using namespace std;

struct STree {
  vector<int64_t> sums;

  void build(const vector<int> &as, int l, int r, int i) {
    if (l + 1 == r) {
      sums[i] = as[l];
      return;
    }

    int m = (l + r) / 2;
    build(as, l, m, i + 1);
    build(as, m, r, i + 2 * (m - l));

    sums[i] = sums[i + 1] + sums[i + 2 * (m - l)];
  }

  int n() const { return (sums.size() + 1) / 2; }

  STree(const vector<int> &as) : sums(2 * as.size() - 1) {
    build(as, 0, as.size(), 0);
  }

  int get(int l, int r, int i, int il, int ir) {
    if (l <= il && ir <= r) {
      return sums[i];
    }
    if (ir <= l || r <= il) {
      return 0;
    }

    const int im = (il + ir) / 2;
    return get(l, r, i + 1, il, im) + get(l, r, i + 2 * (im - il), im, ir);
  }

  int get(int l, int r) { return get(l, r, 0, 0, n()); }

  void add(int i, int x) {
    int in = 0, l = 0, r = n();
    while (true) {
      sums[in] += x;
      if (l + 1 == r) {
        break;
      }
      int m = (l + r) / 2;
      if (i < m) {
        r = m;
        in = in + 1;
      } else {
        in += 2 * (m - l);
        l = m;
      }
    }
  }

  int find(int64_t sum) const {
    int i = 0, l = 0, r = n();
    while (l + 1 < r) {
      const int m = (l + r) / 2;
      int il = i + 1, ir = i + 2 * (m - l);

      if (sum >= sums[il]) {
        sum -= sums[il];
        i = ir;
        l = m;
      } else {
        i = il;
        r = m;
      }
    }
    return l;
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  as.push_back(0);
  STree stree(as);

  for (int i = 0; i < q; ++i) {
    int t;
    cin >> t;
    if (t == 1) {
      int x;
      cin >> x;
      cout << stree.find(x) << '\n';
    } else {
      int i, d;
      cin >> i >> d;
      stree.add(--i, d);
    }
  }
}
