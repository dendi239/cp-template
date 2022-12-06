#include "bits/stdc++.h"

using namespace std;

int main() {
  int n;
  cin >> n;

  int banknotes = 0;
  for (int factor : {500, 200, 100, 50, 20, 10, 5, 2, 1}) {
    int count = n / factor;
    n -= count * factor;
    banknotes += count;
  }

  cout << banknotes << '\n';

  return 0;
}
