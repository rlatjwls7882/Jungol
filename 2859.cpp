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

vvll sum(200'001);
vvi color(200'001);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pii> v(n);
    vll bsz(n+1), allSum(n+1);
    for(int i=0;i<n;i++) {
        cin >> v[i].x >> v[i].y;
        color[v[i].x].push_back(v[i].y);
        bsz[i]=v[i].y;
    }
    sort(all(bsz));
    for(int i=1;i<=n;i++) allSum[i]=allSum[i-1]+bsz[i];

    for(int i=1;i<=200'000;i++) {
        color[i].push_back(0);
        sort(all(color[i]));
        sum[i].push_back(0);
        for(int j=1;j<sz(color[i]);j++) {
            sum[i].push_back(color[i][j]+sum[i].back());
        }
    }

    for(auto [c, s]:v) {
        ll all=allSum[lower_bound(bsz.begin(), bsz.end(), s)-bsz.begin()-1];
        ll cur=sum[c][lower_bound(color[c].begin(), color[c].end(), s)-color[c].begin()-1];
        cout << all-cur << '\n';
    }
}
