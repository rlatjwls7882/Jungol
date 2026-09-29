#include<bits/stdc++.h>
using namespace std;

int cnt[3];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    while(n--) {
        string s; cin >> s;
        int cur=0;
        for(char c:s) cur+=c-'0';
        cnt[cur%3]++;
    }
    for(auto e:cnt) cout << e << ' ';
}
