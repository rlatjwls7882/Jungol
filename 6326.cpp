#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("fma")
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define x first
#define y second
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
#define rep(x) for(int __i=(x);__i>0;--__i)
#define compress(x) sort(all(x)), x.erase(unique(all(x)), x.end())

typedef long long ll;
typedef long double ld;
typedef __int128 i128;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> T sq(T x) { return x*x; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ld PI = acosl(-1);
const ld EPS = 1e-10;

mt19937 rd((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rnd_int(0, 0); // rnd_int(rd)
uniform_real_distribution<double> rnd_real(0, 1); // rnd_real(rd)

ll dp[200'000][4];
string rgb="RGB";

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, a, b, c; string s; cin >> n >> s >> a >> b >> c;
    fill(&dp[0][0], &dp[n][0], LINF);
    dp[0][0] = s[0]=='R' ? 0 : c;
    dp[0][3] = a;

    ll res=min(a, b)*n;
    for(int i=1;i<n;i++) {
        res=min(res, dp[i-1][2]+(n-i)*b);
        dp[i][0]=dp[i-1][3];
        dp[i][3]=dp[i-1][3]+a;
        for(int j=0;j<3;j++) {
            dp[i][j] = min(dp[i][j], dp[i-1][(j+2)%3]);
            if(rgb[j]!=s[i]) dp[i][j]+=c;
        }
    }
    cout << min(res, dp[n-1][2]);
}