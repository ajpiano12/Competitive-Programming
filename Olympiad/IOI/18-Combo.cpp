#include <bits/stdc++.h>
#include <combo.h>
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

/*
//grader press function
const string sans = "ABXYY";
const int sz = 5;

int cptr = 1;

int press(string a){
    int sz2 = a.size();
    if(sz2 > 4*sz){
        cout << a << " PROBLEM COMBO SIZE TOO BIG\n";
        exit(1);
    }
    if(cptr > sz+2){
        cout << a << " PROBLEM TOO MANY QUERIES\n";
        exit(2);
    }
    cout << "Combo " << cptr++ << ": " << a << "     Similarity: ";
    int best = 0;
    F0R(i,1,sz){
        FOR(j,sz2-i+1){
            bool good = 1;
            FOR(k,i){
                if(a[j+k] != sans[k]){
                    good = 0;
                    break;
                }
            }
            if(good) best = i;
        }
    }
    cout << best << "\n";
    return best;
}
*/

string guess_sequence(int n){
    if(n == 1){
        if(press("A")) return "A";
        else if(press("B")) return "B";
        else if(press("X")) return "X";
        else return "Y";
    }
    string ans = "";
    int cnt1 = press("BABXAXAY");
    if(cnt1 == 1){
        int cnt2 = press("BY");
        if(cnt2 == 0) ans += 'X';
        else if(cnt2 == 1) ans += 'Y';
        else ans += 'B';
    }else{
        int cnt2 = press("XA");
        if(cnt2 == 0) ans += 'B';
        else if(cnt2 == 1) ans += 'A';
        else ans += 'X';
    }
    char car[4] = {'A','B','X','Y'};
    char acar[3];
    for(int ptr = 0, check = 0; check < 4; check++){
        if(car[check] != ans[0]){
            acar[ptr++] = car[check];
        }
    }
    FOR(i,n-2){
        string check = "";
        FOR(j,3) check += ans+acar[0]+acar[j];
        check += ans+acar[1];
        int cnt = press(check);
        if(cnt == i+3) ans += acar[0];
        else if(cnt == i+2) ans += acar[1];
        else ans += acar[2];
    }
    string check1 = ans+acar[0]+ans+acar[1];
    cnt1 = press(check1);
    if(cnt1 == n){
        string check2 = ans+acar[0];
        int cnt2 = press(check2);
        if(cnt2 == n) ans += acar[0];
        else ans += acar[1];
    }else ans += acar[2];
    return ans;
}

/*
//grader
int main(){
    cout << "Answer: " << guess_sequence(sz) << "\n";
}
*/
