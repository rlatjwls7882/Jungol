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

const int MAX = 1e5+1;

bool vis1[MAX], vis2[MAX];
vvi conn1(MAX), conn2(MAX);

int dfs1(int cur) {
    vis1[cur]=true;
    int ret=1;
    for(int nxt:conn1[cur]) {
        if(!vis1[nxt]) ret+=dfs1(nxt);
    }
    return ret;
}

int dfs2(int cur) {
    vis2[cur]=true;
    int ret=1;
    for(int nxt:conn2[cur]) {
        if(!vis2[nxt]) ret+=dfs2(nxt);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, x; cin >> n >> m >> x;
    while(m--) {
        int a, b; cin >> a >> b;
        conn1[a].push_back(b);
        conn2[b].push_back(a);
    }
    cout << dfs2(x) << ' ' << n-dfs1(x)+1;
}
