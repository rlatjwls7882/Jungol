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

int vis[10000];
pii p[10000];
vi buc[31][31];
int dx[] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int h, f; cin >> h >> f;
    queue<int> q;
    for(int i=0;i<f;i++) {
        cin >> p[i].x >> p[i].y;
        buc[p[i].x/1000][p[i].y/1000].push_back(i);
        if(p[i].y<=1000) {
            q.push(i);
            vis[i]=1;
        }
    }

    while(!q.empty()) {
        int cur=q.front(); q.pop();
        if(h-p[cur].y<=1000) return !(cout << vis[cur]);
        for(int i=0;i<9;i++) {
            int nx=p[cur].x/1000+dx[i];
            int ny=p[cur].y/1000+dy[i];
            if(nx<0 || nx>30 || ny<0 || ny>30) continue;
            for(int nxt:buc[nx][ny]) {
                if(sq(p[cur].x-p[nxt].x)+sq(p[cur].y-p[nxt].y)<=1'000'000 && !vis[nxt]) {
                    vis[nxt]=vis[cur]+1;
                    q.push(nxt);
                }
            }
        }
    }
}
