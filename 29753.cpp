#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a[1'000'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n,k;cin>>n>>k;

    ll res=0,sz=0,sum=0;
    deque<pair<int,int>> deq;
    for(int i=0;i<n;i++){
        cin>>a[i];
        sz++;
        sum+=a[i];
        while(deq.size()&&deq.back().second<=a[i])deq.pop_back();
        deq.push_back({i,a[i]});

        while(deq.front().second*sz-sum>k){
            int pop=i-sz+1;
            if(deq.front().first==pop)deq.pop_front();
            sz--;
            sum-=a[pop];
        }
        res=max(res,deq.front().second*sz);
    }
    cout<<res;
}
