/*
Logic:

We can solve this problem using dp by
rooting the tree at x. We do dp on a
node's children where dp[i] is the
optimal cost of visiting i nodes in the
subtree. Because the path does not have
to end at x, we store the longest
distance of the root node to a node in the
optimal set. To combine the dp of subtrees
we can do knapsack dp. With certain
optimizations, this algorithm easily runs in
time.
*/

#include <bits/stdc++.h>
#pragma GCC optimize("O3")

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

const int large = 1e4+1;

const int inf = 1e9;

int n,k,x;

vpi edges[large];

bool regcomp(const pi &a, const pi &b){
    if(a.f != b.f) return (a.f < b.f);
    else return (a.s > b.s);
}

bool greecomp(const pi &a, const pi &b){
    if(2*a.f-a.s != 2*b.f-b.s) return (2*a.f-a.s < 2*b.f-b.s);
    else return (a.f < b.f);
}


int dfs(int child, int parent, vpi &reg, vpi &greedy){
    int children = 1;
    int ptr = 0;
    vpi csize;
    vector<vpi> chilreg,chilgree;
    for(auto &a: edges[child]){
        if(a.f == parent) continue;
        chilreg.resize(ptr+1);
        chilgree.resize(ptr+1);
        int c = dfs(a.f,child,chilreg[ptr],chilgree[ptr]);
        for(auto &b: chilreg[ptr]){
            b.f += a.s;
            b.s += a.s;
        }
        for(auto &b: chilgree[ptr]){
            b.f += a.s;
            b.s += a.s;
        }
        children += c;
        csize.push_back({c,ptr});
        ptr++;
    }
    int nsz = min(children,k);
    reg.resize(nsz+1,{inf,0});
    greedy.resize(nsz+1,{inf,0});
    reg[1].f = 0;
    greedy[1].f = 0;
    sort(all(csize),greater<pi>());
    int chilcnt = 1;
    for(auto &a: csize){
        int c = a.f; ptr = a.s;
        int sz = min(c,k);
        for(int i = min(chilcnt,nsz-1); i >= 1; i--){
            F0R(j,1,sz){
                if(i+j> nsz) break;
                //reg
                pi b = {reg[i].f+chilreg[ptr][j].f,max(reg[i].s,chilreg[ptr][j].s)};
                reg[i+j]= min(reg[i+j],b,regcomp);
                //greedy
                greedy[i+j] = min(greedy[i+j],b,greecomp);
                b = {greedy[i].f+chilreg[ptr][j].f,max(greedy[i].s,chilreg[ptr][j].s)};
                greedy[i+j] = min(greedy[i+j],b,greecomp);
                b = {reg[i].f+chilgree[ptr][j].f,max(reg[i].s,chilgree[ptr][j].s)};
                greedy[i+j] = min(greedy[i+j],b,greecomp);
            }
        }
        chilcnt += c;
    }
    return children;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k >> x;
    FOR(i,n-1){
        int a,b,c; cin >> a >> b >> c;
        edges[a].push_back({b,c});
        edges[b].push_back({a,c});
    }
    vpi reg,greedy;
    dfs(x,0,reg,greedy);
    cout << 2*greedy[k].f-greedy[k].s << "\n";
    return 0;
}
