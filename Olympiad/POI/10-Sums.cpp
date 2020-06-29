/*
Logic:
All of the numbers in the second set can be represented as k*A[1]+x
Knowing this we can do knapsack dp to find the smallest number that
can be represented as k mod A[1]
The time limit was extremely strict so I came up with another optimization
I assumed(not too sure of correctness) that if the number of distinct numbers
mod A[1] in ratio to A[1] was large enough, we wouldn't have to dp on every
b*a[i], 0 < b < n, but only to b < n/8.
*/

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
//#pragma GCC target("sse4")

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

const int large = 1e9+1;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vi arr(n);
    FOR(i,n) cin >> arr[i];
    const int sz = arr[0];
    vi fast(sz,large); fast[0] = 0;
    vi mod(n);
    vector<bool> found(sz); found[0] = 1;
    vector<bool> good(n);
    int cnt = 0;
    FOR(i,n){
        mod[i] = arr[i]%sz;
        if(found[mod[i]] == 0){
            found[mod[i]] = 1;
            good[i] = 1;
            cnt++;
        }
    }
    int b = sz-1;
    if(cnt > 500 && sz > 5000) b /= 8;
    const int len = b;
    F0R(i,1,n-1){
        int a = mod[i];
        if(!good[i]) continue;
        int k = a;
        F0R(j,1,len){
            int d = j*arr[i];
            if(d >= large) break;
            if(d < fast[k]) fast[k] = d;
            k += a;
            if(k >= sz) k -= sz;
            if(k == 0) break;
        }
    }
    F0R(i,1,n-1){
        int a = mod[i];
        if(!good[i]) continue;
        FOR(j,sz){
            int rel = (j-a);
            if(rel < 0) rel += sz;
            int d = arr[i]+fast[rel];
            if(d < fast[j]) fast[j] = d;
        }
    }
    int k; cin >> k;
    FOR(i,k){
        int a; cin >> a;
        if(fast[a%sz] > a) cout << "NIE\n";
        else cout << "TAK\n";
    }
    return 0;
}
