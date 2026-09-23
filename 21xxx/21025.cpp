#include<bits/stdc++.h>
using namespace std;

int a[100];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,k;cin>>n>>k;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=a[0];;i--)  {
        bool chk=true;
        for(int j=0;j<n;j++) {
            if(i+j*k>a[j]) {
                chk=false;
            }
        }
        if(chk) {
            for(int j=0;j<n;j++) cout << i+j*k<<' ';
            return 0;
        }
    }
}
