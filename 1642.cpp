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

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
string s[10], ns[10];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>s[i];
        ns[i]=s[i];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j]=='X'){
                int cnt=0;
                for(int k=0;k<4;k++){
                    int nx=i+dx[k];
                    int ny=j+dy[k];
                    if(nx<0||nx>=n||ny<0||ny>=m||s[nx][ny]=='.')cnt++;
                }
                if(cnt>=3)ns[i][j]='.';
            }
        }
    }
    int lx=n-1,rx=0,ly=m-1,ry=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(ns[i][j]=='X') {
                lx=min(lx,i);
                rx=max(rx,i);
                ly=min(ly,j);
                ry=max(ry,j);
            }
        }
    }
    for(int i=lx;i<=rx;i++){
        for(int j=ly;j<=ry;j++){
            cout<<ns[i][j];
        }
        cout<<'\n';
    }
}
