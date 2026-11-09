#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n,k;cin>>n>>k;
    cout<<(n<=2*k||n>3*k+2?"SS":"DY");
}
