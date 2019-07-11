#include<bits/stdc++.h>
using namespace std;

typedef string::const_iterator State;


// 例えば、普段の数式を構文解析すると以下のようになる.

/////////////////////////////////////////////////////////////////
//数字の文字列を数字に直す.
/////////////////////////////////////////////////////////////////
int number(State &begin) {
  int ret = 0;
  while (isdigit(*begin)) {
    ret *= 10;
    ret += *begin - '0';
    begin++;
  }
  return ret;
}

/////////////////////////////////////////////////////////////////
//優先順位が最上位の演算子の計算
/////////////////////////////////////////////////////////////////
int term(State &begin) {
  int ret = factor(begin);
  for (;;) {
    if (*begin == '*') {
      begin++;
      ret *= factor(begin);
    } else if (*begin == '/') {
      begin++;
      ret /= factor(begin);
    } else {
      break;
    }
  }
  return ret;
}

/////////////////////////////////////////////////////////////////
//括弧への対処
/////////////////////////////////////////////////////////////////
int factor(State &begin) {
  if (*begin == '(') {
    begin++;
    int ret = expression(begin);
    begin++;
    return ret;
  } else {
    return number(begin);
  }
}

/////////////////////////////////////////////////////////////////
//優先順位が最低の演算子の計算
/////////////////////////////////////////////////////////////////
int expression(State &begin) {
  int ret = term(begin);
  for (;;) {
    if (*begin == '+') {
      begin++;
      ret += term(begin);
    } else if (*begin == '-') {
      begin++;
      ret -= term(begin);
    } else {
      break;
    }
  }
  return ret;
}

/////////////////////////////////////////////////////////////////
//安全に入力してね
/////////////////////////////////////////////////////////////////
int main(){
  int n; cin >> n;
  cin.ignore();
  for (int i = 0; i < n; i++) {
    string s; getline(cin, s);
    State begin = s.begin();
    int ans = expression(begin);
    cout << ans << endl;
  }
}