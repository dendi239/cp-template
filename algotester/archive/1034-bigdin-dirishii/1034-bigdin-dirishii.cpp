#include "bits/stdc++.h"

using namespace std;

int main() {
  string s;
  cin >> s;

  set<char> odd;
  for (auto c : s) {
    if (odd.count(c)) {
      odd.erase(c);
    } else {
      odd.insert(c);
    }
  }

  if (odd.empty()) {
    cout << "2\n";
  } else {
    cout << "1\n" << string(odd.begin(), odd.end()) << '\n';
  }

  return 0;
}
