#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int a[200'001],b[200'001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(n==1)return!(cout<<a[1]);

    int res=-1;
    for(int aa=0;aa<=1;aa++){
        for(int bb=0;bb<=1;bb++){
            b[0]=aa;
            b[1]=bb;

            int cnt=aa+bb;
            bool chk=true;
            for(int i=2;i<=n;i++){
                b[i]=a[i-1]-b[i-1]-b[i-2];
                if(b[i]<0||b[i]>1){
                    chk=false;
                    break;
                }
                cnt+=b[i];
            }
            if(chk&&0<=a[n]-b[n]-b[n-1]&&a[n]-b[n]-b[n-1]<=1)res=max(res,cnt+a[n]-b[n]-b[n-1]);
        }
    }
    cout<<res;
}
