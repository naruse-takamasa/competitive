#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define endl "\n"
#define rep(i, a, b) for (auto i = (a); i < (b); ++i)
#define rrep(i, a, b) for (auto i = (a); i > (b); --i)
#define UNIQUE(v) (v).erase(unique((v).begin(), (v).end()), (v).end())
typedef long long ll;
typedef unsigned long long ull;

#ifdef LOCAL_DEFINE
struct InitInput
{
  InitInput()
  {
    FILE *stream1;
    stream1 = freopen("in.txt", "r", stdin);
    assert(stream1 != nullptr);
    cerr << "This problem is not interactive" << endl;
  }
} LOCAL_INPUT;
struct LOCAL_OUTPUT
{
  LOCAL_OUTPUT()
  {
    FILE *stream2;
    const char *outputfile = "out.txt";
    stream2 = freopen(outputfile, "w", stdout);
    assert(stream2 != nullptr);
    cerr << "output [ " << outputfile << " ]" << endl;
  }
} /*LOCAL_OUTPUT*/;
#define show(x) cerr << #x << " = " << (x) << " (line " << __LINE__ << ")" << endl
#define showA(a, n) \
  do{for(int i=0;i<(n);i++)cerr<<"("<<i<<" = "<<(a)[i]<<") ";cerr<<endl;}while(0)
#define showA2(a, n, m) \
  do {for(int i=0;i<(n);i++){for(int j=0;j<(m);j++){cerr<<"("<<i<<", "<<j<<" = "<<(a)[i][j]<<") ";}cerr<<endl;}cerr<<endl;}while(0)
#else
#define show(x)
#define showA(a, n)
#define showA2(a, n, m)
#endif

struct InitAim
{
  InitAim()
  {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(12);
    cout << fixed;
#ifdef LOCAL_DEFINE
    cerr << "This problem is not interactive" << endl;
#endif
  }
} aim_cpo;

///////////////////////////////////////////////////////////////////////////////////
// TEMPLATE(data structure)
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool chmin(T &a, T b) { return a > b ? (a = b, true) : false; }
template <typename T>
bool chmax(T &a, T b) { return a < b ? (a = b, true) : false; }
template <typename T>
void ln(T i, T n) { cout << (i == n - 1 ? "\n" : " "); }
template <typename T, typename S>
ostream &operator<<(ostream &out, const pair<T, S> &pair1)
{
  out << '(' << pair1.fi << ", " << pair1.se << ')';
  return out;
}
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &vector1)
{
  out << '[';
  for (unsigned int i = 0; i < vector1.size(); i++)
  {
    out << vector1[i];
    if (i == vector1.size() - 1)
      out << "]";
    else
      out << ", ";
  }
  return out;
}

#define GCD(a, b) __gcd(a, b)
template <typename T>
T LCM(T a, T b)
{
  return a / GCD(a, b) * b;
}
template <typename T>
T EXTGCD(T a, T b, T &x, T &y)
{
  T d = a;
  if (b != 0)
  {
    d = EXTGCD(b, a % b, y, x);
    y -= (a / b) * x;
  }
  else
    x = 1, y = 0;
  return d;
}
template <typename T>
bool is_prime(T a)
{
  for (int i = 2; i * i <= a; i++)
    if (a % i == 0)
      return true;
  return false;
}
template <typename T, typename S>
T Pow(T a, S b)
{
  T res = 1, now = a;
  while (b)
  {
    if (b & 1)
      res *= now;
    b >>= 1;
    now *= now;
  }
  return res;
}

/* MOD */
ll MOD = 1000000000L + 7L;
#define Madd(a, b) (((a) % MOD) + ((b) % MOD)) % MOD
#define Mmul(a, b) (((a) % MOD) * ((b) % MOD)) % MOD
#define Msub(a, b) (((a) % MOD) + MOD - ((b) % MOD)) % MOD
template <typename T, typename S>
T ModPow(T a, S b)
{
  assert(b >= 0);
  T res = 1, now = Msub(a, 0);
  while (b)
  {
    if (b & 1)
      res = Mmul(res, now);
    b >>= 1;
    now = Mmul(now, now);
  }
  return res;
}
template <typename T>
T ModInverse(T a, T mod, bool prime)
{ // if mod is prime, "prime" is true.
  if (prime)
    return ModPow(a, mod - 2);
  else
  {
    T x, y;
    EXTGCD(a, mod, x, y);
    return (mod + x % mod) % mod;
  }
}
template <typename T>
T EulerTotient(T a)
{
  vector<pair<int, int>> v;
  for (T i = 2; i * i <= a; i++)
  {
    int cnt = 0;
    while (a % i == 0)
    {
      cnt++;
      a /= i;
    }
    if (cnt != 0)
      v.emplace_back(i, cnt);
  }
  if (a != 1)
    v.emplace_back(a, 1);
  //showV(v, (int) v.size());
  T res = 1;
  for (int i = 0; i < (int)v.size(); i++)
  {
    if (v[i].se == 1)
    {
      //res *= v[i].fi - 1;
      res = Mmul(res, v[i].fi - 1);
    }
    else
    {
      //res *= Pow(v[i].fi, v[i].se) - Pow(v[i].fi, v[i].se - 1);
      res = Mmul(res, Msub(ModPow(v[i].fi, v[i].se), ModPow(v[i].fi, v[i].se - 1)));
    }
  }
  return res;
}
#define Mdivide(a, b) Mmul(((a) % MOD), (ModInverse((b), MOD, true))) % MOD
ll comb(ll a, ll b)
{
  chmin(b, a - b);
  ll res = 1LL, now = a;
  for (ll i = 1; i <= b; i++)
  {
    res = Mmul(res, now);  //res *= now;
    res = Mdivide(res, i); // res /= i;
    now--;
  }
  return res;
}

template <typename T>
class BIT
{
public:
  BIT(int size)
  {
    BITTable.assign(++size, 0);
  }
  T sum(int k)
  {
    T res = 0;
    for (++k; k > 0; k -= k & -k)
    {
      res += BITTable[k];
    }
    return res;
  }
  T sum(int l, int r)
  {
    if (l == 0)
      return sum(r);
    return sum(r) - sum(l - 1);
  }
  void update(int k, T x)
  { // b[k] += x;
    for (++k; k < (int)BITTable.size(); k += k & -k)
      BITTable[k] += x;
  }

private:
  vector<T> BITTable;
};

template <typename T>
class IntervalTree
{
  using F = function<T(T, T)>;

public:
  IntervalTree(int n, const F func, const T init) : func(func), init(init)
  {
    size = 1;
    while ((int)size < n)
      size <<= 1;
    table.assign(2 * size, init);
  }
  void set(int k, T &x)
  {
    table[size + k] = x;
  }
  void build()
  {
    for (int i = size - 1; i >= 0; --i)
    {
      table[i] = func(table[i * 2], table[i * 2 + 1]);
    }
  }
  void update(int k, const T &x)
  {
    k += size;
    table[k] = x;
    while (k >>= 1)
    {
      table[k] = func(table[k * 2], table[k * 2 + 1]);
    }
  }
  T query(int a, int b)
  {
    T L = init, R = init;
    for (a += size, b += size; a < b; a >>= 1, b >>= 1)
    {
      if (a & 1)
        L = func(L, table[a++]);
      if (b & 1)
        R = func(table[--b], R);
    }
    return func(L, R);
  }
  T operator[](const int k) const
  {
    return table[k + size];
  }

private:
  unsigned int size;
  vector<T> table;
  const F func;
  const T init;
};

class UnionFind
{
public:
  explicit UnionFind(int _n) : n(_n)
  {
    par.resize(static_cast<unsigned long>(_n));
    rank.resize(static_cast<unsigned long>(_n));
    sizes.resize(static_cast<unsigned long>(_n));
    for (int i = 0; i < _n; i++)
    {
      par[i] = i;
      rank[i] = 0;
      sizes[i] = 1;
    }
  }
  int find(int a)
  {
    if (par[a] == a)
      return a;
    return par[a] = find(par[a]);
  }
  bool same(int a, int b)
  {
    return find(a) == find(b);
  }
  void unite(int a, int b)
  {
    link(find(a), find(b));
  }
  int size(int a)
  {
    return sizes[find(a)];
  }
  void view()
  {
    for (int i = 0; i < n; i++)
    {
      cout << " par"
           << "[" << i << "]=" << par[i] << ((i == n - 1) ? "\n" : ",");
    }
    for (int i = 0; i < n; i++)
    {
      cout << "size"
           << "[" << i << "]=" << sizes[i] << ((i == n - 1) ? "\n" : ",");
    }
    cout << endl;
  }

private:
  void link(int a, int b)
  {
    if (same(a, b))
      return;
    if (rank[a] > rank[b])
    {
      par[b] = a;
      sizes[a] += sizes[b];
      sizes[b] = 0;
    }
    else
    {
      par[a] = b;
      if (rank[a] == rank[b])
        rank[b]++;
      sizes[b] += sizes[a];
      sizes[a] = 0;
    }
  }
  int n;
  vector<int> par;
  vector<int> rank;
  vector<int> sizes;
};

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

template< typename flow_t, typename cost_t >
struct PrimalDual {
  const cost_t INF;

  struct edge {
    int to;
    flow_t cap;
    cost_t cost;
    int rev;
    bool isrev;
  };
  vector< vector< edge > > graph;
  vector< cost_t > potential, min_cost;
  vector< int > prevv, preve;

  PrimalDual(int V) : graph(V), INF(numeric_limits< cost_t >::max()) {}

  void add_edge(int from, int to, flow_t cap, cost_t cost) {
    graph[from].emplace_back((edge) {to, cap, cost, (int) graph[to].size(), false});
    graph[to].emplace_back((edge) {from, 0, -cost, (int) graph[from].size() - 1, true});
  }

  cost_t min_cost_flow(int s, int t, flow_t f) {
    int V = (int) graph.size();
    cost_t ret = 0;
    using Pi = pair< cost_t, int >;
    priority_queue< Pi, vector< Pi >, greater< Pi > > que;
    potential.assign(V, 0);
    preve.assign(V, -1);
    prevv.assign(V, -1);

    while(f > 0) {
      min_cost.assign(V, INF);
      que.emplace(0, s);
      min_cost[s] = 0;
      while(!que.empty()) {
        Pi p = que.top();
        que.pop();
        if(min_cost[p.second] < p.first) continue;
        for(int i = 0; i < graph[p.second].size(); i++) {
          edge &e = graph[p.second][i];
          cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second] - potential[e.to];
          if(e.cap > 0 && min_cost[e.to] > nextCost) {
            min_cost[e.to] = nextCost;
            prevv[e.to] = p.second, preve[e.to] = i;
            que.emplace(min_cost[e.to], e.to);
          }
        }
      }
      if(min_cost[t] == INF) return -1;
      for(int v = 0; v < V; v++) potential[v] += min_cost[v];
      flow_t addflow = f;
      for(int v = t; v != s; v = prevv[v]) {
        addflow = min(addflow, graph[prevv[v]][preve[v]].cap);
      }
      f -= addflow;
      ret += addflow * potential[t];
      for(int v = t; v != s; v = prevv[v]) {
        edge &e = graph[prevv[v]][preve[v]];
        e.cap -= addflow;
        graph[v][e.rev].cap += addflow;
      }
    }
    return ret;
  }

  void output() {
    for(int i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << rev_e.cap + e.cap << ")" << endl;
      }
    }
  }
};


///////////////////////////////////////////////////////////////////////////////////
// MAIN
///////////////////////////////////////////////////////////////////////////////////
// 735134400 約数が1344個ある高度合成数(<= 1e9)
// 897612484786617600 約数が103680個ある高度合成数(<= 1e18)
// 苦手分野 重複順列
// LLの数値をつかう時は最後にLLをつける癖をつけよう



int main()
{
#ifdef LOCAL_DEFINE
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << "s." << endl;
  show(MOD);
#endif
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////
// NOTE
///////////////////////////////////////////////////////////////////////////////////
/*
*/