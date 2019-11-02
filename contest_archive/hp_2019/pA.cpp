#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define FOR3(i, a, b) for (int i = (a); i<(b); i++)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#define f first
#define s second
#define MN(a,b) a = min(a,(__typeof__(a))(b))
#define MX(a,b) a = max(a,(__typeof__(a))(b))
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#ifdef BTC
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 1000006;

void GG(){cout<<"-1\n"; exit(0);}

int n;
vector<int> edge[MAXN];

vector<int> gp1, gp2;

bool vis[MAXN], nans;
bool c[MAXN];
void dfs (int nd, bool cl) {
    c[nd] = cl;
    vis[nd] = true;
    if (cl) {
        gp1.emplace_back(nd);
    } else {
        gp2.emplace_back(nd);
    }
    for (auto v : edge[nd]) {
        if (vis[v] && c[v] == cl) {
            debug(nd, v);
            nans = true;
        }
        if (!vis[v]) {
            dfs(v, !cl);
        }
    }
}

void opt (vector<int> &vec) {
    cout << "[";
    for (int i=0; i<SZ(vec); i++) {
        cout << vec[i] << ",]"[i==SZ(vec)-1];
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    string str;
    int idx = 0;
    while (cin >> str) {
        stringstream ss;
        string cur;
        for (int i=1; i<SZ(str)-1; i++) {
            if (str[i] == ',') {
                cur += ' ';
            } else {
                cur += str[i];
            }
        }
        debug(cur);
        ss << cur;
        int tmp;
        debug("HI");
        while (ss >> tmp) {
            edge[idx].emplace_back(tmp);
        }
        idx++;
    }

    REP (i, idx) {
        if (!vis[i]) {
            debug(i);
            dfs(0, 1);
        }

    }


    sort(ALL(gp1));
    sort(ALL(gp2));

    if (nans) {
        cout << "[0]" << endl;
    } else {
        opt(gp1);
        cout << " ";
        opt(gp2);
        cout << endl;
    }



    return 0;
}
