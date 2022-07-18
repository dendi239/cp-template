#include <bits/stdc++.h>

using namespace std;

int main() {
  int64_t n, a, b;
  cin >> n >> a >> b;
  --n;

  int64_t ans = n / a + n / b - n / lcm(a, b);
  cout << ans << '\n';
}
