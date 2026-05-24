#include<bits/stdc++.h>
using namespace std;

int cnt[4];
string x[4] = {"MUPC", "MJUPC", "MPC", "MJPC"};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;

    int mx=0;
    while(n--) {
        string s; cin >> s;

        int idx=0;
        for(int i=1;i<4;i++) {
            if(s==x[i]) idx=i;
        }
        mx = max(mx, ++cnt[idx]);
    }

    int idx=-1;
    for(int i=0;i<4;i++) {
        if(mx==cnt[i]) {
            if(idx!=-1) return !(cout << "REVOTE");
            idx=i;
        }
    }
    cout << x[idx];
}
