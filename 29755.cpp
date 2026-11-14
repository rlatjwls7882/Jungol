#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;
    while(t--){
        ll n;cin>>n;

        ll xx=1;
        while(xx<=n/10)xx*=10;

        set<pair<ll,ll>>s;
        for(int i=0;i<=9;i++){
            for(int j=0;j<=9;j++){
                ll x=n-i-j;
                if(x<0||x%2||x/2+i<xx||x/2+j<xx||x/2+i==0||x/2+j==0||(x/2+i)/10!=(x/2+j)/10)continue;
                s.insert({x/2+i,x/2+j});
            }
        }
        if(s.size())cout<<s.size()<<'\n';
        else cout<<"bass\n";
    }
}
