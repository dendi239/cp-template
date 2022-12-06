#include <bits/stdc++.h>

using namespace std;

bool IS_DEBUG = false;
#define D for (bool _flag = IS_DEBUG; _flag; _flag = false)

struct STree {
  struct Node {
    int color = -1;
  };

  const int n;
  vector<Node> nodes;

  STree(int n) : n(n), nodes(2 * n - 1) {}

  void push(int i, int l, int r) {
    if (r - l == 1)
      return;

    const int m = (l + r) / 2;
    const int il = i + 1, ir = i + 2 * (m - l);

    if (nodes[i].color != -1) {
      nodes[il].color = nodes[i].color;
      nodes[ir].color = nodes[i].color;
      nodes[i].color = -1;
    }
  }

  void set(int l, int r, int c, int i, int il, int ir) {
    if (r <= il || ir <= l)
      return;

    if (l <= il && ir <= r) {
      nodes[i].color = c;
      return;
    }

    push(i, il, ir);

    const int m = (il + ir) / 2;
    set(l, r, c, i + 1, il, m);
    set(l, r, c, i + 2 * (m - il), m, ir);
  }

  void set(int l, int r, int c) { set(l, r, c, 0, 0, n); }

  void fill(vector<int> *cs, int i, int l, int r) {
    if (r - l == 1) {
      (*cs)[l] = nodes[i].color;
      return;
    } else {
      push(i, l, r);
      const int m = (l + r) / 2;
      fill(cs, i + 1, l, m);
      fill(cs, i + 2 * (m - l), m, r);
    }
  }

  void fill(vector<int> *colors) { fill(colors, 0, 0, n); }
};

int main() {
  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int>> segs(m);
  for (auto &[l, r, c] : segs) {
    cin >> l >> r >> c;
    --l;
  }

  STree st(n);
  for (auto &[l, r, c] : segs) {
    st.set(l, r, c);
  }

  vector<int> colors(n);
  st.fill(&colors);

  for (auto c : colors)
    cout << max(0, c) << " ";
  
  cout << '\n';
}