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

int a[4][4];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) cin >> a[i][j];
    while(n--) {
        int dir, x, y, c; cin >> dir >> x >> y >> c;
        vector<int> stk;
        if(dir==1) {
            for(int j=0;j<4;j++) {
                for(int i=0;i<4;i++) {
                    if(!a[i][j]) continue;
                    stk.push_back(a[i][j]);
                    a[i][j]=0;
                    while(stk.size()>=2 && stk.back()==stk[sz(stk)-2]) stk.pop_back(), stk.back()*=2;
                }
                for(int i=0;i<stk.size();i++) {
                    a[i][j]=stk[i];
                }
                stk.clear();
            }
        } else if(dir==2) {
            for(int i=0;i<4;i++) {
                for(int j=0;j<4;j++) {
                    if(!a[i][j]) continue;
                    stk.push_back(a[i][j]);
                    a[i][j]=0;
                    while(stk.size()>=2 && stk.back()==stk[sz(stk)-2]) stk.pop_back(), stk.back()*=2;
                }
                for(int j=0;j<stk.size();j++) {
                    a[i][j]=stk[j];
                }
                stk.clear();
            }
        } else if(dir==3) {
            for(int j=0;j<4;j++) {
                for(int i=3;i>=0;i--) {
                    if(!a[i][j]) continue;
                    stk.push_back(a[i][j]);
                    a[i][j]=0;
                    while(stk.size()>=2 && stk.back()==stk[sz(stk)-2]) stk.pop_back(), stk.back()*=2;
                }
                for(int i=0;i<stk.size();i++) {
                    a[3-i][j]=stk[i];
                }
                stk.clear();
            }
        } else {
            for(int i=0;i<4;i++) {
                for(int j=3;j>=0;j--) {
                    if(!a[i][j]) continue;
                    stk.push_back(a[i][j]);
                    a[i][j]=0;
                    while(stk.size()>=2 && stk.back()==stk[sz(stk)-2]) stk.pop_back(), stk.back()*=2;
                }
                for(int j=0;j<stk.size();j++) {
                    a[i][3-j]=stk[j];
                }
                stk.clear();
            }
        }
        a[x-1][y-1]=c;
    }
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) cout << a[i][j] << ' ';
        cout << '\n';
    }
}