#include "bits/stdc++.h"

using namespace std;

int main() {
  string s;
  cin >> s;

  int n;
  cin >> n;

  vector<pair<int, int>> segs(n);
  for (auto &[l, r] : segs) {
    cin >> l >> r;
    --l, --r;
  }

  vector<vector<int>> answers(s.size(), vector<int>(s.size(), s.size()));
  for (int i = 0; i < s.size(); ++i) {
    answers[i][i] = 0;
  }
  for (int i = 0; i + 1 < s.size(); ++i) {
    answers[i][i + 1] = s[i] != s[i + 1];
  }

  for (int diff = 2; diff < s.size(); ++diff) {
    for (int l = 0; l + diff < s.size(); ++l) {
      const int r = l + diff;

      answers[l][r] = min({
          1 + answers[l + 1][r],
          1 + answers[l][r - 1],
      });

      if (s[l] == s[r]) {
        answers[l][r] = min(answers[l][r], answers[l + 1][r - 1]);
      }
    }
  }

  for (auto [l, r] : segs) {
    cout << answers[l][r] << " ";
  }
  cout << "\n";

  return 0;
}
