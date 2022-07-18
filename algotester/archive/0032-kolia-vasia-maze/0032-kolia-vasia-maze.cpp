#include "bits/stdc++.h"

using namespace std;

#define D for (bool _flag = false; _flag; _flag = false)

using G = vector<vector<int>>;

enum Color { NEW, USING, USED };

struct Dfs {
  const G &g;

  vector<Color> used;
  vector<int> cycle;

  Dfs(const G &g) : g(g), used(g.size(), NEW) {}

  int dfs(int u, int p) {
    used[u] = USING;
    int ans = -1;

    for (int v : g[u]) {
      if (v == p)
        continue;
      if (used[v] == USED)
        continue;

      if (used[v] == USING) {
        ans = v;
      } else {
        auto top = dfs(v, u);
        if (top != -1) {
          ans = top;
        }
      }
    }

    if (ans != -1) {
      D cerr << "top from " << u << " to " << ans << endl;
      cycle.push_back(u);
    }
    if (ans == u) {
      ans = -1;
    }

    used[u] = USED;
    return ans;
  }
};

int main() {
  int n;
  cin >> n;

  G g(n);
  for (int i = 0; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  Dfs dfs(g);
  dfs.dfs(0, -2);

  sort(dfs.cycle.begin(), dfs.cycle.end());
  cout << dfs.cycle.size() << "\n";
  for (auto u : dfs.cycle) {
    cout << u + 1 << " ";
  }
  cout << '\n';

  return 0;
}
