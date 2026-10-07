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

int w,h,a[1000][1000];
int vis1[1000][1000],vis2[1000][1000];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

void bfs1(int cx, int cy){
    memset(vis1,-1,sizeof vis1);
    queue<pair<int,int>>q;q.push({cx,cy});
    vis1[cx][cy]=0;
    while(!q.empty()){
        auto [cx,cy]=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nx=cx+dx[i],ny=cy+dy[i];
            if(nx<0||nx>=h||ny<0||ny>=w||vis1[nx][ny]!=-1||a[nx][ny]==1)continue;
            vis1[nx][ny]=vis1[cx][cy]+1;
            q.push({nx,ny});
        }
    }
}

void bfs2(int cx, int cy){
    memset(vis2,-1,sizeof vis2);
    queue<pair<int,int>>q;q.push({cx,cy});
    vis2[cx][cy]=0;
    while(!q.empty()){
        auto [cx,cy]=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nx=cx+dx[i],ny=cy+dy[i];
            if(nx<0||nx>=h||ny<0||ny>=w||vis2[nx][ny]!=-1||a[nx][ny]==1)continue;
            vis2[nx][ny]=vis2[cx][cy]+1;
            q.push({nx,ny});
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>w>>h;
    int x1,y1,x2,y2;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cin>>a[i][j];
            if(a[i][j]==2)x1=i,y1=j;
            else if(a[i][j]==3)x2=i,y2=j;
        }
    }
    bfs1(x1,y1);
    bfs2(x2,y2);

    int r=INT_MAX;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(a[i][j]==4&&vis1[i][j]!=-1&&vis2[i][j]!=-1){
                r=min(r,vis1[i][j]+vis2[i][j]);
            }
        }
    }
    cout<<r;
}
