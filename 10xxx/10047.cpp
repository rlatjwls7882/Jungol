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
#define compress(x) sort(all(x)), x.erase(unique(all(x)), x.end())

typedef long long ll;
typedef long double ld;
typedef __int128 i128;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> T sq(T x) { return x*x; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const ld PI = acosl(-1);
const ld EPS = 1e-10;

mt19937 rd((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rnd_int(0, 0); // rnd_int(rd)
uniform_real_distribution<double> rnd_real(0, 1); // rnd_real(rd)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;cin>>T;
    for(int tc=1;tc<=T;tc++){
        int n;cin>>n;
        ll sx=0,sy=0,sz=0,svx=0,svy=0,svz=0;
        for(int i=0;i<n;i++) {
            ll x,y,z,vx,vy,vz;cin>>x>>y>>z>>vx>>vy>>vz;
            sx+=x;
            sy+=y;
            sz+=z;
            svx+=vx;
            svy+=vy;
            svz+=vz;
        }
        ld vv=sq(svx)+sq(svy)+sq(svz);
        ld t=0;
        if(vv)t=max(t,-(sx*svx+sy*svy+sz*svz)/vv);

        ld x=sx+svx*t;
        ld y=sy+svy*t;
        ld z=sz+svz*t;
        cout<<setprecision(5)<<fixed<<"Case #"<<tc<<": "<<sqrt(sq(x)+sq(y)+sq(z))/n<<" "<<t<<'\n';
    }
}
