#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;
    while(t--){
        ull n,k;cin>>n>>k;
        n= n%4==0 ? ~n : n%4==1 ? 1 : n%4==2 ? ~(n+1) : 0;
        cout<< rotl(n,k%64)<<'\n';
    }
}
