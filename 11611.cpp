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

int cnt, n, maxDep;
string s[100];
bool vis[100][100];
int par[10000];
int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, -1, 1, -1, 1};
int ndx[] = {2, 2, 1, 1, -1, -1, -2, -2};
int ndy[] = {1, -1, 2, -2, 2, -2, 1, -1};
vector<vector<int>> conn(10000), deps(10000);

void dfs(int cx, int cy, int dep) {
    maxDep = max(maxDep, dep);
    deps[dep].push_back(cx*n+cy);
    cnt--;
    vis[cx][cy]=true;
    for(int nxt:conn[cx*n+cy]) {
        int nx=nxt/n;
        int ny=nxt%n;
        if(!vis[nx][ny]) {
            par[nx*n+ny]=cx*n+cy;
            dfs(nx, ny, dep+1);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    char k; cin >> n >> k;
    for(int i=0;i<n;i++) {
        cin >> s[i];
        for(int j=0;j<n;j++) cnt+=s[i][j]==k;
    }
    pii last;
    for(int cx=0;cx<n;cx++) {
        for(int cy=0;cy<n;cy++) {
            if(s[cx][cy]==k) {
                last={cx, cy};
                if(k=='K') {
                    for(int i=0;i<8;i++) {
                        int nx=cx+dx[i];
                        int ny=cy+dy[i];
                        if(nx<0 || nx>=n || ny<0 || ny>=n || s[nx][ny]!=k) continue;
                        conn[cx*n+cy].push_back(nx*n+ny);
                    }
                } else if(k=='N') {
                    for(int i=0;i<8;i++) {
                        int nx=cx+ndx[i];
                        int ny=cy+ndy[i];
                        if(nx<0 || nx>=n || ny<0 || ny>=n || s[nx][ny]!=k) continue;
                        conn[cx*n+cy].push_back(nx*n+ny);
                    }
                } else if(k=='R') {
                    for(int i=0;i<4;i++) {
                        for(int j=1;;j++) {
                            int nx=cx+dx[i]*j;
                            int ny=cy+dy[i]*j;
                            if(nx<0 || nx>=n || ny<0 || ny>=n) break;
                            if(s[nx][ny]==k) {
                                conn[cx*n+cy].push_back(nx*n+ny);
                                break;
                            }
                        }
                    }
                } else if(k=='B') {
                    for(int i=4;i<8;i++) {
                        for(int j=1;;j++) {
                            int nx=cx+dx[i]*j;
                            int ny=cy+dy[i]*j;
                            if(nx<0 || nx>=n || ny<0 || ny>=n) break;
                            if(s[nx][ny]==k) {
                                conn[cx*n+cy].push_back(nx*n+ny);
                                break;
                            }
                        }
                    }
                } else {
                    for(int i=0;i<8;i++) {
                        for(int j=1;;j++) {
                            int nx=cx+dx[i]*j;
                            int ny=cy+dy[i]*j;
                            if(nx<0 || nx>=n || ny<0 || ny>=n) break;
                            if(s[nx][ny]==k) {
                                conn[cx*n+cy].push_back(nx*n+ny);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    dfs(last.x, last.y, 0);
    if(cnt==0) {
        cout << "YES\n";
        for(int i=maxDep;i>0;i--) {
            for(auto e:deps[i]) {
                int cx=e/n, cy=e%n;
                int nx=par[e]/n, ny=par[e]%n;
                cout << cx+1 << ' ' << cy+1 << ' ' << nx+1 << ' ' << ny+1 << '\n';
            }
        }
        return 0;
    }
    cout << "NO";
}
