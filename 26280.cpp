#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;

    ordered_set<pair<int, int>> s;
    vector<int> res(n);
    for(int i=0;i<n;i++) {
        int x; cin >> x;
        int left=s.order_of_key({x, -1});
        cout << left << ' ';
        if(left>=m) res[i]=(*s.find_by_order(m-1)).second+1;
        s.insert({x, i});
    }
    cout << '\n';
    for(auto e:res) cout << e << " ";
}
