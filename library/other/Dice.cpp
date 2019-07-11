#include<bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

class Dice {
public:
  // front, back, right, left, top, bottom
  int number[6];
  // サイコロがメスならis_female = true(1, 2, 3の目が反時計回りになっている)
  Dice(int top, int front, bool is_female) {
    number[4] = top, number[0] = front, number[5] = 7 - top, number[1] = 7 - front;
    if (is_female) {
      number[2] = female[top - 1][front - 1];
      number[3] = 7 - number[2];
    } else {
      number[3] = female[top - 1][front - 1];
      number[2] = 7 - number[3];
    }
    assert(number[2] != -1 && number[3] != -1);
  }

  Dice(int top, int front, int right) { // 3面わかっている
    number[4] = top, number[0] = front, number[2] = right, number[5] = 7 - top, number[1] = 7 - front, number[3] = 7 - right;
  }

  Dice(int front, int back, int right, int left, int top, int bottom) { // 全面わかっている
    number[0] = front, number[1] = back, number[2] = right, number[3] = left, number[4] = top, number[5] = bottom;
  }

  int get_front() { // 手前
    return number[0];
  }

  int get_back() { // 奥
    return number[1];
  }

  int get_right() { // 右
    return number[2];
  }

  int get_left() { // 左
    return number[3];
  }

  int get_top() { // 上底
    return number[4];
  }

  int get_bottom() { // 下底
    return number[5];
  }

  void up() { // y--
    int t[6];
    t[1] = number[4], t[4] = number[0], t[2] = number[2], t[3] = number[3], t[0] = number[5], t[5] = number[1];
    rep(i, 0, 6) number[i] = t[i];
  }
  void down() { // y++
    int t[6];
    t[1] = number[5], t[4] = number[1], t[2] = number[2], t[3] = number[3], t[0] = number[4], t[5] = number[0];
    rep(i, 0, 6) number[i] = t[i];
  }

  void right() { // x++
    int t[6];
    t[1] = number[1],   t[4] = number[3], t[2] = number[4], t[3] = number[5], t[0] = number[0], t[5] = number[2];
    rep(i, 0, 6) number[i] = t[i];
  }

  void left() { // x--
    int t[6];
    t[1] = number[1], t[4] = number[2], t[2] = number[5], t[3] = number[4], t[0] = number[0], t[5] = number[3];
    rep(i, 0, 6) number[i] = t[i];
  }

private:
  int female[6][6] = { {-1, 3, 5, 2, 4, -1},{4, -1, 1, 6, -1, 3},
    {2, 6, -1, -1, 1, 5}, {5, 1, -1, -1, 6, 2}, {3, -1, 6, 1, -1, 4},
    {-1, 4, 2, 5, 3, -1} };
};
