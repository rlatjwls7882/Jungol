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

vi makeTable(vi s) {
    vi table(sz(s));
    for(int idx=0, i=1;i<sz(s);i++) {
        while(idx && s[idx]!=s[i]) idx=table[idx-1];
        if(s[idx]==s[i]) table[i]=++idx;
    }
    return table;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vi t(n);
    for(int i=n-1;i>=0;i--) cin >> t[i];
    t = makeTable(t);

    int k=INF, p=INF;
    for(int i=0;i<n;i++) {
        int a=n-i-1, b=i+1-t[i];
        if(a+b<k+p || a+b==k+p && b<p) {
            k=a;
            p=b;
        }
    }
    cout << k << ' ' << p;
}
