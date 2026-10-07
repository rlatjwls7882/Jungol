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

ll c[40];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n,m;cin>>n>>m;
    for(int i=0;i<n;i++)cin>>c[i];

    vector<ll> a={0},b={0};
    for(int i=0;i<n/2;i++){
        int k=a.size();
        for(int j=0;j<k;j++)a.push_back(a[j]+c[i]);
    }
    for(int i=n/2;i<n;i++){
        int k=b.size();
        for(int j=0;j<k;j++)b.push_back(b[j]+c[i]);
    }
    sort(all(a));sort(all(b));

    ll cnt=0;
    if(m==0)cnt--;
    int l=0,r=b.size()-1;
    while(l<a.size()&&r>=0){
        ll s=a[l]+b[r];
        if(s<m)l++;
        else if(s>m)r--;
        else {
            ll aa=a[l],bb=b[r];
            ll L=0,R=0;
            while(l<a.size()&&a[l]==aa)L++,l++;
            while(r>=0&&b[r]==bb)R++,r--;
            cnt+=L*R;
        }
    }
    cout<<cnt;
}
