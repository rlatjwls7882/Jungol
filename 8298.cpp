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

int p[1024];
vector<vi> conn(1024);

int find(int x){
    if(x==p[x])return x;
    return p[x]=find(p[x]);
}

bool merge(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y)return false;
    if(x<y)p[y]=x;
    else p[x]=y;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<tuple<int,int,int>>v;
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            int a; cin >> a;
            v.push_back({a,i,j});
        }
    }
    sort(all(v));
    for(int i=0;i<n;i++)p[i]=i;

    for(auto [x,i,j]:v){
        if(merge(i,j)){
            conn[i].push_back(j);
            conn[j].push_back(i);
        }
    }
    for(int i=0;i<n;i++){
        cout<<conn[i].size();
        sort(all(conn[i]));
        for(auto e:conn[i])cout<<' '<<e+1;
        cout<<'\n';
    }
}
