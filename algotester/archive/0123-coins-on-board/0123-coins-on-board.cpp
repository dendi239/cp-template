#include "bits/stdc++.h"

#ifdef __APPLE__
#define D for (bool _flag = true; _flag; _flag = false)
#else
#define D while (false)
#endif

using namespace std;

int solve_simple(int n, const vector<int> &ys) {
  int start = 0, result = 0;
  for (auto y : ys) {
    result += 2 * ((y - start) / 2);
    start = y + 1;
  }
  result += 2 * ((n - start) / 2);
  return result;
}

struct Solver {
  int n, m;
  int dr, dc;

  int get_index(int x, int y) const {
    return min(x / dr, y / dc);
  }

  pair<int, int> get_hash(int x, int y) {
    int i = get_index(x, y);
    x -= i * dr, y -= i * dc;
    return {x, y};
  }

  int get_count(int x, int y) const {
    int max_x = n - (n % dr) + x % dr;
    while (max_x > n) max_x -= dr;
    while (max_x < n) max_x += dr;
    int ix = (max_x - x) / dr;

    int max_y = m - (m % dc) + y % dc;
    while (max_y > m) max_y -= dc;
    while (max_y < m) max_y += dc;
    int iy = (max_y - y) / dc;

    return min(ix, iy) + get_index(x, y);
  }

  int base_answer(int x, int y) const {
    return 2 * (get_count(x, y) / 2);
  }
};

int64_t base_answer(int n, int m, int dr, int dc) {
  int64_t answer = 0;

  int64_t c = min(n / (2 * dr), m / (2 * dc));
  answer += 2 * c * (n * 1ll * dc + m * 1ll * dr - dr * 3ll * dc);
  answer -= 4 * c * (c - 1) * dr * dc;

  n -= 2 * dr * c, m -= 2 * dc * c;
  if (m > dc && n > dr) {
    answer += 2ll * (m - dc) * 1ll * (n - dr);
  }
  
  return answer;
}

int64_t naive_base_answer(int n, int m, int dr, int dc) {
  int64_t answer = 0;
  vector<vector<bool>> table(n, vector<bool>(m));
  for (int x = 0; x + dr < n; ++x) {
    for (int y = 0; y + dc < m; ++y) {
      if (!table[x][y]) {
        table[x][y] = true;
        table[x + dr][y + dc] = true;
        answer += 2;
      }
    }
  }
  return answer;
}

void test_index(int n, int m, int dr, int dc) {
  Solver s{n, m, dr, dc};
  vector<vector<int>> index(n, vector<int>(m, 0));
  for (int x = 0; x + dr < n; ++x) {
    for (int y = 0; y + dc < m; ++y) {
      index[x + dr][y + dc] = index[x][y] + 1;
    }
  }

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y)  {
      auto expected = index[x][y];
      auto actual = s.get_index(x, y);
      
      if (expected != actual) {
        cerr << "n: " << n << " m: " << m << " dr: " << dr << " dc: " << dc << endl;
        cerr << "wrong index: " << x << " " << y << " " << expected << " " << actual << endl;
      }

      auto [x0, y0] = s.get_hash(x, y);
      if (index[x0][y0] != 0) {
        cerr << "wrong hash for x:" << x << " y:" << y << endl;
        cerr << "  found: " << x0 << " " << y0 << endl;
      }

      if (index[x][y] == 0) {
        int len = 0, x1 = x, y1 = y;
        for (;;) {
          if (x1 >= n || y1 >= m) break;
          ++len;
          x1 += dr;
          y1 += dc;
        }
        if (len != s.get_count(x, y)) {
          cerr << "n: " << n << " m: " << m << " dr: " << dr << " dc: " << dc << endl;
          cerr << "wrong count for x:" << x << " y:" << y << endl;
          cerr << "  expected: " << len << endl;
          cerr << "    actual: " << s.get_count(x, y) << endl;
        }
      }
    }
  }
}

void test_base() {
  for (int n = 1; n < 5; ++n) {
    for (int m = 1; m < 5; ++m) {
      for (int dr = 1; dr <= n; ++dr) {
        for (int dc = 1; dc <= m; ++dc) {
          auto expected = naive_base_answer(n, m, dr, dc);
          auto actual = base_answer(n, m, dr, dc);

          if (expected != actual) {
            cerr << "n: " << n << " m: " << m << " dr: " << dr << " dc: " << dc
                 << " expected: " << expected << " actual: " << actual << endl;
          }

          test_index(n, m, dr, dc);
        }
      }
    }
  }

  cerr << "tests are done" << endl;
}

int main() {
  D test_base();

  int n, m, k, dr, dc;
  cin >> n >> m >> k >> dr >> dc;

  vector<pair<int, int>> coins(k);
  for (auto &[x, y] : coins) {
    cin >> x >> y;
    --x, --y;
  }

  Solver s{n, m, dr, dc};
  map<pair<int, int>, vector<pair<int, int>>> by_hash;
  for (auto [x, y] : coins) {
    by_hash[s.get_hash(x, y)].push_back({x, y});
  }

  int64_t answer = base_answer(n, m, dr, dc);
  for (auto &[lc, ps] : by_hash) {
    vector<int> is;
    auto [x, y] = lc;

    answer -= s.base_answer(x, y);
    for (auto [x, y] : ps) {
      is.push_back(s.get_index(x, y));
    }
    sort(is.begin(), is.end());
    answer += solve_simple(s.get_count(x, y), is);
  }

  cout << answer << '\n';
}