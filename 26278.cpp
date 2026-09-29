#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll M=1e9+7;
ll dp[100'001][8];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    dp[0][0]=1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<8;j++) {
            if(i>=1) dp[i][j|1]+=dp[i-1][j];
            if(i>=2) dp[i][j|2]+=dp[i-2][j];
            if(i>=3) dp[i][j|4]+=dp[i-3][j];
            dp[i][j]%=M;
        }
    }
    cout << dp[n][7];
}
