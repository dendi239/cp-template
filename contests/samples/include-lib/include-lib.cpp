/*
  Author: Me
  Time: 2023-02-11 17:07:59
*/

#include "bits/stdc++.h"
#include "tourist/modular.hpp"

#ifdef DENDI239
#define D                                                                      \
  for (bool _flag_dendi239 = true; _flag_dendi239; _flag_dendi239 = false)
#else
#define D while (false)
#endif

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

using namespace std;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int64_t a, b;
  cin >> a >> b;

  Mint A(a), B(b);
  cout << (A + B) << '\n';  
}
