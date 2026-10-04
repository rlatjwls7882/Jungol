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

int a[200'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,s1,s2;cin>>n>>s1>>s2;
    vector<int> v;
    for(int i=0;i<s1;i++) {
        int a;cin>>a;v.push_back(a);
    }
    for(int i=0;i<s2;i++)cin>>a[i];
    for(int i=s2-1;i>=0;i--)v.push_back(a[i]);

    int id=find(v.begin(),v.end(),0)-v.begin();
    int r=0,m=0;
    for(int i=id-1;i>=0;i--){
        if(m<v[i]){
            m=v[i];
            r++;
        }
    }
    m=0;
    for(int i=id+1;i<=n;i++){
        if(m<v[i]){
            m=v[i];
            r++;
        }
    }
    cout<<r;
}
