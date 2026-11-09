#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;string s;cin>>n>>s;

    string res="Safe!";
    for(int i=1;i*2<=n;i++){
        if(s.substr(n-i,i)==s.substr(n-i*2,i)){
            res=s.substr(0,n-i);
        }
    }
    cout<<res;
}
