#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>> v(n);
    for(int i=0;i<n;i++) cin >> v[i].x >> v[i].y;
    sort(v.begin(), v.end(), greater<pair<int,int>>());

    ll res=0, idx=0;
    priority_queue<int> pq;
    for(int i=v[0].x;i>=1;i--) {
        while(idx<n && v[idx].x==i) pq.push(v[idx++].y);
        if(pq.size()) {
            res+=pq.top();
            pq.pop();
        }
    }
    cout << res;
}
