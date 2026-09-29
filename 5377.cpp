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

int res[50];
string dir[50];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0;i<n;i++) cin >> dir[i] >> v[i].x >> v[i].y;

    for(int i=0;i<n;i++) res[i]=INF;
    rep(n) {
        int idx, c=INF;
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if(dir[i]=="E" && dir[j]=="N" && v[i].x<v[j].x && v[i].y>v[j].y) {
                    int a=v[j].x-v[i].x;
                    int b=v[i].y-v[j].y;
                    if(a<b && res[j]!=INF || a>b && res[i]!=INF) continue;
                    if(a<b && b<c && res[i]>=a) idx=j, c=b;
                    else if(b<a && a<c && res[j]>=b) idx=i, c=a;
                }
            }
        }
        if(c==INF) break;
        res[idx]=c;
    }
    for(int i=0;i<n;i++) {
        if(res[i]==INF) cout << "Infinity\n";
        else cout << res[i] << '\n';
    }
}