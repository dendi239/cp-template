#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> as(n);
  for (auto &a : as) cin >> a;

  map<int, int> last;
  for (auto a : as) {
    auto it = last.lower_bound(a);
    if (it != last.begin()) {
      --it;
      last[a] = it->second + 1;
    } else {
      last[a] = 1;
    }

    it = last.find(a);
    while (next(it) != last.end() && next(it)->second == it->second) {
      last.erase(next(it));
      it = last.find(a);
    }
  }

  cout << last.rbegin()->second << "\n";
}
