#include<bits/stdc++.h>
using namespace std;

int r[5];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    while(n--) {
        int x, y; cin >> x >> y;
        if(!x || !y) r[4]++;
        else if(x>0 && y>0) r[0]++;
        else if(y>0) r[1]++;
        else if(x<0) r[2]++;
        else r[3]++;
    }
    cout << "Q1: " << r[0] << '\n';
    cout << "Q2: " << r[1] << '\n';
    cout << "Q3: " << r[2] << '\n';
    cout << "Q4: " << r[3] << '\n';
    cout << "AXIS: " << r[4] << '\n';
}
