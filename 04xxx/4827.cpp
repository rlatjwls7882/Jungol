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

int p[1000];
int dp[1000][1001];
vvi conn(1000);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, c; cin >> n >> m >> c;
    for(int i=0;i<n;i++) cin >> p[i];
    while(m--) {
        int a, b; cin >> a >> b;
        conn[a-1].push_back(b-1);
    }

    fill(&dp[0][0], &dp[1000][0], -INF);
    dp[0][0]=0;
    for(int i=0;i<1000;i++) {
        for(int j=0;j<n;j++) {
            if(dp[j][i]==-INF) continue;
            for(int nxt:conn[j]) {
                dp[nxt][i+1] = max(dp[nxt][i+1], dp[j][i]+p[nxt]+c*(i*i-(i+1)*(i+1)));
            }
        }
    }
    int res=0;
    for(int i=1;i<=1000;i++) res=max(res, dp[0][i]);
    cout << res;
}
