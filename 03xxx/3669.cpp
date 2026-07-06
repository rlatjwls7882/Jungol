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

struct ConvexHull {
    struct point {
        ll x, y, p=0, q=0;
        bool operator<(const point &o) const {
            if(p*o.q!=o.p*q) return p*o.q>o.p*q;
            if(p*p+q*q!=o.p*o.p+o.q*o.q) return p*p+q*q<o.p*o.p+o.q*o.q;
            if(y!=o.y) return y<o.y;
            return x<o.x;
        }
        bool operator==(const point &o) const {
            return x==o.x && y==o.y;
        }
    };
    vector<point> hull;

    ll ccw(point a, point b, point c) {
        point v1 = {b.x-a.x, b.y-a.y};
        point v2 = {c.x-a.x, c.y-a.y};
        return v1.x*v2.y-v2.x*v1.y;
    }

    ll ccw(point a, point b, point c, point d) {
        point v1 = {b.x-a.x, b.y-a.y};
        point v2 = {d.x-c.x, d.y-c.y};
        return v1.x*v2.y-v2.x*v1.y;
    }

    ll dist(point a, point b) {
        return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
    }

    ll triArea(point a, point b, point c) { // area*2
        return a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y;
    }

    ll area() { // area*2
        ll ret=0;
        for(int i=1;i<hull.size()-1;i++) ret += triArea(hull[0], hull[i], hull[i+1]);
        return ret;
    }

    void angleSort(vector<point> &v) {
        for(int i=0;i<v.size();i++) v[i].p=v[i].q=0;
        sort(v.begin(), v.end());

        for(int i=1;i<v.size();i++) {
            v[i].p = v[i].x-v[0].x;
            v[i].q = v[i].y-v[0].y;
        }
        sort(v.begin(), v.end());

        int revIdx=v.size()-1;
        while(revIdx>1 && ccw(v[0], v[revIdx-1], v[revIdx])==0) revIdx--;
        reverse(v.begin()+revIdx, v.end());
    }

    ConvexHull(vector<point> &v) {
        for(int i=0;i<v.size();i++) v[i].p=v[i].q=0;
        sort(v.begin(), v.end());

        for(int i=1;i<v.size();i++) {
            v[i].p = v[i].x-v[0].x;
            v[i].q = v[i].y-v[0].y;
        }
        sort(v.begin(), v.end());

        hull.clear();
        for(point cur:v) {
            while(hull.size()>=2 && ccw(hull[hull.size()-2], hull[hull.size()-1], cur)<=0) hull.pop_back();
            hull.push_back(cur);
        }
    }

    bool inHull(point &p) {
        if(ccw(hull[0], hull[1], p)<0) return false;
        if(ccw(hull[0], hull[hull.size()-1], p)>0) return false;

        int l=1, r=hull.size()-2;
        while(l<r) {
            int m = l+r+1>>1;
            if(ccw(hull[0], hull[m], p)>0) l=m;
            else r=m-1;
        }
        return ccw(hull[l], hull[l+1], p)>=0;
    }

    ll rotatingCalipers() {
        ll ret=0, i=0, j=1;
        while(i<hull.size() && j<hull.size()) {
            ret = max(ret, dist(hull[i], hull[j]));
            if(ccw(hull[i], hull[(i+1)%hull.size()], hull[j], hull[(j+1)%hull.size()])>0) j++;
            else i++;
        }
        return ret;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<ConvexHull::point> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;
    ConvexHull ch(v);
    cout << ch.rotatingCalipers();
}
