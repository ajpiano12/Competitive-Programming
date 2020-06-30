/*
Problem: https://oj.uz/problem/view/COCI16_vjestica
Submission: https://oj.uz/submission/243259

Logic:

We can realize that to minimize the number of nodes
in a trie of strings, we should put all the common
letters in the front. After that we can split the
group of strings up in every possible way into two
groups and find the minimum length of the tries over
all possibilities. To find the final answer we have
to subtract the amount of common letters since we
would have counted that twice. To do all of this
efficiently we can use bitmask dp as shown below.

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

struct word{
    int letters[26];
};

const int large = 1e9;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vi dp(1<<n);
    vi nones[n+1];
    F0R(i,1,(1<<n)-1){
        int a = __builtin_popcount(i);
        nones[a].push_back(i);
    }
    vector<word> words;
    FOR(i,n){
        word w;
        string s; cin >> s;
        FOR(j,26) w.letters[j] = 0;
        for(auto &a:s) w.letters[a-'a']++;
        words.push_back(w);
    }
    FOR(i,n){
        int tot = 0;
        FOR(j,26) tot += words[i].letters[j];
        dp[nones[1][i]] = tot;
    }
    F0R(bits,2,n){
        for(auto & mask:nones[bits]){
            word a;
            FOR(i,26) a.letters[i] = large;
            FOR(i,n){
                if(mask&(1<<i)){
                    FOR(j,26){
                        a.letters[j] = min(a.letters[j],words[i].letters[j]);
                    }
                }
            }
            int tot = 0;
            FOR(i,26) tot += a.letters[i];
            int best = large;
            int ptr = mask;
            ptr = (ptr-1)&mask;
            while(ptr > 0){
                best = min(best, dp[ptr]+dp[mask^ptr]);
                ptr = (ptr-1)&mask;
            }
            dp[mask] = best-tot;
        }
    }
    int k = (1<<n)-1;
    cout << dp[k]+1 << "\n";
    return 0;
}
