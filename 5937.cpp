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

int res=INF;
int n, a[11];
bool vis[11];
vector<vector<int>> conn(11);

void back(int depth=0, int sum1=0) {
    if(depth==0) {
        for(int i=1;i<=n;i++) {
            vis[i]=true;
            back(depth+1, a[i]);
            vis[i]=false;
        }
        return;
    }
    for(int i=1;i<=n;i++) {
        if(!vis[i]) {
            int sum2=0;
            vector<int> mem;
            queue<int> q; q.push(i);
            vis[i]=true;
            while(!q.empty()) {
                int cur=q.front(); q.pop();
                mem.push_back(cur);
                sum2+=a[cur];
                for(int next:conn[cur]) {
                    if(!vis[next]) {
                        vis[next]=true;
                        q.push(next);
                    }
                }
            }
            if(depth+sz(mem)==n) res=min(res, abs(sum1-sum2));
            for(auto e:mem) vis[e]=false;
            break;
        }
    }
    vector<int> canGo;
    for(int i=1;i<=n;i++) {
        if(vis[i]) {
            for(int next:conn[i]) {
                if(!vis[next]) {
                    canGo.push_back(next);
                }
            }
        }
    }
    compress(canGo);
    for(auto e:canGo) {
        vis[e]=true;
        back(depth+1, sum1+a[e]);
        vis[e]=false;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) {
        int cnt; cin >> cnt;
        while(cnt--) {
            int j; cin >> j;
            conn[i].push_back(j);
        }
    }
    back();
    cout << (res==INF ? -1 : res);
}