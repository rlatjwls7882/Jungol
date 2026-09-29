#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> conn(10001);

bool chk(int s, int e, int k) {
    queue<int> q; q.push(s);
    vector<bool> vis(10001);
    vis[s]=true;
    while(!q.empty()) {
        int cur=q.front(); q.pop();
        if(cur==e) return true;
        for(auto [nxt, w]:conn[cur]) {
            if(!vis[nxt] && w>=k) {
                q.push(nxt);
                vis[nxt]=true;
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        conn[a].push_back({b, c});
        conn[b].push_back({a, c});
    }
    int a, b; cin >> a >> b;

    int l=1, r=1'000'000'000;
    while(l<r) {
        int m=l+r+1>>1;
        if(chk(a, b, m)) l=m;
        else r=m-1;
    }
    cout << l;
}
