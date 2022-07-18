#include "bits/stdc++.h"

using namespace std;

#define D for (bool _flag = false; _flag; _flag = false)

int lucky[] = {
  4, 7,
  44, 47,
  74, 77,
};

int64_t c(int n, int k) {
  if (k == 0 || k == n) return 1;
  return c(n - 1, k - 1) * n / k;
}

int64_t count_lucky_numbers(int length, int changes_so_far = 0) {
  int64_t total = 0;

  for (auto changes : lucky) {
    if (changes < changes_so_far) continue;
    if (changes == changes_so_far && length == 0) {
      total += 1;
    } else {
      total += c(length - 1, changes - changes_so_far);
    }
  }
  D {
    cerr << "lucky numbers with len: " << length << " and changes: " << changes_so_far << " total: " << total << endl;
  }

  return total;
}

string GetNthLucky(int64_t n) {
  int len = 1;
  bool starts_seven = false;
  for (;; ++len) {
    auto lucky = count_lucky_numbers(len);
    if (lucky == 0) {
      continue;
    }
    D {
      cerr << "len: " << len << " starts with 7: " << starts_seven << " n: " << n << endl;
    }
    
    if (2 * lucky <= n) {
      n -= 2 * lucky;
    } else {
      if (n >= lucky) {
        n -= lucky;
        starts_seven = true;
      }
      break;
    }
  }

  D {
    cerr << "len: " << len << endl;
  }

  string ans;
  int changes = 0;

  for (int i = 0; i < len; ++i) {
    if (starts_seven) {
      ans += '7';
    } else {
      ans += '4';
    }

    int64_t next_four = count_lucky_numbers(len - i - 1, changes + starts_seven);
    int64_t next_seven = count_lucky_numbers(len - i - 1, changes + !starts_seven);

    if (next_four + next_seven <= n) {
      D cerr << "impossible condition on i: " << i << endl;
    }

    if (n < next_four) {
      changes += starts_seven;
      starts_seven = false;
    } else {
      n -= next_four;
      changes += !starts_seven;
      starts_seven = true;
    }
  }

  return ans;
}

bool Check(string lucky_number) {
  int changes = 0;
  for (int i = 1; i < lucky_number.size(); ++i) {
    changes += lucky_number[i] != lucky_number[i - 1];
  }
  if (find(begin(lucky), end(lucky), changes) == end(lucky)) {
    return false;
  } else {
    return true;
  }
}

void Stress() {
  vector<string> lucky_numbers;
  for (int n = 1; n < 100; ++n) {
    lucky_numbers.push_back(GetNthLucky(n));
  }
  assert(is_sorted(begin(lucky_numbers), end(lucky_numbers), [](const string& lhs, const string &rhs) {
    if (lhs.size() != rhs.size()) {
      return lhs.size() < rhs.size();
    } else {
      return lhs < rhs;
    }
  }));
  assert(all_of(begin(lucky_numbers), end(lucky_numbers), Check));
}

int main() {
  D cerr << boolalpha;
  D Stress();

  int64_t n;
  cin >> n;
  --n;
  cout << GetNthLucky(n) << endl;

  return 0;
}
