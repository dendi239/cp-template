#include "bits/stdc++.h"
#include <ctime>

using namespace std;

#define D for (bool _flag = false; _flag; _flag = false)

const int mod = 1000000007;

int &inc(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
  return x;
}

int &mul(int &x, int y) { return x = (x * 1ll * y) % mod; }

int bin_pow(int x, int n) {
  if (n == 0)
    return 1;
  if (n % 2) {
    return x * 1ll * bin_pow(x * 1ll * x % mod, n / 2) % mod;
  } else {
    return bin_pow(x * 1ll * x % mod, n / 2);
  }
}

int solve(const vector<int> &as, const vector<int> &bs) {
  int min_a = *min_element(as.begin(), as.end());
  int min_b = *min_element(bs.begin(), bs.end());

  int min_table = max(min_a, min_b);
  int cnt_a =
      count_if(as.begin(), as.end(), [&](int a) { return a <= min_table; });
  int cnt_b =
      count_if(bs.begin(), bs.end(), [&](int b) { return b <= min_table; });

  int result = mod - 1;
  inc(result, bin_pow(min_table + 1, cnt_a));
  inc(result, bin_pow(min_table + 1, cnt_b));

  D {
    cerr << "solve [";
    for (auto a : as) {
      cerr << " " << a;
    }
    cerr << " ], [";
    for (auto b : bs) {
      cerr << " " << b;
    }
    cerr << " ] = " << result << endl;
  }

  return result;
}

vector<int> get_factors(int p, const vector<int> &as) {
  vector<int> as_;
  as_.reserve(as.size());
  for (auto a : as) {
    int alpha = 0;
    while (a % p == 0) {
      a /= p;
      alpha++;
    }
    as_.push_back(alpha);
  }
  return as_;
}

int solve(int p, const vector<int> &as, const vector<int> &bs) {
  return solve(get_factors(p, as), get_factors(p, bs));
}

int gcd(int a, int b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

vector<int> get_primes() {
  const int MAX_PRIME = 1000000;
  vector<bool> is_prime(MAX_PRIME, true);
  vector<int> primes;
  for (int p = 2; p < MAX_PRIME; p++) {
    if (is_prime[p]) {
      primes.push_back(p);
      if (p > MAX_PRIME / p) {
        continue;
      }
      for (int q = p * p; q < MAX_PRIME; q += p) {
        is_prime[q] = false;
      }
    }
  }

  return primes;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> as(n), bs(m);
  for (auto &a : as)
    cin >> a;
  for (auto &b : bs)
    cin >> b;

  int gcd_rows = 0;
  for (auto a : as)
    gcd_rows = gcd(gcd_rows, a);

  int gcd_columns = 0;
  for (auto b : bs)
    gcd_columns = gcd(gcd_columns, b);

  auto primes = get_primes();

  int result = 1;
  set<int> used_primes{1};

  D {
    cerr << "gcd_rows = " << gcd_rows << endl;
    cerr << "gcd_columns = " << gcd_columns << endl;
    cerr << "primes:";
    for (int i = 0; i < 10; ++i) 
      cerr << " " << primes[i];
    cerr << endl;
  }

  auto record = [&](int p) {
    if (used_primes.count(p))
      return;
    used_primes.insert(p);
    mul(result, solve(p, as, bs));
  };

  for (auto total : {gcd_rows, gcd_columns}) {
    for (int p : primes) {
      if (total % p == 0) {
        record(p);
        while (total % p == 0) {
          total /= p;
        }
      }
    }
    record(total);
  }

  cout << result << '\n';
}
