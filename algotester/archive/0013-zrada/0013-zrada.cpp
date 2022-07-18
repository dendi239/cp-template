#include "bits/stdc++.h"

using namespace std;

template <typename T>
T gcd(T a, T b) {
  return a ? gcd(b % a, a) : b;
}

int divs_between(int x, int a, int b, int c, int d) {
  int ans = 0;
  auto check = [&](int d1, int d2) {
    if (a <= d1 && d1 <= b && c <= d2 && d2 <= d) {
      ans++;
    }
  };

  for (int d = 1; d <= x / d; ++d) {
    if (x % d == 0) {
      check(d, x / d);
    }
    if (x % d == 0 && d != x / d) {
      check(x / d, d);
    }
  }
  
  return ans;
}

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;


    int64_t num = divs_between(x, a, b, c, d);
    int64_t den = (b - a + 1) * 1ll * (d - c + 1);

    int64_t g = gcd(num, den);
    num /= g;
    den /= g;

    cout << num << "/" << den << '\n';
  }

  return 0;
}
