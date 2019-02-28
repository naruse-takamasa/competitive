#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define all(a) (a).begin(),(a).end()
#define endl "\n"
#define rep(i, a, b) for (auto (i) = (a); (i) < (b); (i)++)
#define rrep(i, a, b) for (auto (i) = (a); (i) > (b); (i)--)
#define UNIQUE(v) (v).erase(unique((v).begin(), (v).end()), (v).end());

#ifdef LOCAL_DEFINE
struct InitInput{
  InitInput() {
    FILE *stream1;
    stream1=freopen("/Users/aim_cpo/CLionProjects/competitive/in.txt","r",stdin);
    assert(stream1 != nullptr);
    cerr << "This problem is not interactive" << endl;
  }
}LOCAL_INPUT;
struct LOCAL_OUTPUT{
  LOCAL_OUTPUT() {
    FILE *stream2;
    const char *outputfile = "out.txt";
    stream2 = freopen(outputfile, "w", stdout);
    assert(stream2 != nullptr);
    cerr << "output [ " << outputfile << " ]" << endl;
  }
}/*LOCAL_OUTPUT*/;
#define show(x) cerr << #x << " = " << (x) << " (line " << __LINE__ << ")" << endl
#define showV(v, n) do{\
for(int _i_t_e_=0; _i_t_e_<(n);_i_t_e_++)\
cerr<<"("<<_i_t_e_<<" = "<<(v)[_i_t_e_]<<") ";\
cerr<<endl;}while(0)
#define showA(a, n) do{\
for(int _i_t_e_=0;_i_t_e_<(n);_i_t_e_++)\
cerr<<"("<<_i_t_e_<<" = "<<(a)[_i_t_e_]<<") ";\
cerr<<endl;}while(0)
#define showA2(a, n, m) do{\
for(int _i_t_e_=0;_i_t_e_<(n);_i_t_e_++){\
for(int _i_t_e_2=0;_i_t_e_2<(m);_i_t_e_2++){\
cerr<<"("<<_i_t_e_<<", "<<_i_t_e_2<<" = "<<(a)[_i_t_e_][_i_t_e_2]<<") ";\
}cerr<<endl;}cerr<<endl;}while(0)
#else
#define show(x)
#define showV(v, n)
#define showA(a, n)
#define showA2(a, n, m)
#endif

struct InitAim{
  InitAim() {
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cout.precision(12);cout<<fixed;
#ifdef LOCAL_DEFINE
    cerr << "This problem is not interactive" << endl;
#endif
  }
}aim_cpo;

typedef long long ll;
typedef unsigned long long ull;

constexpr const int INT_INF=0x3f3f3f3f; //1061109567
constexpr const ll LL_INF=0x3f3f3f3f3f3f3f3f; //4557430888798830399

template <typename T> bool chmin(T &a, T b){return a>b?(a=b,true):false;}
template <typename T> bool chmax(T &a, T b){return a<b?(a=b,true):false;}
template <typename T> void ln(T i, T n){cout<<(i==n-1?"\n":" ");}
template<typename T, typename S>
ostream &operator<<(ostream &out, const pair<T, S> &pair1) {
  out << '(' << pair1.fi << ", " << pair1.se << ')';
  return out;
}
template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vector1) {
  out << '[';
  for (unsigned int i = 0; i < vector1.size(); i++) {
    out << vector1[i];
    if (i == vector1.size() - 1)out << "]"; else out << ", ";
  }
  return out;
}

// INT
#define GCD(a, b) __gcd(a, b)
template <typename T> T LCM(T a, T b) {return a / GCD(a, b) * b;}
template <typename T> T EXTGCD(T a, T b, T& x, T& y) {
  T d = a;
  if (b != 0) {d=EXTGCD(b,a%b,y,x);y-=(a/b)*x;}
  else x=1,y=0;
  return d;
}
template <typename T> bool is_prime(T a) {
  for(int i=2;i*i<=a;i++)if(a%i==0)return true;
  return false;
}
template <typename T, typename S> T Pow(T a, S b) {
  T res = 1, now = a;
  while(b){if(b&1)res*=now;b>>=1;now*=now;}return res;
}

// MOD
ll MOD = 1000000000L + 7L;
#define add(a, b) ((a % MOD) + (b % MOD)) % MOD
#define mul(a, b) ((a % MOD) * (b % MOD)) % MOD
#define sub(a, b) ((a % MOD) + MOD - (b % MOD)) % MOD
template <typename T, typename S> T ModPow(T a, S b) {
  T res = 1, now = a;
  while(b){if(b&1)res=mul(res,now);b>>=1;now=mul(now,now);}return res;
}
template <typename T> T mod_inverse(T a, T mod, bool prime){ // if mod is prime, "prime" is true.
  if(prime)return ModPow(a, mod - 2);
  else{T x,y;EXTGCD(a,mod,x,y);return (mod+x%mod)%mod;}
}
#define divide(a, b) ((a % MOD) * (mod_inverse(b, MOD, true))) % MOD

//LLの数値をつかう時は最後にLLをつける癖をつけよう
///////////////////////////////////////////////////////////////////////////////////
// VARIABLE
///////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////
// TEMPLATE(data structure)
///////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////
// MAIN
///////////////////////////////////////////////////////////////////////////////////

int main() {
#ifdef LOCAL_DEFINE
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << "s." << endl;
  show(MOD);
#endif
  return 0;
}
