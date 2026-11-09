#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,m;cin>>n>>m;
    n=1<<n;m=1<<m;
    int sum=n*m;
    while(n>1||m>1){
        n=n+1>>1;
        m=m+1>>1;
        sum+=n*m;
    }
    cout<<sum*3;
}
