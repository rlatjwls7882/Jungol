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

int A[2500], B[7500];
bool vis[7500];
vector<vector<int>> conn(2500);

bool dfs(int cur) {
    vis[cur]=true;
    for(int nxt:conn[cur]) {
        if(B[nxt]==-1 || !vis[B[nxt]] && dfs(B[nxt])) {
            B[nxt]=cur;
            A[cur]=nxt;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pll> v(n);
    vector<ll> lst;
    for(int i=0;i<n;i++) {
        cin >> v[i].x >> v[i].y;
        lst.push_back(v[i].x+v[i].y);
        lst.push_back(v[i].x-v[i].y);
        lst.push_back(v[i].x*v[i].y);
    }
    compress(lst);
    for(int i=0;i<n;i++) {
        conn[i].push_back(lower_bound(lst.begin(), lst.end(), v[i].x+v[i].y)-lst.begin());
        conn[i].push_back(lower_bound(lst.begin(), lst.end(), v[i].x-v[i].y)-lst.begin());
        conn[i].push_back(lower_bound(lst.begin(), lst.end(), v[i].x*v[i].y)-lst.begin());
    }

    memset(B, -1, sizeof B);
    for(int i=0;i<n;i++) {
        memset(vis, 0, sizeof vis);
        if(!dfs(i)) return !(cout << "impossible");
    }
    for(int i=0;i<n;i++) {
        ll res=lst[A[i]];
        if(res==v[i].x+v[i].y) cout << v[i].x << " + " << v[i].y << " = " << res << '\n';
        else if(res==v[i].x-v[i].y) cout << v[i].x << " - " << v[i].y << " = " << res << '\n';
        else cout << v[i].x << " * " << v[i].y << " = " << res << '\n';
    }
}
