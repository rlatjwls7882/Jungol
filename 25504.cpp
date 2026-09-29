#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>> v;
    while(n--) {
        int s, e; cin >> s >> e;
        v.push_back({s, 1});
        v.push_back({e, -1});
    }
    sort(v.begin(), v.end());

    int cur=0, mx=0;
    for(auto [i, x]:v) {
        cur+=x;
        mx=max(mx, cur);
    }
    cout << mx;
}
