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

int vis[2'000'000], d[13], pw[13];

int val(string s) {
    int ret=0;
    for(int i=sz(s)-1;i>=0;i--) ret=ret*3+s[i]-'A';
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    memset(vis, -1, sizeof vis);
    pw[0]=1;
    for(int i=1;i<n;i++) pw[i]=pw[i-1]*3;

    queue<int> qu;
    for(int i=0;i<=n;i++) {
        for(int j=0;i+j<=n;j++) {
            int k=n-i-j;
            int v=0;
            for(int l=0;l<k;l++) v=v*3+2;
            for(int l=0;l<j;l++) v=v*3+1;
            for(int l=0;l<i;l++) v=v*3;
            qu.push(v);
            vis[v]=0;
        }
    }

    while(!qu.empty()) {
        int cur=qu.front(); qu.pop();
        int tmp=cur;
        for(int i=0;i<n;i++) {
            d[i]=tmp%3;
            tmp/=3;
        }
        int rem=0, rev=0;
        for(int i=0;i<n;i++) {
            rem+=d[i]*pw[i];
            rev=rev*3+d[i];
            int nxt=cur-rem+rev;
            if(vis[nxt]==-1) {
                vis[nxt]=vis[cur]+1;
                qu.push(nxt);
            }
        }
    }
    while(q--) {
        string s; cin >> s;
        cout << vis[val(s)] << '\n';
    }
}
