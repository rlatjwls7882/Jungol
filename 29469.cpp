#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll pe[200'001], pd[200'001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,h;cin>>n>>h;
    for(int i=1;i<=n;i++){
        cin>>pe[i]>>pd[i];
        pe[i]+=pe[i-1];
        pd[i]+=pd[i-1];
    }

    ll res=0,l=0,r=0;
    while(l<n){
        while(r<n&&pd[r+1]-pd[l]<=h)r++;
        res=max(res,pe[r]-pe[l]);
        l++;
    }
    cout<<res;
}
