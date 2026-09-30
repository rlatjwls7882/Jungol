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

int ma[102][102],dist[102][102];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

struct element {
    int a,b,co;
    bool operator<(const element e) const {
        return co>e.co;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,a,b;cin>>n>>a>>b;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>ma[i][j];

    fill(&dist[0][0],&dist[n+2][0],LINF);
    priority_queue<element>pq;pq.push({a,b,0});
    while(!pq.empty()){
        auto [a,b,c]=pq.top();pq.pop();
        if(c>=dist[a][b])continue;
        dist[a][b]=c;
        if(a==0||a==n+1||b==0||b==n+1)return!(cout<<c);
        for(int i=0;i<4;i++){
            int na=a+dx[i],nb=b+dy[i];
            if(na<0||na>n+1||nb<0||nb>n+1)continue;
            int nc=c + (ma[a][b]>ma[na][nb] ? sq(ma[a][b]-ma[na][nb]) : ma[na][nb]-ma[a][b]);
            if(nc<dist[na][nb])pq.push({na,nb,nc});
        }
    }
}
