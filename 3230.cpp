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

int vis[100'001];
pii prv[100'001];
vector<vector<pair<int, int>>> conn(100'001);

struct element {
    int cur, w, prv, lastW;
    bool operator<(const element e) const {
        return w>e.w;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, a, b; cin >> n >> a >> b;
    for(int i=0;i<n-1;i++) {
        int u, v, w; cin >> u >> v >> w;
        conn[u].push_back({v, w});
        conn[v].push_back({u, w});
    }

    fill(vis, vis+n+1, INF);
    priority_queue<element> pq; pq.push({a, 0, -1, 0});
    while(!pq.empty()) {
        auto [cur, cw, p, lw]=pq.top(); pq.pop();
        if(vis[cur]<=cw) continue;
        vis[cur]=cw;
        prv[cur]={p, lw};
        if(cur==b) break;
        for(auto [nxt, nw]:conn[cur]) {
            if(vis[nxt]>vis[cur]+nw) {
                pq.push({nxt, vis[cur]+nw, cur, nw});
            }
        }
    }

    int ret=INF;
    for(int i=b;i!=-1;i=prv[i].x) {
        ret=min(ret, vis[b]-prv[i].y);
    }
    cout << ret;
}
