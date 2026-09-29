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

int b[250][250];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> b[i][j];

    int tot=0;
    for(int i=0;i<(n+m)/2;i++) {
        int x1, y1, x2, y2;
        if(i<n) x1=i, y1=0;
        else x1=n-1, y1=i-n+1;
        int i2=(n+m-2-i);
        if(i2<n) x2=i2, y2=0;
        else x2=n-1, y2=i2-n+1;
        vector<int> v;
        if(x2!=x1 || y2!=y1) {
            while(0<=x2 && x2<n && 0<=y2 && y2<m) {
                v.push_back(b[x2][y2]);
                x2--; y2++;
            }
        }
        while(0<=x1 && x1<n && 0<=y1 && y1<m) {
            v.push_back(b[x1][y1]);
            x1--; y1++;
        }
        sort(all(v));

        int len=0, res=INF;
        for(int i=0;i<v.size();i++) {
            if(i==0 || v[i]!=v[i-1]) len=1;
            else len++;
            res=min(res, sz(v)-len);
        }
        tot+=res;
    }
    cout << tot;
}
