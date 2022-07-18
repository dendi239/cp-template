#include <bits/stdc++.h>
#include <limits>
#include <numeric>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int64_t>>> g(n);
  for (int e = 0; e < m; ++e) {
    int u, v;
    int64_t c;
    cin >> u >> v >> c;

    --u, --v;
    g[u].emplace_back(v, c);
    g[v].emplace_back(u, c);
  }

  vector<int64_t> d(n, numeric_limits<int64_t>::max());
  d[0] = 0;

  set<pair<int64_t, int>> q;
  q.emplace(0, 0);
  while (!q.empty()) {
    auto [d_, u] = *q.begin();
    q.erase(q.begin());

    for (auto [v, c] : g[u]) {
      if (d[v] > d_ + c) {
        q.erase({d[v], v});
        d[v] = d_ + c;
        q.emplace(d[v], v);
      }
    }
  }

  cout << accumulate(d.begin(), d.end(), 0ll) << "\n";
}