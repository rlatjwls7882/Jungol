#include<bits/stdc++.h>
using namespace std;

int a[350][350];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i=0;i<n;i++) for(int j=0;j<=i;j++) cin >> a[i][j];
    for(int i=n-2;i>=0;i--) {
        for(int j=0;j<=i;j++) {
            a[i][j]+=max(a[i+1][j], a[i+1][j+1]);
        }
    }
    cout << a[0][0];
}
