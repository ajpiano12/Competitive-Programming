/*
Logic:
We can solve this question using dp
where dp[i][mask_1][mask_2] represents
the maximum happiness where the state of
the first four animals is represented by
mask_1 and the state of the last 5 animals
is represented by mask_2. It counts all
children whose last visible cages is from 5
to i.
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

typedef pair<int,int> pi;
typedef long long ll;
typedef vector<int> vi;
typedef vector<pi> vpi;

struct child{
    int like = 0;
    int hate = 0;
};

int dp[2][16][32];
vector<child> children[10000];

const int inf = 1e9;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n,c; cin >> n >> c;
        FOR(i,n) children[i].clear();
        FOR(j,c){
            child cur; cur.like = 0, cur.hate = 0;
            int e; cin >> e; e--;
            int b = e+4; if(b >= n) b -= n;
            int f,l; cin >> f >> l;
            FOR(i,f){
                int a; cin >> a; a -= e+1;
                if(a < 0) a += n;
                cur.hate |= 1<<(4-a);
            }
            FOR(i,l){
                int a; cin >> a; a -= e+1;
                if(a < 0) a += n;
                cur.like |= 1<<(4-a);
            }
            children[b].push_back(cur);
        }
        FOR(j,16) FOR(k,32) dp[0][j][k] = -inf;
        FOR(j,32) dp[0][(j>>1)][j] = 0;
        FOR(j,32) for(child &a:children[4]) if(a.like&j || a.hate&(j^31)) dp[0][(j>>1)][j]++;
        F0R(i,5,8){
            int cur = (i&1);
            int pre = cur^1;
            FOR(j,16) FOR(k,32) dp[cur][j][k] = -inf;
            FOR(j,16){
                FOR(k,1<<(i-3)){
                    int place = (j<<(i-3))+k;
                    int b = place; b >>= 1;
                    b &= 31; place &= 31;
                    dp[cur][j][place] = dp[pre][j][b];
                    for(auto &a: children[i]) if(a.like&place || a.hate&(place^31)) dp[cur][j][place]++;
                }
            }
        }
        F0R(i,9,n-1){
            int cur = (i&1);
            int pre = cur^1;
            FOR(j,16) FOR(k,32) dp[cur][j][k] = -inf;
            FOR(j,16){
                FOR(k,32){
                    int b = k; b >>= 1;
                    dp[cur][j][k] = max(dp[pre][j][b],dp[pre][j][b+16]);
                    for(auto &a: children[i]) if(a.like&k || a.hate&(k^31)) dp[cur][j][k]++;
                }
            }
        }
        FOR(i,4){
            int cur = ((n+i)&1);
            int pre = cur^1;
            FOR(j,16) FOR(k,32) dp[cur][j][k] = -inf;
            FOR(j,16){
                FOR(k,1<<(4-i)){
                    int place = (k<<(i+1))+(j>>(3-i));
                    int b = place; b >>= 1;
                    dp[cur][j][place] = max(dp[pre][j][b],dp[pre][j][b+16]);
                    for(auto &a: children[i]) if(a.like&place || a.hate&(place^31)) dp[cur][j][place]++;
                }
            }
        }
        int place = (n+3)&1;
        int best = 0;
        FOR(j,16) FOR(k,32) best = max(best,dp[place][j][k]);
        cout << best << "\n";
    }
    return 0;
}
