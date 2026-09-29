#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int x1,y1,x2,y2,x3,y3,x4,y4;cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    cout << (min(x2,x4)-max(x1,x3))*(min(y2,y4)-max(y1,y3));
}
