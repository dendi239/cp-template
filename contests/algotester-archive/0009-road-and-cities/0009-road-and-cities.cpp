#include <bits/stdc++.h>

using namespace std;

struct DSU {
  vector<int> parent_or_size;

  DSU(int n) : parent_or_size(n, -1) {
  }

  int parent(int p) {
    if (parent_or_size[p] < 0) {
      return p;
    } else {
      return parent_or_size[p] = parent(parent_or_size[p]);
    }
  }

  bool merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    
    if (a == b) return false;
    if (-parent_or_size[a] < -parent_or_size[b]) {
      swap(a, b);
    }

    parent_or_size[a] += parent_or_size[b];
    parent_or_size[b] = a;

    return true;
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  DSU dsu(n);
  int total = n;
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v;

    if (dsu.merge(u - 1, v - 1)) {
      --total;
    }

    cout << total << '\n';
  }
}