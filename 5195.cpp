#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;

    int i=1, r=0;
    while(n--) {
        int a; cin >> a;
        if(a==i) i++;
        else r++;
    }
    cout<<r;
}
