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

const int MAX=201;
stack<int> stk;
int idx, par[MAX], vis[MAX];
vector<vector<int>> conn(MAX), SCCs;

int DFS(int cur) {
    int rem=par[cur]=++idx;
    stk.push(cur);
    for(int nxt:conn[cur]) {
        if(!par[nxt]) rem=min(rem, DFS(nxt));
        else if(!vis[nxt]) rem=min(rem, par[nxt]);
    }
    if(rem==par[cur]) {
        SCCs.push_back(vector<int>());
        while(true) {
            int top=stk.top(); stk.pop();
            SCCs.back().push_back(top);
            vis[top]=true;
            par[top]=rem;
            if(top==cur) break;
        }
    }
    return rem;
}

int cost[MAX];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=1;i<=n;i++) cin>>cost[i];
    for(int i=1;i<=n;i++) {
        string s; cin >> s;
        for(int j=1;j<=n;j++) {
            if(s[j-1]=='1') conn[i].push_back(j);
        }
    }
    for(int i=1;i<=n;i++) if(!vis[i]) DFS(i);

    int res=0;
    for(auto SCC:SCCs) {
        int mn=INF;
        for(auto e:SCC) mn=min(mn, cost[e]);
        res+=mn;
    }
    cout<<res;
}
