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

int h,w,n;
int dx[]={1,-1,0,0};
int dy[]={0,0,-1,1};
bool vis[20][20];
vector<vector<vector<int>>> block(20,vector<vector<int>>(20,vector<int>(4)));

void dfs(int x,int y){
    vis[x][y]=true;
    for(int i=0;i<4;i++){
        if(block[x][y][i])continue;
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<0||nx>=h||ny<0||ny>=w||vis[nx][ny])continue;
        dfs(nx,ny);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>w>>h>>n;
    while(n--){
        int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        for(int i=x1;i<x2;i++){
            block[i][y1][2]=block[i][y2-1][3]=1;
            if(y1-1>=0)block[i][y1-1][3]=1;
            if(y2<w)block[i][y2][2]=1;
        }
        for(int i=y1;i<y2;i++){
            block[x1][i][1]=block[x2-1][i][0]=1;
            if(x1-1>=0)block[x1-1][i][0]=1;
            if(x2<h)block[x2][i][1]=1;
        }
    }
    int cnt=0;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(!vis[i][j]){
                dfs(i,j);
                cnt++;
            }
        }
    }
    cout<<cnt;
}
