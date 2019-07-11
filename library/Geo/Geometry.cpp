#include<bits/stdc++.h>

namespace geo
{
#define IL inline
typedef double D;
typedef bool B;
typedef complex<D> P;
#define X real()
#define Y imag()
ostream &operator<<(ostream &out, const P &point1) // Pの出力
{
  out << '(' << point1.X << ", " << point1.Y << ')';
  return out;
}
B comp(const P &l, const P &r)
{
  return (l.X == r.X) ? l.Y < r.Y : l.X < r.X;
}
typedef pair<P, P> L;  //line
typedef pair<P, P> LS; //line segment
typedef pair<P, D> C;  //circle
typedef vector<P> Poly;
const D EPS = 1e-8;
//Decompotision Macro
#define DCl(a, b, l) \
  P a, b;            \
  tie(a, b) = l
#define DCc(a, b, c) \
  P a;               \
  D b;               \
  tie(a, b) = c

//A dot B
IL D dot(P a, P b) { return a.X * b.X + a.Y * b.Y; }
//A cross B
IL D cross(P a, P b) { return a.X * b.Y - a.Y * b.X; }
IL D ccw(P a, P b, P c)
{
  return cross(b - a, c - a);
}

// 未検証!!
IL P rotation(P a, double angle) {
  a *= exp(complex<double>(.0, angle * M_PI / 180.0));
  return a;
}

IL int sgn(P a, P b, P c)
{
  if (cross(b - a, c - a) > EPS)
    return 1;
  if (cross(b - a, c - a) < -EPS)
    return -1;
  if (dot(b - a, c - a) < -EPS)
    return 2; // b-a-c
  if (dot(a - b, c - b) < -EPS)
    return -2; // a-b-c
  return 0;
}
IL D signed_distance_P_L(P p, L l)
{
  DCl(a, b, l);
  return ccw(a, b, p) / abs(b - a);
}

IL D distance_P_L(P p, L l) // 点と直線の距離
{
  return abs(signed_distance_P_L(p, l));
}

IL D distance_P_P(P p1, P p2) // 二点間距離
{
  return abs(p1 - p2);
}

IL D distance_P_LS(P p, LS ls) // 点と線分の距離
{
  DCl(a, b, ls);
  if (dot(b - a, p - a) < EPS)
    return abs(p - a);
  if (dot(a - b, p - b) < EPS)
    return abs(p - b);
  return abs(cross(b - a, p - a)) / abs(b - a);
}

IL B is_L_L(L p, L q)
{
  DCl(a, b, p);
  DCl(c, d, q);
  return abs(cross(a - b, c - d)) > EPS ||
         abs(cross(a - b, d - b)) < EPS;
}
IL B is_L_LS(L l, LS ls)
{
  DCl(a, b, l);
  DCl(c, d, ls);
  return ccw(a, b, c) * ccw(a, b, d) < EPS;
}
IL B is_LS_LS(LS p, LS q)
{
  DCl(a, b, p);
  DCl(c, d, q);
  return sgn(a, b, c) * sgn(a, b, d) <= 0 && sgn(c, d, a) * sgn(c, d, b) <= 0;
}

IL D distance_LS_LS(LS p, LS q)
{
  if (is_LS_LS(p, q))
    return 0;
  return min({distance_P_LS(p.fi, q),
              distance_P_LS(p.se, q),
              distance_P_LS(q.fi, p),
              distance_P_LS(q.se, p)});
}

//caution: have to use isintersected_L_L before this function
IL P cross_L_L(L p, L q)
{
  DCl(a, b, p);
  D d1 = signed_distance_P_L(a, q);
  D d2 = signed_distance_P_L(b, q);
  return (a * d2 - b * d1) / (d2 - d1);
}

IL B is_C_C(C p, C q)
{
  DCc(cp, rp, p);
  DCc(cq, rq, q);
  D d = abs(cp - cq);
  return abs(rp - rq) - d < EPS &&
         rp + rq - d > -EPS;
}
IL LS cross_C_C(C p, C q)
{
  DCc(cp, rp, p);
  DCc(cq, rq, q);
  D d = abs(cp - cq);
  D rc = (d * d + rp * rp - rq * rq) / (2 * d);
  D rs = sqrt(rp * rp - rc * rc);
  P diff = (cq - cp) / d;
  return {cp + P(rc, rs) * diff, cp + P(rc, -rs) * diff};
}
IL Poly convex_hull(Poly p)
{
  int n = p.size();
  Poly res(2 * n);
  int k = 0, t;
  sort(all(p), comp);
  rep(i, 0, n)
  {
    while (k > 1 && ccw(res[k - 2], res[k - 1], p[i]) < EPS)
      k--;
    res[k++] = p[i];
  }
  t = k;
  rep(j, 0, n - 1)
  {
    int i = n - 2 - j;
    while (k > t && ccw(res[k - 2], res[k - 1], p[i]) < EPS)
      k--;
    res[k++] = p[i];
  }
  res.resize(k - 1);
  return res;
}
IL B convex_in(Poly &l, P &p)
{
  int a = 0, b = l.size(), c;
  D A, C;
  P g = (l[a] + l[b - 1] + l[b / 2]) / 3.0;
  while (b - a > 1)
  {
    c = (a + b) / 2;
    A = cross(l[a] - g, p - l[a]);
    C = cross(l[c] - g, p - l[c]);
    if (cross(l[a] - g, l[c] - g) >= 0)
    {
      if (A > -EPS && C < -EPS)
        b = c;
      else
        a = c;
    }
    else
    {
      if (C < -EPS || A > -EPS)
        b = c;
      else
        a = c;
    }
  }
  return (cross(l[b % l.size()] - l[a], p - l[b % l.size()]) > -EPS);
}

//not necessary?
IL D convex_area(Poly &l)
{
  double res = 0;
  int n = l.size();
  rep(i, 2, n)
      res += (abs(cross(l[i - 1] - l[0], l[i] - l[i - 1]))) / 2.0;
  return res;
}
IL D area(Poly &l)
{
  double res = 0;
  int n = l.size();
  rep(i, 0, n)
      res += cross(l[i], l[(i + 1) % n]);
  return abs(res) / 2.0;
}
inline vector<L> tangent_line(C c, P p)
{
  vector<L> res;
  DCc(cp, r, c);
  P v = p - cp;
  D dist = abs(v);
  if (dist - r > -EPS)
  {
    double _cos = r / dist;
    double _sin = sqrt(1.0 - _cos * _cos);
    v = v * (r / dist);
    {
      P e = P(_cos * v.X - _sin * v.Y, _sin * v.X + _cos * v.Y);
      res.push_back({p, cp + e});
    }
    if (dist - r > EPS)
    {
      P e = P(_cos * v.X + _sin * v.Y, -_sin * v.X + _cos * v.Y);
      res.push_back({p, cp + e});
    }
  }
  return res;
}
IL vector<L> inner_common_tangent_line(C p, C q)
{
  vector<L> res;
  DCc(Mp, Rp, p);
  DCc(Mq, Rq, q);
  D dist = abs(Mp - Mq);
  if (dist - (Rp + Rq) > -EPS)
  {
    P mid = (Mq * Rp + Mp * Rq) / (Rp + Rq);
    res = tangent_line(p, mid);
  }
  return res;
}
inline vector<L> outer_common_tangent_line(C p, C q)
{
  vector<L> res;
  DCc(Mp, Rp, p);
  DCc(Mq, Rq, q);
  P v = Mp - Mq;
  D dist = abs(v);
  if (dist - abs(Rp - Rq) > -EPS)
  {
    if (abs(Rp - Rq) < EPS)
    {
      P e = v * P(0, 1);
      e = e / dist;
      res.pb(L(Mp + e, Mq + e));
      res.pb(L(Mp - e, Mq - e));
    }
    else
    {
      P mid = Mp + (Mq - Mp) * Rp / (Rp - Rq);
      res = tangent_line(p, mid);
    }
  }
  return res;
}

vector<Poly> decomposition(Poly p)
{
  int n = p.size();
  vector<Poly> res;
  while (n >= 3)
  {
    [&]() {
      rep(i, 0, n)
      {
        P a = p[i];
        P b = p[(i + 1) % n];
        P c = p[(i + 2) % n];
        if (ccw(a, b, c) < 0)
          continue;
        if ([&]() {
              rep(j, 3, n)
              {
                P d = p[(i + j) % n];
                if (ccw(a, b, d) > -EPS && ccw(b, c, d) > -EPS && ccw(c, a, d) > -EPS)
                  return true;
              }
              return false;
            }())
          continue;
        Poly nxt;
        rep(j, 0, n) if ((i + j) % n != (i + 1) % n)
            nxt.push_back(p[(i + j) % n]);
        swap(p, nxt);
        res.push_back({a, b, c});
        n--;
        return;
      }
    }();
  }
  return res;
}
int in_triangle(P p, Poly q)
{
  rep(i, 0, 3) if (abs(p - q[i]) < EPS) return 3; //on point
  rep(i, 0, 3)
  {
    int s = sgn(q[i], q[(i + 1) % 3], p);
    if (s != 1)
    {
      if (s == 0)
        return 2; //on line
      else
        return 0; // not in
    }
  }
  return 1; // inside triangle
}
int in_C(P q, C c) // 円での点の内外判定(円周上も判定)
{
  DCc(p, r, c);
  if (abs(r - abs(p - q)) < EPS)
    return 2; // 円周
  return r - abs(p - q) > -EPS ? 1 : 0;
}
int is_triangle_C(Poly t, C c)
{
  t = convex_hull(t);
  DCc(p, r, c);
  int cnt = 0;
  rep(i, 0, 3)
      cnt += (in_C(t[i], c) > 0);
  if (cnt == 3)
    return 3; // t in c
  if (cnt == 0)
  {
    double d = distance_P_LS(p, LS(t[2], t[0]));
    rep(i, 0, 2)
        d = min(d, distance_P_LS(p, LS(t[i], t[i + 1])));
    if (r - d > EPS)
      return 1; //intersect
    if (in_triangle(p, t))
      return 2; //c in t
    else if (r - d < -EPS)
      return 0; //not intersect
  }
  return 1; //intersect
}

//p must be convex and ccw
LS diameter(Poly &p)
{
  int n = p.size();
  int is = 0, js = 0;
  rep(i, 0, n) if (p[i].Y > p[is].Y)
      is = i;
  rep(i, 0, n) if (p[i].Y < p[js].Y)
      js = i;
  LS res = {p[is], p[js]};
  {
    int i = is;
    int j = js;
    do
    {
      int ni = (i + 1) % n;
      int nj = (j + 1) % n;
      if (cross(p[ni] - p[i], p[nj] - p[j]) < EPS)
        i = ni;
      else
        j = nj;
      if (abs(res.fi - res.se) < abs(p[i] - p[j]))
        res = LS(p[i], p[j]);
    } while (i != is || j != js);
  }
  return res;
}

Poly cross_C_L(C c, L v)
{
  DCc(p, r, c);
  DCl(a, b, v);
  a -= p;
  b -= p;
  P u = a - b;
  u = P(-u.Y, u.X);
  P x = cross_L_L({a, b}, {P(0, 0), u});
  D d = abs(x);
  Poly res;
  if (d - r > EPS)
    return res;
  D y = sqrt(r * r - d * d);
  res.pb(p + x + (b - a) * y / abs(b - a));
  //if(d-r>-EPS)return res;
  res.pb(p + x + (a - b) * y / abs(b - a));
  return res;
}

pair<C, C> GetC_p_p_r(P p1, P p2, D r) // 二点と半径から２つの円を求める
{
  D d = distance_P_P(p1, p2);
  assert(d <= 2. * r); // 二点間の距離は2 * r以内じゃないと同じ円周上に存在することはできない.
  P mid = (p1 + p2) / 2.;
  P NormalVector = (p1 - p2) / d * sqrt(r * r - d * d / 4.);
  NormalVector = P(NormalVector.Y, -NormalVector.X);
  P center1 = mid + NormalVector;
  P center2 = mid - NormalVector;
  return mp(C(center1, r), C(center2, r));
}
} // namespace geo
