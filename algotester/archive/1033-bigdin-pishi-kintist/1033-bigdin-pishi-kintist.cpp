#include "bits/stdc++.h"

using namespace std;

vector<tuple<int, int>> generate2(int n) {
  vector<vector<bool>> wl(n, vector<bool>(n));
  vector<tuple<int, int>> results;

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      for (int dx = 1; dx <= x; ++dx) {
        if (!wl[x - dx][y]) {
          wl[x][y] = true;
          break;
        }
      }
      for (int dy = 1; dy <= y; ++dy) {
        if (!wl[x][y - dy]) {
          wl[x][y] = true;
          break;
        }
      }
      for (int d = 1; d <= min({x, y}); ++d) {
        if (!wl[x - d][y - d]) {
          wl[x][y] = true;
          break;
        }
      }

      if (!wl[x][y]) {
        results.emplace_back(x, y);
      }
    }
  }
  return results;
}

vector<tuple<int, int, int>> generate(int n) {
  vector<vector<vector<bool>>> wl(n, vector<vector<bool>>(n, vector<bool>(n)));
  vector<tuple<int, int, int>> results;

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      for (int z = !(x + y); z < n; ++z) {
        for (int dx = 1; dx <= x; ++dx) {
          if (!wl[x - dx][y][z]) {
            wl[x][y][z] = true;
            break;
          }
        }
        for (int dy = 1; dy <= y; ++dy) {
          if (!wl[x][y - dy][z]) {
            wl[x][y][z] = true;
            break;
          }
        }
        for (int dz = 1; dz <= z; ++dz) {
          if (!wl[x][y][z - dz]) {
            wl[x][y][z] = true;
            break;
          }
        }

        for (int d = 1; d <= min({x, y, z}); ++d) {
          if (!wl[x - d][y - d][z - d]) {
            wl[x][y][z] = true;
            break;
          }
        }

        if (!wl[x][y][z]) {
          results.emplace_back(x, y, z);
        }
      }
    }
  }
  return results;
}

int main() {
  int64_t x, y, z;
  cin >> x >> y >> z;

  int64_t score = x ^ y ^ z;
  if (score) {
    int64_t dx = 0, dy = 0, dz = 0;
    cout << "Sereja\n";
    if ((z ^ score) < z) {
      dz = z - (z ^ score);
    } else if ((y ^ score) < y) {
      dy = y - (y ^ score);
    } else if ((x ^ score) < x) {
      dx = x - (x ^ score);
    } else {
      dx = dy = dz = score;
    }

    cout << dx << ' ' << dy << ' ' << dz << '\n';
  } else {
    cout << "LiBrin\n";
  }
  return 0;

  const int n = 100;

  auto ps = generate2(n);
  sort(ps.begin(), ps.end(), [](tuple<int, int> lhs, tuple<int, int> rhs) {
    auto sum = [](tuple<int, int> x) {
      return get<0>(x) + get<1>(x);
    };
    return sum(lhs) < sum(rhs);
  });

  for (auto [x, y] : ps) {
    if (x > y) {
      cout << x << "\t" << y << "\t" << x - y  << "\t" << x + y << endl;
    }
  }

  auto ps3 = generate(n);
  sort(ps3.begin(), ps3.end(), [](tuple<int, int, int> lhs, tuple<int, int, int> rhs) {
    auto sum = [](tuple<int, int, int> x) {
      return get<0>(x) + get<1>(x) + get<2>(x);
    };
    return sum(lhs) < sum(rhs);
  });

  for (auto [x, y, z] : ps3) {
    if (x <= y && y <= z) {
      cout << x << "\t" << y << "\t" << z << "\t" << (x ^ y ^ z) << endl;
    }
  }

  return 0;
}
