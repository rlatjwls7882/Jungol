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
    int n; string s; cin >> n >> s;

    vector<int> len,edge;
    int cur=0, i=0;
    if(s[0]=='1'){
        while(i+1<n&&s[i+1]=='1')i++;
        edge.push_back(i+1);
    }
    i++;
    for(;i<n;i++){
        auto e=s[i];
        if(e=='1')cur++;
        else {
            if(cur)len.push_back(cur);
            cur=0;
        }
    }
    if(cur)edge.push_back(cur);
    if(len.empty()&&edge.empty()) return !(cout<<0);
    sort(all(len));

    int mn=INF,cnt=0;
    if(len.size())mn=(len[0]-1)/2;
    for(auto e:edge)mn=min(mn,e-1);
    mn=mn*2+1;

    for(auto e:len)cnt+=(e+mn-1)/mn;
    for(auto e:edge)cnt+=(e+mn-1)/mn;
    cout<<cnt;
}
