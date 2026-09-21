#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int d,h,m,s,e;cin>>d>>h>>m>>s>>e;
    s=((d*24+h)*60+m)*60+s-e;
    m=s/60;
    s%=60;
    h=m/60;
    m%=60;
    d=h/24;
    h%=24;
    cout<<d<<' '<<h<<' '<<m<<' '<<s;
}
