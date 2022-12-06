#include "bits/stdc++.h"

using namespace std;

using G = vector<vector<pair<int, int64_t>>>;

struct Dfs {
  const int n;
  const G &g;

  vector<int64_t> on_discovery;
  vector<int64_t> cycles;

  Dfs(const G &g) : n(g.size()), g(g), on_discovery(n, -1) {
  }

  void visit(int u) {
    for (auto [v, c] : g[u]) {
      if (on_discovery[v] == -1) {
        on_discovery[v] = on_discovery[u] ^ c;
        visit(v);
      } else {
        cycles.push_back(on_discovery[v] ^ on_discovery[u] ^ c);
      }
    }
  }

  void fill(int root) {
    on_discovery[root] = 0;
    visit(root);
  }
};

vector<int64_t> build_basis(const vector<int64_t> &xs) {
  vector<int64_t> basis;
  for (auto x : xs) {
    for (auto b : basis) {
      x = min(x, x ^ b);
    }
    if (x) {
      for (auto &b : basis) {
        b = min(b, b ^ x);
      }
      basis.push_back(x);
      sort(begin(basis), end(basis), greater<int64_t>());
    }
  }
  return basis;
}

int main() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  --s, --t;

  G g(n);
  for (int e = 0; e < m; ++e) {
    int u, v;
    int64_t c;
    cin >> u >> v >> c;
    --u, --v;
    g[u].emplace_back(v, c);
    g[v].emplace_back(u, c);
  }

  Dfs dfs(g);
  dfs.fill(s);

  auto basis = build_basis(dfs.cycles);
  int64_t best = dfs.on_discovery[t];

  for (auto b : basis) {
    best = max(best, best ^ b);
  }

  cout << best << '\n';

  return 0;
}
