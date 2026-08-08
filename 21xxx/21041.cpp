#include<bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    bool a=0,g=0,c=0,u=0;
    for(char ch:s) {
        if(ch=='A')a=1;
        else if(ch=='G')g=1;
        else if(ch=='C')c=1;
        else u=1;
    }
    int r=0;
    if(a)r++;
    if(g)r+=2;
    if(c)r+=4;
    if(u)r+=8;
    cout<<r;
}
