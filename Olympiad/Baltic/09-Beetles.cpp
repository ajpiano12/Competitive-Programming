/*
Logic:
We can solve this using dp. The approach would
be to write it as dp[i][j][k] where it stands
for the best combination of time and dew drops
collected if the first i negative and first j
positive positions have been reached and you
want to reach k more dew drops. We can split
each dp entry into two parts. The best pair
when the path ends at the lower end and the
best pair when the path ends at the upper end.
The answer is the maximum value in the array.
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

struct dobj{
    int water = 0;
    int time = 0;
};

struct dpobj{
    dobj reg;
    dobj rev;
} dp[301][301][301];

const int inf = 7e6;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    m0(dp);
    FOR(i,201)FOR(j,201)FOR(k,301){
        dp[i][j][k].reg.time =  inf;
        dp[i][j][k].rev.time =  inf;
    }
    int n,m; cin >> n >> m;
    int add = 0;
    vi pos;
    vi neg;
    int negcnt = 0, poscnt = 0;
    FOR(i,n){
        int a; cin >> a;
        if(a == 0){
            add += m;
            continue;
        }
        else if(a > 0){
            pos.push_back(a); poscnt++;
        }
        else{
            neg.push_back(a); negcnt++;
        }
    }
    pos.push_back(0);
    neg.push_back(0);
    sort(all(pos));
    sort(all(neg), greater<int>());
    dp[0][0][1].reg.time = 0;
    dp[0][0][1].rev.time = 0;
    int best = 0;
    F0R(i,1,poscnt){
        pi a,b;
        a.s = pos[i];
        a.f = dp[0][i-1][1].reg.water + m - a.s;
        b.s = a.s+pos[i];
        b.f = a.f;
        best = max(best, a.f);
        F0R(k,1,n){
            dp[0][i][k].reg.water = a.f;
            dp[0][i][k].reg.time = a.s;
            dp[0][i][k].rev.water = b.f;
            dp[0][i][k].rev.time = b.s;
        }
    }
    F0R(i,1,negcnt){
        pi a,b;
        a.s = -neg[i];
        a.f = dp[i-1][0][1].reg.water + m - a.s;
        b.s = a.s-neg[i];
        b.f = a.f;
        best = max(best, a.f);
        F0R(k,1,n){
            dp[i][0][k].rev.water = a.f;
            dp[i][0][k].rev.time = a.s;
            dp[i][0][k].reg.water = b.f;
            dp[i][0][k].reg.time = b.s;
        }
    }
    F0R(i,1,negcnt){
        F0R(j,1,poscnt){
            FOR(k,n){
                pi a,b;
                //top
                a.s = dp[i][j-1][k+1].reg.time + pos[j]-pos[j-1];
                a.f = dp[i][j-1][k+1].reg.water + m - a.s;
                b.s = dp[i][j-1][k+1].rev.time + pos[j]-neg[i];
                b.f = dp[i][j-1][k+1].rev.water + m - b.s;
                best = max(best,a.f);
                best = max(best,b.f);
                if(a.f-k*a.s < b.f-k*b.s) a = b;
                dp[i][j][k].reg.water = a.f;
                dp[i][j][k].reg.time = a.s;
                //bottom
                a.s = dp[i-1][j][k+1].rev.time + neg[i-1]-neg[i];
                a.f = dp[i-1][j][k+1].rev.water + m - a.s;
                b.s = dp[i-1][j][k+1].reg.time + pos[j]-neg[i];
                b.f = dp[i-1][j][k+1].reg.water + m - b.s;
                best = max(best,a.f);
                best = max(best,b.f);
                if(a.f-k*a.s < b.f-k*b.s) a = b;
                dp[i][j][k].rev.water = a.f;
                dp[i][j][k].rev.time = a.s;
                int dist = pos[j]-neg[i];
                if(dp[i][j][k].rev.water-k*dp[i][j][k].rev.time-k*dist > dp[i][j][k].reg.water-k*dp[i][j][k].reg.time){
                    dp[i][j][k].reg.water = dp[i][j][k].rev.water;
                    dp[i][j][k].reg.time = dp[i][j][k].rev.time+dist;
                }
                if(dp[i][j][k].reg.water-k*dp[i][j][k].reg.time-k*dist > dp[i][j][k].rev.water-k*dp[i][j][k].rev.time){
                    dp[i][j][k].rev.water = dp[i][j][k].reg.water;
                    dp[i][j][k].rev.time = dp[i][j][k].reg.time+dist;
                }
            }
        }
    }
    cout << add+best << "\n";
    return 0;
}
