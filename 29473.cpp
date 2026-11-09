#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    map<string,string>mm;
    vector<string> v;
    while(n--){
        string a,b,c;cin>>a>>b>>c;
        if(c=="IN"){
            mm[b]=a;
        }else{
            if(mm[b]!=a)v.push_back(a);
        }
    }

    set<string>s;
    bool chk=true;
    for(auto e:v){
        if(!s.count(e)){
            s.insert(e);
            cout<<e<<'\n';
            chk=false;
        }
    }
    if(chk)cout<<-1;
}
