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

struct element {
    ll id, w, pos;
    bool operator<(const element e) const {
        if(w!=e.w) return w>e.w;
        return pos<e.pos;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<pii> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;

    priority_queue<element> pq;
    for(int i=0;i<k && i<n;i++) pq.push({v[i].x, v[i].y, i});

    ll res=0, r=1;
    set<element> rem;
    for(int i=k;i<n;i++) {
        if(rem.empty()) {
            res+=pq.top().id*r++;
            rem.insert(pq.top()); pq.pop();
            while(sz(pq) && pq.top().w==(*rem.begin()).w) {
                res+=pq.top().id*r++;
                rem.insert(pq.top()); pq.pop();
            }
        }
        auto cur=*rem.begin();
        rem.erase(rem.begin());
        pq.push({v[i].x, cur.w+v[i].y, cur.pos});
    }
    while(!pq.empty()) {
        auto [id, w, pos]=pq.top(); pq.pop();
        res+=id*r++;
    }
    cout << res;
}
