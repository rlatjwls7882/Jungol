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

int a[3][3];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++){
            char c;cin>>c;
            a[i][j]=c-'A'+1;
        }
    }

    int r=0, rr=0;
    for(int i=1;i<=4;i++) {
        for(int j=1;j<=4;j++){
            for(int k=1;k<=4;k++){
                if(i==j||i==k||j==k)continue;
                int c1=0,c2=0,c3=0,i1,i2,i3;
                for(int l=0;l<3;l++)if(a[l][0]==i)c1++,i1=l;
                for(int l=0;l<3;l++)if(a[l][1]==j)c2++,i2=l;
                for(int l=0;l<3;l++)if(a[l][2]==k)c3++,i3=l;
                if(c1!=1||c2!=1||c3!=1||i1==i2||i1==i3||i2==i3)continue;
                r++;
                rr=j;
            }
        }
    }
    cout<<(r!=1?5:rr);
}
