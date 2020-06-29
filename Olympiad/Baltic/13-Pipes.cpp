/*
Problem: https://oj.uz/problem/view/BOI13_pipes
Submission: https://oj.uz/submission/242877
Logic:
If there is a cycle with an odd number of edges, there are an infinite
number of solutions
If there are multiple cycles, there are an infinite number of solutions
Otherwise the graph looks like a tree with at most one additional edge
Solve for the edges from the bottom up, add the remainder to the additional
edge
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

int n,m;
const int large = 1e5;
vpi edges[large+1];
vpi parents;
vi found;
vi change;
vi ans;

bool ef = 0;
pair<int,pi> ge;

int dfs(int p,int child, int height){
    found[child] = height;
    int upedge = 0;
    int got = 0;
    for(auto &a: edges[child]){
        if(a.f == p){
            upedge = a.s; continue;
        }
        if(!found[a.f]){
            got += dfs(child,a.f,height+1);
        }else if(found[a.f] < found[child]){
            int dist = found[child]-found[a.f];
            if(dist&1 || ef){
                cout << 0 << "\n";
                exit(0);
            }else{
                ef = 1;
                ge = {a.s,{child,a.f}};
            }
        }
    }
    parents[child] = {p,upedge};
    ans[upedge] = change[child]-got;
    return ans[upedge];
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    if(m > n){
        cout << "0\n"; return 0;
    }
    parents.resize(n+1);
    found.resize(n+1);
    change.resize(n+1);
    ans.resize(m+1);
    F0R(i,1,n) cin >> change[i];
    F0R(i,1,m){
        int u,v; cin >> u >> v;
        edges[u].push_back({v,i});
        edges[v].push_back({u,i});
    }
    int rem = dfs(0,1,1);
    if(rem&1 || (rem != 0 && ef == 0)){
        cout << "0\n"; return 0;
    }
    if(ef){
        int add = rem/2;
        if((found[ge.s.s]-1)&1){
            add = -add;
        }
        ans[ge.f] = add;
        int ptr = ge.s.f;
        bool m1 = 1;
        for(; ptr != 1; ){
            if(ptr == ge.s.s) add *= 2;
            if(m1) ans[parents[ptr].s] -= add;
            else ans[parents[ptr].s] += add;
            ptr = parents[ptr].f;
            m1 = !m1;
        }
    }
    F0R(i,1,m) cout << 2*ans[i] << "\n";
    return 0;
}
