#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Dinic{
public:
  Dinic(int SIZE) :SIZE(SIZE) {
    v = vector<vector<tuple<int, T, int>>>(SIZE + 10);
  }

  void AddEdge(int from, int to, T cap) {
    v[from].push_back(make_tuple(to, cap, v[to].size()));
    v[to].push_back(make_tuple(from, 0, v[from].size() - 1));
  }

  void bfs(int s) {
    level = vector<int>(SIZE + 10, -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int now = q.front(); q.pop();
      for (int i = 0; i < (int)v[now].size(); i++) {
        int next, nextrv; T nextc; tie(next, nextc, nextrv) = v[now][i];
        if (nextc > 0 && level[next] < 0) {
          level[next] = level[now] + 1;
          q.push(next);
        }
      }
    }
  }

  T dfs(int now, int t, T f) {
    if (now == t) return f;
    for (int &i = iter[now]; i < (int)v[now].size(); i++) {
      int next, nextrv; T nextc; tie(next, nextc, nextrv) = v[now][i];
      if (nextc > 0 && level[now] < level[next]) {
        T d = dfs(next, t, min(f, nextc));
        if (d > 0) {
          get<1>(v[now][i]) -= d;
          get<1>(v[next][nextrv]) += d;
          return d;
        }
      }
    }
    return 0;
  }

  T max_flow(int s, int t) {
    T flow = 0;
    for (;;) {
      bfs(s);
      if (level[t] < 0) return flow;
      iter = vector<int>(SIZE + 10, 0);
      int f;
      while ((f = dfs(s, t, INT_MAX)) > 0) {
        flow += f;
      }
    }
  }
private:
  int SIZE;
  vector<vector<tuple<int, T, int>>> v;
  vector<int> level, iter;
};