#include "bits/stdc++.h"
#ifdef __APPLE__
#define D for (bool _flag = true; _flag; _flag = false)
#else
#define D while (false)
#endif

using namespace std;

using G = vector<vector<int>>;

struct DoNothing {
  void operator()(int u) const {}
};

struct Dfs {
  const G &g;
  vector<int> tin, tout;
  int now = 0;

  Dfs(const G &g) : g(g), tin(g.size(), -1), tout(g.size(), -1) {}

  bool visited(int u) const { return tin[u] != -1; }

  template <class F = DoNothing> void visit(int u, F callback = {}) {
    tin[u] = now++;
    for (auto v : g[u]) {
      if (tin[v] == -1) {
        visit(v, callback);
      }
    }
    callback(u);
    tout[u] = now++;
  }

  vector<int> exit_order() const {
    const int n = g.size();
    vector<int> order, who(2 * n, -1);
    for (int u = 0; u < n; ++u) {
      who[tout[u]] = u;
    }
    for (int i = 0; i < 2 * n; ++i) {
      if (who[i] != -1) {
        order.push_back(who[i]);
      }
    }
    reverse(order.begin(), order.end());
    return order;
  }
};

G Reverse(const G &g) {
  G rg(g.size());
  for (int u = 0; u < g.size(); ++u) {
    for (auto v : g[u]) {
      rg[v].push_back(u);
    }
  }
  return rg;
}

pair<G, vector<int>> BuildCondensation(const G &g) {
  const int n = g.size();
  Dfs dfs(g);

  for (int u = 0; u < n; ++u) {
    if (!dfs.visited(u)) {
      dfs.visit(u);
    }
  }

  auto exit_order = dfs.exit_order();
  vector<int> colors(n, -1);
  int last_color = 0;

  D {
    cerr << "exit_order:";
    for (auto u : exit_order)
      cerr << " " << u;
    cerr << "\n";
  }

  G rg = Reverse(g);
  Dfs rfs(rg);
  for (auto u : exit_order) {
    if (!rfs.visited(u)) {
      rfs.visit(u, [&](int v) { colors[v] = last_color; });
      ++last_color;
    }
  }

  G cond(last_color);

  for (int u = 0; u < n; ++u) {
    for (int v : g[u]) {
      if (colors[u] != colors[v]) {
        cond[colors[u]].push_back(colors[v]);
      }
    }
  }

  for (auto &slice : cond) {
    sort(slice.begin(), slice.end());
    slice.erase(unique(slice.begin(), slice.end()), slice.end());
  }

  return {cond, colors};
}

int main() {
  int n, m;
  cin >> n >> m;

  G g(n);
  for (int e = 0; e < m; ++e) {
    int u, v;
    cin >> u >> v;

    g[--u].push_back(--v);
  }

  auto [cond, cond_colors] = BuildCondensation(g);
  D {
    for (auto c : cond_colors) {
      cerr << c << " ";
    }
    cerr << endl;
    for (int u = 0; u < cond.size(); ++u) {
      cerr << u << ": ";
      for (auto v : cond[u]) {
        cerr << v << " ";
      }
      cerr << endl;
    }
  }

  auto rcond = Reverse(cond);
  auto empty = [](const auto &slice) { return slice.empty(); };

  if (count_if(rcond.begin(), rcond.end(), empty) > 1) {
    cout << "-1\n";
    return 0;
  }

  auto icond = find(rcond.begin(), rcond.end(), vector<int>{}) - rcond.begin();
  auto dfs = Dfs(cond);

  dfs.visit(icond);
  for (int u = 0; u < cond.size(); ++u) {
    if (!dfs.visited(u)) {
      cout << "-1\n";
      return 0;
    }
  }

  for (int u = 0; u < n; ++u) {
    if (cond_colors[u] == icond) {
      cout << u + 1 << "\n";
      return 0;
    }
  }

  cout << "-1\n";

  return 0;
}
