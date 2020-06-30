/*
Logic:
This problem is solvable using knapsack dp.
To optimize it from O(n*k*b) to O(n*k*log(b))
we can do knapsack on all values x*a_i where
x is a power of two and x < b_i. We can store
the amount of notes for each position in an
array.
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

int n;
vpi notes;

const int large = 1e9;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    notes.resize(n);
    for(auto &a: notes) cin >> a.f;
    for(auto &a: notes) cin >> a.s;
    int k; cin >> k;
    vi dp(k+1,large); dp[0] = 0;
    vector<vi> vals(k+1,vi(n));
    FOR(i,n){
        for(int j = 0; ((notes[i].f<<j) <= k && (1<<j) <= notes[i].s); j++){
            int dif = (notes[i].f<<j), add = (1<<j);
            for(int pos = k; pos >= dif; pos--){
                if(dp[pos] > dp[pos-dif]+add && vals[pos-dif][i]+add <= notes[i].s){
                    dp[pos] = dp[pos-dif]+add;
                    vals[pos] = vals[pos-dif];
                    vals[pos][i] += add;
                }
            }
        }
    }
    cout << dp[k] << "\n";
    FOR(i,n) cout << vals[k][i] << " ";
    cout << "\n";
    return 0;
}
