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

const int MAX=10000;

int n;
ll sub[MAX], cnt[MAX], res[MAX];
vector<vector<pii>> conn(MAX);

int dfs1(int cur=0) {
    cnt[cur]=1;
    for(auto [nxt, w]:conn[cur]) {
        if(!cnt[nxt]) {
            cnt[cur]+=dfs1(nxt);
            sub[cur]+=sub[nxt]+w*cnt[nxt];
        }
    }
    return cnt[cur];
}

void dfs2(int cur=0) {
    for(auto [nxt, w]:conn[cur]) {
        if(!res[nxt]) {
            res[nxt]=res[cur]+(n-2*cnt[nxt])*w;
            dfs2(nxt);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i=0;i<n-1;i++) {
        int u, v, w; cin >> u >> v >> w;
        conn[u].push_back({v, w});
        conn[v].push_back({u, w});
    }
    dfs1();
    res[0]=sub[0];
    dfs2();
    cout << *min_element(res, res+n);
}
