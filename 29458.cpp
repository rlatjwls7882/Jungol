#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n;cin>>n;
    if(n<=2){
        cout<<"2 1 1\n2 1 1";
    }else if(n==3){
        cout<<"3 2 1\n3 2 1";
    }else{
        cout<<"3 "<<n/3*3<<" 2\n";
        cout<<"3 2 1\n";
    }
}
