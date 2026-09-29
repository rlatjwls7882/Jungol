#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=0x3f3f3f3f;
int s1, s2, s3;
vector<vector<pair<int, int>>> conn(1001);
int prv1[1001], prv2[1001], prv3[1001];
ll cost1[1001], cost2[1001], cost3[1001];

void dijk() {
    priority_queue<pair<ll, ll>> pq; pq.push({0, s1});
    fill(cost1, cost1+1001, INF);
    cost1[s1]=0;
    while(!pq.empty()) {
        auto [mw, cur]=pq.top(); pq.pop();
        if(cost1[cur]!=-mw) continue;
        for(auto [nxt, w]:conn[cur]) {
            if(cost1[nxt]>cost1[cur]+w) {
                pq.push({-cost1[cur]-w, nxt});
                cost1[nxt]=cost1[cur]+w;
                prv1[nxt]=cur;
            }
        }
    }
    pq.push({0, s2});
    fill(cost2, cost2+1001, INF);
    cost2[s2]=0;
    while(!pq.empty()) {
        auto [mw, cur]=pq.top(); pq.pop();
        if(cost2[cur]!=-mw) continue;
        for(auto [nxt, w]:conn[cur]) {
            if(cost2[nxt]>cost2[cur]+w) {
                pq.push({-cost2[cur]-w, nxt});
                cost2[nxt]=cost2[cur]+w;
                prv2[nxt]=cur;
            }
        }
    }
    pq.push({0, s3});
    fill(cost3, cost3+1001, INF);
    cost3[s3]=0;
    while(!pq.empty()) {
        auto [mw, cur]=pq.top(); pq.pop();
        if(cost3[cur]!=-mw) continue;
        for(auto [nxt, w]:conn[cur]) {
            if(cost3[nxt]>cost3[cur]+w) {
                pq.push({-cost3[cur]-w, nxt});
                cost3[nxt]=cost3[cur]+w;
                prv3[nxt]=cur;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        conn[a].push_back({b, c});
        conn[b].push_back({a, c});
    }
    cin >> s1 >> s2 >> s3;
    dijk();

    ll mn=INF, idx;
    for(int i=1;i<=n;i++) {
        if(mn>cost1[i]+cost2[i]+cost3[i]) {
            mn=cost1[i]+cost2[i]+cost3[i];
            idx=i;
        }
    }
    cout << mn << '\n' << idx;

    vector<int> r1, r2, r3;
    for(int i=idx;;i=prv1[i]) {
        r1.push_back(i);
        if(i==s1) break;
    }
    for(int i=idx;;i=prv2[i]) {
        r2.push_back(i);
        if(i==s2) break;
    }
    for(int i=idx;;i=prv3[i]) {
        r3.push_back(i);
        if(i==s3) break;
    }
    reverse(r1.begin(), r1.end());
    reverse(r2.begin(), r2.end());
    reverse(r3.begin(), r3.end());
    cout << '\n' << r1.size() << '\n';
    for(auto e:r1) cout << e << ' ';
    cout << '\n' << r2.size() << '\n';
    for(auto e:r2) cout << e << ' ';
    cout << '\n' << r3.size() << '\n';
    for(auto e:r3) cout << e << ' ';
}
