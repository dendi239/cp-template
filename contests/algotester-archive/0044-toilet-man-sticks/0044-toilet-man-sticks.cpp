#include "bits/stdc++.h"

#ifdef __APPLE__
#define D for (bool _flag = true; _flag; _flag = false)
#else
#define D while (false)
#endif

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  map<int, int, greater<int>> enumerated;
  for (auto a : as) {
    ++enumerated[a];
  }

  int cursor = enumerated.begin()->first;
  int64_t answer = 0;
  for (auto a : as) {
    answer += abs(a - cursor);
  }

  int64_t best = answer, extra = 0;
  while (cursor) {
    int next = enumerated.begin()->first / 2;
    if (enumerated.size() >= 2) {
      next = max(next, std::next(enumerated.begin())->first);
    }

    auto [cost, count] = *enumerated.begin();
    enumerated.erase(enumerated.begin());

    answer += count + count * 1ll * (next - (cost / 2));
    D extra += count;

    answer -= (cost - next) * 1ll * (n - count);
    enumerated[cost / 2] += count;

    best = min(best, answer);

    D {
      int64_t naive = extra;
      for (auto [cost, count] : enumerated) {
        cerr << cost << "x" << count << " ";
        naive += count * 1ll * (next - cost);
      }
      cerr << endl;

      cerr << "next: " << next << " cost: " << cost << " count: " << count
           << " answer: " << answer << " naive: " << naive
           << " extra: " << extra << endl;
    }
    cursor = next;
  }

  cout << best << "\n";

  return 0;
}
