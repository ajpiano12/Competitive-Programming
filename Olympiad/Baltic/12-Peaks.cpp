/*

Logic:
The first step is to do a dfs to find the flat areas
and then store the ones that are peaks. The next step
is to sort the peaks by height. Then we can go through
each peak one by one and do a bfs from each point in the
peak. If dp[x][y] is the lowest point you have to go
through to get from position (x,y) to a higher peak, and
grid[x][y] is the height of position (x,y) in our bfs we
have the transition dp[nx][ny] = max(dp[nx][ny],
min(dp[x][y],grid[nx][ny])) where (nx,ny) represents the
coordinates of a cell adjacent to (x,y). The answer for
a peak is dp[x][y] for any (x,y) located on the peak.
After a bit of analysis I think that this algorithm
becomes about (n*m)^(3/2) in the worst case scenario.

A problem that uses a similar bfs approach:
https://atcoder.jp/contests/agc044/tasks/agc044_b

*/

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

using namespace std;

#define FOR(a,b) for(int a=0;a<b;a++)
#define F0R(a,b,c) for(int a = b; a<=c; a++)
#define f first
#define s second
#define m0(x) memset(x,0,sizeof(x))
#define all(x) x.begin(), x.end()

typedef pair<int,int> pi;
typedef long long ll;
typedef vector<int> vi;
typedef vector<pi> vpi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

vvi grid, dp;
vvb found;

const int dx[8] = {0,0,-1,1,1,1,-1,-1};
const int dy[8] = {-1,1,0,0,1,-1,1,-1};

int ptr = 0;

int n,m;

struct flats{
    vpi parts;
    int height = 0;
    bool peak = 1;
};

bool comp(flats &a, flats &b){
    if(a.height != b.height) return (a.height > b.height);
    return (a.parts[0] > b.parts[0]);
}

vector<flats> things;

void dfs(int x, int y){
    if(x == 0 || x == n+1 || y == 0 || y == m+1) return;
    found[x][y] = 1;
    things[ptr].parts.push_back({x,y});
    FOR(i,8){
        int nx = x+dx[i], ny = y+dy[i];
        if(grid[nx][ny] > grid[x][y]){
            things[ptr].peak = 0; continue;
        }
        if(found[nx][ny]) continue;
        if(grid[nx][ny] == grid[x][y]) dfs(nx,ny);
    }
}

vector<flats> peaks;

void bfs(int x, int y){
    vpi q;
    int qsz = 1, qptr = 0;
    dp[x][y] = grid[x][y];
    q.push_back({x,y});
    for(; qptr < qsz; qptr++){
        int cx = q[qptr].f, cy = q[qptr].s;
        FOR(i,8){
            int nx = cx+dx[i], ny = cy+dy[i];
            int goal = min(grid[nx][ny],dp[cx][cy]);
            if(dp[nx][ny] >= goal) continue;
            dp[nx][ny] = goal;
            q.push_back({nx,ny});
            qsz++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    grid.resize(n+2,vi(m+2));
    dp.resize(n+2,vi(m+2));
    found.resize(n+2,vb(m+2));
    F0R(i,1,n) F0R(j,1,m) cin >> grid[i][j];
    F0R(i,1,n) F0R(j,1,m){
        if(found[i][j]) continue;
        things.emplace_back();
        things[ptr].height = grid[i][j];
        dfs(i,j);
        if(things[ptr].peak) peaks.push_back(things[ptr]);
        ptr++;
    }
    sort(all(peaks),comp);
    int cur = 0;
    vector<flats> waiting;
    vpi finans;
    for(flats & p : peaks){
        if(p.height != cur){
            for(flats &op : waiting){
                for(pi &a : op.parts) bfs(a.f,a.s);
            }
            waiting.clear();
            cur = p.height;
        }
        int ans = 0;
        for(pi &a: p.parts)
            ans = max(ans, dp[a.f][a.s]);
        finans.push_back({cur,ans});
        waiting.push_back(p);
    }
    sort(all(finans),greater<pi>());
    cout << finans.size() << "\n";
    for(auto &a: finans) cout << a.f << " " << a.s << "\n";
    return 0;
}
