#include "bits/stdc++.h"

using namespace std;

int main() {
  int l = 0, r = 1e9 + 1;

  while (true) {
    const int m = (l + r) / 2;
    cout << m << endl;

    string ans;
    cin >> ans;

    if (ans == "<") {
      l = m;
    } else if (ans == ">") {
      r = m;
    } else {
      break;
    }
  }

  return 0;
}
