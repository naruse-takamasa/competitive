#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define all(a) (a).begin(),(a).end()
#define endl "\n"
#define aim_cpo do{ios::sync_with_stdio(false);\
cin.tie(nullptr);cout.precision(10);cout<<fixed;}while(0)
#define LOCAL_INPUT do{FILE *stream1;\
stream1=freopen("/Users/aim_cpo/CLionProjects/competitive/in.txt","r",stdin);\
if(stream1==nullptr)return 0;}while(0)

#ifdef LOCAL_DEFINE
#define show(x) cerr << #x << " = " << x << endl
#else
#define show(x)
#endif

typedef long long ll;
typedef unsigned long long ull;

constexpr const int INT_INF=0x3f3f3f3f; // 1061109567
constexpr const ll LL_INF=0x3f3f3f3f3f3f3f3f; // 4557430888798830399

template <typename T> bool chmin(T &a, T b) {
	if (a > b) {a = b;return true;}return false;
}

template <typename T> bool chmax(T &a, T b) {
	if (a < b) {a = b;return true;}return false;
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
	for(int i=2;i*i<=a;i++)if(a%i==0)return 1;
	return 0;
}

// MOD
const ll MOD = (ll)1e9 + 7;
#define add(a, b) ((a % MOD) + (b % MOD)) % MOD
#define mul(a, b) ((a % MOD) * (b % MOD)) % MOD
#define sub(a, b) ((a % MOD) + MOD - (b % MOD)) % MOD
template <typename T> T mod_inverse(T a, T mod, bool prime){ // if mod is prime, "prime" is true.
	if(prime){
		T tmp=mod-2,now=a,res=1;while(tmp){if(tmp&1)res=mul(res,now);now=mul(now,now);tmp>>=1;}
		return res;
	}else{T x,y;EXTGCD(a,mod,x,y);return (mod+x%mod)%mod;}
}
#define divide(a, b) ((a % MOD) * (mod_inverse(b, MOD, true))) % MOD

//LLの数値をつかう時は最後にLをつける癖をつけよう
//
//  ┏┓┏┓　┓　┏┓
//  ┏┛┃┃　┃　┗┫
//  ┗┛┗┛　┻　┗┛
//
//   謹┃賀┃新┃年┃
//   ━┛━┛━┛━┛
//WWWWWWWWWWWWWWWWWWWWWW

int n;

int main() {
	aim_cpo; // インタラクティブのときは消すように.
#ifdef LOCAL_DEFINE
	LOCAL_INPUT; // インタラクティブのときは消すように.
	show(MOD);
//    FILE *stream2;
//    stream2 = freopen("out.txt", "w", stdout);
//    if (stream2 == NULL) return 0;
#endif
#ifdef  LOCAL_DEFINE
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << "s.\n";
#endif
	return 0;
}