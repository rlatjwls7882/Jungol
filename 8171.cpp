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
    int n,k;cin>>n>>k;
    priority_queue<pll>pq;
    for(int i=0;i<k;i++){
        int a;cin>>a;
        pq.push({-a,i});
    }

    int idx=k;
    vector<vector<int>> vv;
    while(idx<n){
        auto cur=pq.top();pq.pop();
        vector<int> v;
        v.push_back(cur.y);
        int a;cin>>a;idx++;
        pq.push({cur.x-a,cur.y});
        while(idx<n&&cur.x==pq.top().x){
            auto nxt=pq.top();pq.pop();
            int a;cin>>a;idx++;
            pq.push({nxt.x-a,nxt.y});
            v.push_back(nxt.y);
        }
        vv.push_back(v);
    }

    vector<bool> chk(k);
    auto cur=pq.top();pq.pop();
    cout<<-cur.x<<'\n';
    chk[cur.y]=1;
    while(!pq.empty()&&pq.top().x==cur.x){
        chk[pq.top().y]=1;
        pq.pop();
    }

    reverse(all(vv));
    for(auto &v:vv){
        bool cur=false;
        for(auto e:v)cur|=chk[e];
        if(cur)for(auto e:v)chk[e]=1;
    }
    for(auto e:chk)cout<<e;
}
