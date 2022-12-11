#include "bits/stdc++.h"

#define D for (bool _flag = false; _flag; _flag = false)

using namespace std;

const int mod = 1000000007;

int &inc(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
  return x;
}

int &mul(int &x, int y) { return x = (x * 1ll * y) % mod; }

int bin_pow_mod(int x, int n) {
  if (n == 0)
    return 1;
  if (n % 2 == 0)
    return bin_pow_mod(x * 1ll * x % mod, n / 2);
  else
    return bin_pow_mod(x * 1ll * x % mod, n / 2) * 1ll * x % mod;
}

int inv(int x) { return bin_pow_mod(x, mod - 2); }

struct STree {
  struct Node {
    int value = 0;
    int mult = 1;

    int Value() const { return value * 1ll * mult % mod; }
  };

  int n_;
  vector<Node> values;

  void Push(int i, int il, int ir) {
    int im = (il + ir) / 2, li = i + 1, ri = i + 2 * (im - il);
    mul(values[i].value, values[i].mult);
    mul(values[li].mult, values[i].mult);
    mul(values[ri].mult, values[i].mult);
    values[i].mult = 1;
  }

  void Update(int i, int il, int ir) {
    int im = (il + ir) / 2, li = i + 1, ri = i + 2 * (im - il);
    inc(inc(values[i].value = 0, values[li].Value()), values[ri].Value());
  }

  int build(int i, int il, int ir) {
    if (il == ir - 1) {
      values[i].value = 1;
      return values[i].value;
    }

    int im = (il + ir) / 2;
    return inc(inc(values[i].value, build(i + 1, il, im)),
               build(i + 2 * (im - il), im, ir));
  }

  STree(int n) : n_(n), values(2 * n - 1) { build(0, 0, n); }

  struct Multiplier {
    STree *tree;
    int l, r;
    int multiplier;

    void Mult(int i, int il, int ir) const {
      if (r <= il || ir <= l)
        return;
      if (l <= il && ir <= r) {
        mul(tree->values[i].mult, multiplier);
        return;
      }

      tree->Push(i, il, ir);
      const int im = (il + ir) / 2;
      Mult(i + 1, il, im);
      Mult(i + 2 * (im - il), im, ir);
      tree->Update(i, il, ir);
    }
  };

  void Mult(int l, int r, int multiplier) {
    D cerr << "Mult:: " << l << ".." << r << " " << multiplier << endl;
    Multiplier{this, l, r, multiplier}.Mult(0, 0, n_);
  }

  struct Query {
    STree *tree;
    int l, r;
    int result;

    void query(int i, int il, int ir) {
      if (r <= il || ir <= l)
        return;
      if (l <= il && ir <= r) {
        inc(result, tree->values[i].Value());
        return;
      }

      tree->Push(i, il, ir);
      const int im = (il + ir) / 2;
      query(i + 1, il, im);
      query(i + 2 * (im - il), im, ir);
    }
  };

  int Sum(int l, int r) {
    Query q{this, l, r, 0};
    q.query(0, 0, n_);
    D cerr << "Query:: " << l << ".." << r << " is " << q.result << endl;
    return q.result;
  }
};

int solve(const vector<int> &as, const int k) {
  const int n = as.size();

  map<int, int> prev;
  STree tree(n);

  D cerr << "here 1" << endl;

  int half = inv(2);
  int total = bin_pow_mod(2, k);
  int answer = 0;

  for (int i = 0; i < n; ++i) {
    D cerr << "here at i=" << i << endl;
    tree.Mult(prev[as[i]], i + 1, half);
    prev[as[i]] = i + 1;
    inc(answer, tree.Sum(0, i) * 1ll * total % mod);
    D {
      break;
      cerr << "current values: ";
      for (int i = 0; i < n; ++i) {
        cerr << setw(3) << total * 1ll * tree.Sum(i, i + 1) % mod << " ";
      }
      cerr << endl;
    }
  }

  mul(answer, 2);
  inc(answer, (total * 1ll * half % mod) * 1ll * n % mod);

  return answer;
}

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> as(n);
  for (auto &a : as)
    cin >> a;

  cout << solve(as, k) << '\n';

  return 0;
}
