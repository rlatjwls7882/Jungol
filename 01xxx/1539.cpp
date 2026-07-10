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

struct element {
    ll a, b, c, i;
    bool operator<(const element e) const {
        return a>e.a;
    }
};

ll dp[100], prv[100];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<element> v(n);
    for(int i=0;i<n;i++) {
        cin >> v[i].a >> v[i].b >> v[i].c;
        v[i].i=i+1;
    }
    sort(all(v));

    for(int i=0;i<n;i++) {
        dp[i]=v[i].b;
        prv[i]=-1;
        for(int j=0;j<i;j++) {
            if(v[j].c>v[i].c && dp[j]+v[i].b>dp[i]) {
                dp[i]=dp[j]+v[i].b;
                prv[i]=j;
            }
        }
    }

    int mx=*max_element(dp, dp+n);
    for(int i=0;i<n;i++) {
        if(dp[i]==mx) {
            vector<int> res;
            for(int j=i;j!=-1;j=prv[j]) {
                res.push_back(v[j].i);
            }
            cout << sz(res);
            for(auto e:res) cout << '\n' << e;
            return 0;
        }
    }
}
