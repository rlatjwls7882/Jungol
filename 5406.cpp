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
    int t;cin>>t;
    while(t--){
        int n,m;cin>>n>>m;
        vector<vector<int>> cnt(2*n,vi(2));
        vector<string> a(m);
        vector<char> b(m);
        for(int i=0;i<m;i++){
            cin>>a[i]>>b[i];
            b[i]-='0';
            for(int j=0;j<n;j++)a[i][j]-='0';
            for(int j=0;j<n;j++)cnt[j*2+a[i][j]][b[i]]++;
        }

        vector<bool> vis(m);
        for(int i=0;i<m;i++){
            for(int j=0;j<2*n;j++){
                if(cnt[j][0]&&!cnt[j][1]||!cnt[j][0]&&cnt[j][1]){
                    for(int k=0;k<m;k++){
                        if(vis[k]||j/2*2+a[k][j/2]!=j)continue;
                        vis[k]=true;
                        for(int l=0;l<n;l++)cnt[l*2+a[k][l]][b[k]]--;
                    }
                }
            }
        }

        bool chk=true;
        for(int i=0;i<m;i++)if(!vis[i])chk=false;
        if(chk)cout<<"OK\n";
        else cout<<"LIE\n";
    }
}
