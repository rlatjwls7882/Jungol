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
    while(true){
        int n;cin>>n;
        if(!n)break;
        deque<vector<int>> deq;
        for(int i=0;i<n;i++){
            int a,b;cin>>a>>b;
            if(a!=b)deq.push_back({min(a,b),max(a,b)});
        }

        int cnt=0;
        while(!deq.empty()){
            auto cur=deq.front(); deq.pop_front();
            sort(all(cur));
            if(cur.size()>=2&&cur[0]==cur[1])cur.erase(cur.begin()),cur.erase(cur.begin());
            if(cur.size()>=3&&cur[1]==cur[2])cur.erase(cur.begin()+1),cur.erase(cur.begin()+1);
            if(cur.size()){
                cnt++;
                deq.front().push_back(cur.front());
                cur.erase(cur.begin());
                if(cur.size())deq.push_back(cur);
            }
        }
        cout<<cnt<<'\n';
    }
}
