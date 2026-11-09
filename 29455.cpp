#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int a[9];
int n,m,k,l;
string s[100];
int vis[100][100];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int dp[10'001];

int dfs(int x,int y,char c){
    int ret=1;
    s[x][y]='.';
    for(int i=0;i<4;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=m||s[nx][ny]!=c)continue;
        ret+=dfs(nx,ny,c);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>k>>l;
    for(int i=0;i<l;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>s[i];

    pii st;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j]=='S')st={i,j};
        }
    }

    vector<pii>v;
    memset(vis,-1,sizeof vis);
    queue<pii> q; q.push(st);
    vis[st.first][st.second]=0;
    while(!q.empty()){
        auto [x,y]=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx<0||nx>=n||ny<0||ny>=m||vis[nx][ny]!=-1||s[nx][ny]=='#')continue;
            vis[nx][ny]=vis[x][y]+1;
            q.push({nx,ny});
            if(s[nx][ny]!='.')v.push_back({vis[nx][ny],a[s[nx][ny]-'1']*dfs(nx,ny,s[nx][ny])});
        }
    }

    for(auto [a,b]:v){
        for(int i=k;i-a>=0;i--){
            dp[i]=max(dp[i],dp[i-a]+b);
        }
    }
    cout<<dp[k];
}
