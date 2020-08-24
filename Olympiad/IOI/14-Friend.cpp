/*

Difference Between This Solution and Official Solution:

My solution is a bit different from the intended solution.
The intended solution is a bit shorter and uses less variables.
The reason for the difference is because I iterated through
each node's children in chronological order instead of
reverse chronological order like the intended solution.

Logic:

The way my solution works is that it keeps a list of each node's
children. Node j is considered a child of i if host[j] = i. To
find the answer, we do a dp similar to the way you would find the
maximal independent set of a tree. In this method, each node
contains 2 values, the maximal independent set of the subtree of i
if i can be included in the set. I refer to this as dp[i].f. The
other value is the maximal independent set of the subtree where i
can not be included in the set. I refer to this as dp[i].s. In a
tree dp[i].s = sum(dp[children].f) and dp[i].f = max(dp[i].s,
cost[i] + sum(dp[children].s)). However, since this graph is not
always a tree the solution has to get a little bit more creative.
The way I thought about this problem was to separate the nodes into
top level nodes, bottom level nodes and given nodes. If we were
trying to find the dp value for a node i, top level nodes would be
the ones that had an edge connecting them with host[i]. This is
basically i and the children of i who were hosted with protocol 1
or 2. Then there are the bottom level nodes. These were the ones
with an edge connecting them to a top level node. These were the
children of i hosted with protocol 0 or the nodes that constitute
dp[j].s where j is any child of i hosted with protocol 1 or 2.
The given nodes were the nodes that constitute dp[j].s where j is
a child of i hosted with protocol 0. dp[i].s is really just the sum
of the bottom values so we can write that as sum(dp[j].s if
protocol[j] = 1,2 or dp[j].f if protocol[j] = 0) where j is a child
of i. Calculating dp[i].f is a little bit harder. However we can
split it up into cases as we iterate through the children of i in
increasing order.

Case 1 Initialization:
One possible configuration of nodes is node i, children of i's
protocol 2 children nodes and the sum of the given nodes. This
will suffice for an initial value. Other configurations will be
handled in the other cases.

Case 2 Protocol 0 Child:
The cases with this have been counted in the dp[i].s value and
the given value already. So all we have to do is update the
counters counting these values.

Case 3 Protocol 1 Child:
We add dp[j].s to its respective counter.
We also add dp[j].f to its respective counter. We can now try
to figure out a value of dp[i].f. To keep this state different
from the others we have to include node j in this combination.
We can also include all the previous protocol 1 nodes since
they are not friends with j. We can include all the children of
the protocol 2 nodes since the protocol 2 nodes are all friends
with j which means they can not be included. Lastly, we can
either include the rest of i's protocol 0 children and the
current number of given nodes since they are not friends with j
or we can include i and all the given nodes.
Thus we get the expression:
dp[i].f = max(dp[i].f, (sum of protocol 1 nodes) + (sum of
protocol 2 children) + max((current sum of given nodes)+(sum of
the rest of i's protocol 0 children),(value of node i)+(sum of
all the given nodes))).

Case 4 Protocol 2 Child:
Just like in the previous case we have to include this node.
Now we can include all of the previous protocol 1 nodes because
they are not friends with this node. Now we can include all of
the other protocol 2 node's children because we can not include
any other protocol 2 node since they are all friends with this
node. Lastly we can include the protocol 0 nodes that come after
this node and the given nodes that come before this node. Thus
we get this expression:
dp[i].f = max(dp[i].f, (this node) + (previous protocol 1 nodes)
+ (sum of all children of protocol 2 nodes except for this one)
+ (sum of protocol 0 nodes that come after this node)
+ (sum of current given nodes));

Note:
After we find the values for a certain dp[i], we need to do
dp[i].f = max(dp[i].f, dp[i].s) to keep the integrity of this dp.

*/
#include <bits/stdc++.h>
#include <friend.h>
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

int findSample(int n, int conf[], int host[], int pr[]){
    vi edges[n]; // edges[i] contains children of node i
    F0R(i,1,n-1) edges[host[i]].push_back(i);
    vpi dp(n);
    for(int i = n-1; i >= 0; i--){
        int tc = 0, cc = 0; // total number and current
                            // number of protocol 0 and
                            // 1 children respectively

        int wc = 0; // total number of protocol 2 children

        int given = 0, curg = 0; // total  and current
                                 // number of children of
                                 // protocol 0 children

        for(auto &a: edges[i]){ // iterate through children
                                // to add the children's
                                // values to their
                                // respective counts
            if(pr[a] == 0){
                tc += dp[a].f;
                given += dp[a].s;
            }
            else if(pr[a] == 1) tc += dp[a].s;
            else wc += dp[a].s;
        }

        dp[i].s = tc + wc; // these are the bottom level nodes

        dp[i].f = conf[i]+given+wc; // initial top level value
                                    // where i is the only top
                                    // level node

        int upl = 0;                // holds sum of protocol 1
                                    // children

        for(auto &a: edges[i]){     // iterate through children
                                    // to find the max top level
                                    // value
            if(pr[a] == 0){
                cc += dp[a].f;
                curg += dp[a].s;
            }else if(pr[a] == 1){
                cc += dp[a].s;
                upl += dp[a].f;
                dp[i].f = max(dp[i].f, upl + wc + max(tc-cc+curg,conf[i]+given));
            }else{
                dp[i].f = max(dp[i].f, dp[a].f + upl + wc - dp[a].s + tc-cc+curg);
            }
        }
        dp[i].f = max(dp[i].f,dp[i].s);
    }
    return dp[0].f;
}
