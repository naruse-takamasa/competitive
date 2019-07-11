# 構文解析

[参考記事](https://gist.github.com/draftcode/1357281)

上記の参考記事に則って実装するのが安全かな.
演算子の優先順位や括弧への対処の仕方によって、各関数の実装が変わってくるので
そこは臨機応変に.

## 問題
[Bug Hunt](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1282)
これは、数式の構文解析ではないけど、同じような感覚で解ける.  
以下実装
```
map<pair<char, int>, int> GetNum;
map<char, int> GetLen;
typedef string::const_iterator State;
int Error;

int number(State &begin);
int term2(State &begin);

int factor(State &begin) {
  if (isdigit(*begin)) {
    return number(begin);
  } else {
    return term2(begin);
  }
}

int number(State &begin) {
  int ret = 0;
  while (isdigit(*begin)) {
    ret *= 10;
    ret += *begin - '0';
    begin++;
  }
  return ret;
}

pair<char, int> term1(State &begin) {
  char name;
  int idx = -1;
  for (;;) {
    if (('a' <= *begin && *begin <= 'z') || ('A' <= *begin && *begin <= 'Z')) {
      name = *begin;
      begin += 2;
      idx = factor(begin);
      begin++;
    } else {
      break;
    }
  }
  if (idx == -1) {
    Error = 1;
  }
  return mp(name, idx);
}

int term2(State &begin) {
  char name;
  int idx = -1;
  for (;;) {
    if (('a' <= *begin && *begin <= 'z') || ('A' <= *begin && *begin <= 'Z')) {
      name = *begin;
      begin += 2;
      idx = factor(begin);
      begin++;
    } else if (isdigit(*begin)) {
      return number(begin);
    } else {
      break;
    }
  }
  if (GetNum.count(mp(name, idx)) > 0) {
    return GetNum[mp(name, idx)];
  } else {
    Error = 1;
    return -1;
  }
}

pair<pair<char, int>, int> expression(State &begin) {
  pair<char, int> ret1 = term1(begin);
  int ret2 = -1;
  for (;;) {
    if (*begin == '=') {
      ret2 = term2(++begin);
    } else {
      break;
    }
  }
  return mp(ret1, ret2);
}

bool solve() {
  string s;
  getline(cin, s);
  if (s == ".") {
    return false;
  }
  Error = 0;
  GetNum.clear();
  GetLen.clear();
  int cnt = 1;
  bool ng = false;
  while (s != ".") {
    if (ng) {
      getline(cin, s);
      cnt++;
      continue;
    }
    State begin = s.begin();
    pair<pair<char, int>, int> now = expression(begin);
    if (Error == 1) {
      cout << cnt << endl;
      ng = true;
    }
    if (now.se == -1) {
      GetLen[now.fi.fi] = now.fi.se;
    } else {
      if (GetLen[now.fi.fi] > now.fi.se) {
        GetNum[now.fi] = now.se;
      } else {
        Error = 1;
        cout << cnt << endl;
        ng = true;
      }
    }
    getline(cin, s);
    cnt++;
  }
  if (Error == 0) {
    cout << 0 << endl;
  }
  return true;
}
 
int main()
{
  while (solve());
}
```

[Unordered Operators](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2613)
演算子の優先順位が変化するより一般的な構文解析.  
以下実装
```
int ope[] = {'*', '-', '+'};
int priority[] = {0, 0, 0};

typedef string::const_iterator State;

ll factor(State &begin);
ll expression(State &begin);

ll calc(ll a, ll b, char c) {
  if (c == '+') return a + b;
  if (c == '-') return a - b;
  return a * b;
}

ll number(State &begin) {
  ll ret = 0;
  while (isdigit(*begin)) {
    ret *= 10;
    ret += *begin - '0';
    begin++;
  }
  return ret;
}

ll term1(State &begin) {
  ll ret = factor(begin);
  for (;;) {
    bool ok = false;
    rep(i, 0, 3) {
      if (priority[i] != 0) continue;
      if (*begin == ope[i]) {
        ok = true;
        begin++;
        ret = calc(ret, factor(begin), ope[i]);
      }
    }
    if (!ok) break;
  }
  return ret;
}

ll term2(State &begin) {
  ll ret = term1(begin);
  for (;;) {
    bool ok = false;
    rep(i, 0, 3) {
      if (priority[i] != 1) continue;
      if (*begin == ope[i]) {
        ok = true;
        begin++;
        ret = calc(ret, term1(begin), ope[i]);
      }
    }
    if (!ok) break;
  }
  return ret;
}

ll factor(State &begin) {
  if (*begin == '(') {
    begin++;
    ll ret = expression(begin);
    begin++;
    return ret;
  } else {
    return number(begin);
  }
}

ll expression(State &begin) {
  ll ret = term2(begin);
  for (;;) {
    bool ok = false;
    rep(i, 0, 3) {
      if (priority[i] != 2) continue;
      if (*begin == ope[i]) {
        ok = true;
        begin++;
        ret = calc(ret, term2(begin), ope[i]);
      }
    }
    if (!ok) break;
  }
  return ret;
}

int main()
{
  string s; cin >> s;
  sort(ope, ope + 3);
  ll ans = LLONG_MIN;
  do {
    priority[0] = 0;
    rep(i, 0, 2) rep(j, 0, 2) {
      if (i == 0) priority[1] = priority[0];
      else priority[1] = priority[0] + 1;
      if (j == 0) priority[2] = priority[1];
      else priority[2] = priority[1] + 1;
      State begin = s.begin();
      chmax(ans, expression(begin));
    }
  } while (next_permutation(ope, ope + 3));
  cout << ans << endl;
}
```

[Equation](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2401)
論理演算の構文解析.
-演算子をどう処理するかとかの練習.
```
typedef string::const_iterator State;
int factor(State &begin);

int number(State &begin) {
  int ret = 0;
  while (isdigit(*begin)) {
    ret *= 10;
    ret += *begin - '0';
    begin++;
  }
  return ret;
}

int term(State &begin) {
  int ret1 = factor(begin);
  for (;;) {
    if (*begin == '*') {
      begin++;
      ret1 &= factor(begin);
    } else if (*begin == '+') {
      begin++;
      ret1 |= factor(begin);
    } else if (*begin == '-' && *(begin + 1) == '>') {
      begin += 2;
      int ret2 = factor(begin);
      ret1 = (ret1 == 1 && ret2 == 0 ? 0 : 1);
    } else {
      break;
    }
  }
  return ret1;
}

bool expression(State &begin) {
  int ret1 = term(begin);
  begin++;
  int ret2 = term(begin);
  return ret1 == ret2;
}

int factor(State &begin) {
  if (isdigit(*begin)) {
    return number(begin);
  } else if (*begin == '(') {
    begin++;
    int ret = term(begin);
    begin++;
    return ret;
  } else if (*begin == '-') {
    begin++;
    int ret = factor(begin);
    return 1 ^ ret;
  }
}

bool solve() {
  string s; getline(cin, s);
  if (s == "#") return false;
  int n = (int)s.size();
  rep(i, 0, n) {
    if (s[i] == 'T') s[i] = '1';
    else if (s[i] == 'F') s[i] = '0';
  }
  string t = s;
  rep(i, 0, (1 << 11)) {
    rep(j, 0, n) {
      if ('a' <= t[j] && t[j] <= 'k') {
        t[j] = ((i & (1 << (t[j] - 'a'))) == 0 ? '0' : '1');
      }
    }
    State begin = t.begin();
    if (!expression(begin)) {
      cout << "NO" << endl;
      return true;
    }
    t = s;
  }
  cout << "YES" << endl;
  return true;
}

int main()
{
  while (solve());
}
```