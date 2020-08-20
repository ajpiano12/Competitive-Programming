/*
Logic:

The first step is to sort w. It can be proven that if
the array of molecules w, is sorted, the answer if it
exists is some subarray of w.

The proof of this follows:

The first part is to establish that a solution can only
exist if that for some x, x <= n, where pre[x] is the
sum of the first x elements and suf[x] is the sum of the
last x elements, pre[x] <= u and suf[x] >= l. To understand
this let us think that there exists some answer with x
elements. Let us say that the sum of the elements in it is S.
Since pre[x] consists of the smallest elements in
w, S >= pre[x]. If pre[x] > u, then S > u, leading to a
contradiction. Similarly, suf[x] consists of the x largest
elements in w. Thus, S <= suf[x]. If suf[x] < l, S < l
leading to a contradiction. Thus the two conditions pre[x] <= u
and suf[x] >= l  are necessary for an answer to be possible.
The next step is to show that if these conditions are met
we can find an answer. The way do this is to take the x where
the above conditions are met and to start a sliding window with
start 0 and sum S = pre[x]. When you move the sliding window
starting at position i, right by one element, the sum increases
by w_(i+x)-w_(i). Since the conditions above tell us that S
ranges from below u to above l, the only way that we can not
have an S such that l <= S <= u, is if S moves from S < l to S > u
in one move. This means that there would have to exist an i such
that w_(i+x)-w(i) > u-l. However the problem states that
u-l > max(w)-min(w) implying a contradiction. Thus, we have shown
that pre[x] <= u and  suf[x] >= l <--> an answer exists and can be
a contiguous interval of length x.

With the above proof all we have to do is find an interval that satisfies
l <= S <= u. We can easily do this with the sliding window method.

*/

#include <bits/stdc++.h>
#include <molecules.h>
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

vi find_subset(int d, int u, vi w){
    int n = w.size();
    vector<pair<ll,int>> w2(n);
    FOR(i,n) w2[i].f = w[i];
    FOR(i,n) w2[i].s = i;
    sort(all(w2));
    int l = 0, r = 0;
    ll total = 0;
    for(; l < n; l++){
        if(r < l){
            total = 0;
            r = l;
        }else if(l != 0) total -= w2[l-1].f;
        for(; (r<n && total+w2[r].f <= u); r++) total += w2[r].f;
        if(total >= d) break;
    }
    if(l >= r || total < d){
        vi ans;
        return ans;
    }else{
        vi ans(r-l);
        assert(r <= n);
        assert(l < n);
        FOR(i,r-l) ans[i] = w2[l+i].s;
        return ans;
    }
}
