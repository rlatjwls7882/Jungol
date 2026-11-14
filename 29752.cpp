#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[1'000'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,a,b;cin>>n>>a>>b;

    ll r=0;
    for(int i=0;i<n;i++){
        cin>>A[i];
        if(i)r+=max(0,A[i-1]-A[i]);
    }
    cout<<r*min(a,b);
}
