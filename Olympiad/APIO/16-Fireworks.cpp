/*
Used slope trick. Same idea as mentioned here:
https://codeforces.com/blog/entry/47821
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

struct hull{
    priority_queue<ll> lhull;
    priority_queue<ll,vector<ll>,greater<ll>> rhull;
    ll height = 0;
    void putpar(ll len){
        if(lhull.empty()){
            lhull.push(len);
            rhull.push(len);
            return;
        }
        ll a = lhull.top(); lhull.pop(); a += len;
        lhull.push(a);
        a = rhull.top();
        while(!rhull.empty()) rhull.pop();
        rhull.push(a+len);
    }
    void plu(ll num){
        lhull.push(num);
        ll a = lhull.top(); lhull.pop();
        height += a-num;
        rhull.push(a);
    }
    void pld(ll num){
        rhull.push(num);
        ll a = rhull.top(); rhull.pop();
        height += num - a;
        lhull.push(a);
    }
    void ins(ll num){
        plu(num);
        pld(num);
    }
    void combine(hull & other){
        while(!other.lhull.empty()){
            ll a = other.lhull.top();
            other.lhull.pop();
            pld(a);
        }
        while(!other.rhull.empty()){
            ll a = other.rhull.top();
            other.rhull.pop();
            plu(a);
        }
        height += other.height;
    }
};

vector<ll> children, root;

const int large = 3e5+1;

vi edges[large];

int dfs1(int child){
    int ccnt = 1;
    for(auto &a: edges[child]) ccnt += dfs1(a);
    children[child] = ccnt;
    return ccnt;
}

void dfs2(int child, hull &ans){
    const int sz = edges[child].size();
    vi &e = edges[child];
    FOR(i,sz){
        if(children[e[i]] > children[e[0]])
            swap(e[i], e[0]);
    }
    if(sz != 0){
        dfs2(e[0],ans);
    }
    F0R(i,1,sz-1){
        hull cur;
        dfs2(e[i],cur);
        ans.combine(cur);
    }
    ans.putpar(root[child]);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin >> n >> m;
    hull ans;
    children.resize(n+m+1);
    root.resize(n+m+1);
    F0R(i,2,n+m){
        int par;
        cin >> par >> root[i];
        edges[par].push_back(i);
    }
    dfs1(1);
    dfs2(1,ans);
    cout << ans.height << "\n";
    return 0;
}
