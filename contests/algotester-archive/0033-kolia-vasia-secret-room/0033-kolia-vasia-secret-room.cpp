#include "bits/stdc++.h"

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> ss(n);
  for (auto &s : ss)
    cin >> s;

  vector<int> bs(m);
  for (auto &b : bs)
    cin >> b;

  priority_queue<int> bq(bs.begin(), bs.end());
  sort(ss.begin(), ss.end(), greater<int>());

  int64_t answer = 0;
  for (auto s : ss) {
    auto b = bq.top();
    bq.pop();

    answer += s * 1ll * b;
    if (b == 0) {
      break;
    }

    bq.push(b - 1);
  }

  cout << answer << "\n";

  return 0;
}
