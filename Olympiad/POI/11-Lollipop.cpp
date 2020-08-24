/*

Logic:
The key observation is that if you have a segment
that looks like 1.... or ....1 you can make any
number from 1 to S, the sum of the subsequence.
We can prove this case with induction. We will
assume that all cases look like 1.... because the
same logic will apply to ....1 since it is just
1.... backwards. Our base case is when the size is
1. In that case the segment is just 1. Thus by using
the 1 we get the 1. Now for everything else we get 2
cases.

Case 1 1....1:
In this case we have some segment. If S1 is the sum of
the segment 1.... we can assume that we can create all
the numbers 1 - S1. Now the sum of this sequence S2,
is S1+1. This is obviously reached by choosing all the
numbers. Thus this case is proven.

Case 2 1....2:
In this case we need to achieve S1+1 and S1+2. We will
first deal with S1+2. This is obviously reached by using
the whole segment. The second case is S1+1. Since
S1 = 1...., then S1-1 = .... so S1-1 + 2 = ....2 = S1+1.
Thus we can achieve both S1+1 and S1+2 and are given that
we can achieve 1 - S1 so our proof for this case is complete.

Since both cases have been proven, it is true that the
sequence 1.... can create lollipops of size 1 to S. We
can now find the longest 1.... or ....1 sequence in the
big lollipop in O(n) and find the smaller segments in the
same method we used for the proof. Lastly if there are x
2s in the lollipop that aren't in the 1.... sequence i.e.
it looks like 2...2,1... or ...1,2..2 we can achieve all
values S+2y where y <= x where S is the sum of the 1...
sequence. This is easily seen since you just add one of 2s
to the sequence one by one.

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

const int large = 2e6+1;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin >> n >> m;
    vi loll(n);
    vector<pair<bool,pi>> ans(large);
    int tsum = 0;
    FOR(i,n){
        char a; cin >> a;
        if(a == 'T') loll[i] = 2;
        else loll[i] = 1;
        tsum += loll[i];
    }
    int fr = 0, ba = 0;
    for(; (loll[fr] == 2 && fr < n); fr++);
    for(; (loll[n-ba-1] == 2 && ba < n); ba++);
    bool gf = 0;
    if(fr <= ba) gf = 1;
    if(gf){
        bool moveup = 0;
        int ptr = fr;
        int total = 0;
        F0R(i,1,tsum-2*fr){
            if(moveup){
                total++;
                moveup = 0;
                ans[i].f = 1;
                ans[i].s = {fr+moveup+1,ptr};
                continue;
            }
            total += loll[ptr++];
            if(total == i+1){
                moveup = 1;
                total--;
            }
            ans[i].f = 1;
            ans[i].s = {fr+moveup+1,ptr};
        }
        FOR(i,fr){
            total += 2;
            ans[total].f = 1;
            ans[total].s = {fr-i,ptr};
        }
    }else{
        bool moveup = 0;
        int start = n-ba-1;
        int ptr = start;
        int total = 0;
        F0R(i,1,tsum-2*ba){
            if(moveup){
                total++;
                moveup = 0;
                ans[i].f = 1;
                ans[i].s = {ptr+2,start-moveup+1};
                continue;
            }
            total += loll[ptr--];
            if(total == i+1){
                moveup = 1;
                total--;
            }
            ans[i].f = 1;
            ans[i].s = {ptr+2,start-moveup+1};
        }
        FOR(i,ba){
            total += 2;
            ans[total].f = 1;
            ans[total].s = {1,start+i+2};
        }
    }
    FOR(i,m){
        int k; cin >> k;
        if(ans[k].f){
            cout << ans[k].s.f << " " << ans[k].s.s << "\n";
        }else cout << "NIE\n";
    }
    return 0;
}
