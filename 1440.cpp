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
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> T sq(T x) { return x*x; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ld PI = acosl(-1);
const ld EPS = 1e-10;

const int MAX=20;
int par[10001][MAX], dep[10001];
vector<vector<int>> conn(10001);

void dfs(int cur) {
    for(int nxt:conn[cur]) dep[nxt]=dep[cur]+1, dfs(nxt);
}

void build(int n) {
    for(int i=0;i<MAX-1;i++) {
        for(int j=1;j<=n;j++) {
            par[j][i+1]=par[par[j][i]][i];
        }
    }
    int root=1;
    while(par[root][0]) root=par[root][0];
    dfs(root);
}

int find(int u, int d) {
    for(int i=0;d;i++) {
        if(!u) break;
        if(d&1) u=par[u][i];
        d>>=1;
    }
    return u;
}

int LCA(int u, int v) {
    if(dep[u]<dep[v]) swap(u, v);
    u = find(u, dep[u]-dep[v]);
    if(u!=v) {
        for(int i=MAX-1;i>=0;i--) {
            if(par[u][i]!=par[v][i] && par[u][i]) {
                u=par[u][i];
                v=par[v][i];
            }
        }
        u=par[u][0];
    }
    return u;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    rep(n-1) {
        int a, b; cin >> a >> b;
        conn[a].push_back(b);
        par[b][0]=a;
    }
    build(n);
    int a,b;cin>>a>>b;
    cout<<LCA(a,b);
}
