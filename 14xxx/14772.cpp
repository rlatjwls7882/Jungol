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

const int MAX = 100'001;

char t;
bool val[MAX];
int dp[MAX][2];
vector<vector<int>> child(MAX);

void dfs(int cur=1, int dep=1) {
    if(child[cur].empty()) {
        if(val[cur]) {
            dp[cur][0]=1;
            dp[cur][1]=0;
        } else {
            dp[cur][0]=0;
            dp[cur][1]=1;
        }
        return;
    }

    int zero=0, one=0;
    for(int nxt:child[cur]) {
        dfs(nxt, dep+1);
        zero+=dp[nxt][0];
        one+=dp[nxt][1];
    }

    if(dep%2 && t=='O' || dep%2==0 && t=='A') {
        dp[cur][0]=zero;
        for(int nxt:child[cur]) dp[cur][1]=min(dp[cur][1], dp[nxt][1]);
    } else {
        for(int nxt:child[cur]) dp[cur][0]=min(dp[cur][0], dp[nxt][0]);
        dp[cur][1]=one;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n >> t;
    int node=1;
    vector<int> level = {1};
    for(int i=1;i<=n;i++) {
        vector<int> nxtL;
        for(int cur:level) {
            string s; cin >> s;
            if(s=="F" || s=="T") {
                val[cur]=s=="T";
            } else {
                int v=stoi(s);
                while(v--) {
                    node++;
                    child[cur].push_back(node);
                    nxtL.push_back(node);
                }
            }
        }
        level=nxtL;
    }
    fill(&dp[0][0], &dp[MAX][0], INF);
    dfs();
    cout << max(dp[1][0], dp[1][1]);
}
