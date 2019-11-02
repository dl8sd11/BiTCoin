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
#ifdef BTCd
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
const ll INF = 0x3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 102;

void GG(){cout<<"-1\n"; exit(0);}

ll n;
set<string> ing[MAXN];
ll id[MAXN], prc[MAXN];

struct Ans {
    ll mat;
    ll pc;
    ll dd;

    bool bter (const Ans &ans) const {
        if (mat != ans.mat) {
            return mat > ans.mat;
        }
        if (pc != ans.mat) {
            return pc < ans.pc;
        }
        if (dd != ans.dd) {
            return dd < ans.dd;
        }
        return false;
    }
} res;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> id[i];
        debug("tets");
        char c;
        cin >> c;
        string str;
        while (cin >> str) {
            debug(str);

            bool flag = false;
            REP (j, SZ(str)) {
                if (str[j] == ',') {
                    ing[i].insert(str.substr(0, j));
                    prc[i] = stoll(str.substr(j+1));
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
            ing[i].insert(str);
        }

        debug(id[i], ing[i], prc[i]);
    }

    set<string> ming;
    string in;
    while (cin >> in) {
        ming.insert(in);
    }

    res.mat = -1;
    REP (i, n) {
        int cnt = 0;
        if (ming == ing[i]) {
            cnt = INF;
        } else {
            for (auto v : ming) {
                cnt += ing[i].count(v);
            }
            debug(i, cnt);

        }

        Ans cur = {cnt, prc[i], id[i]};
        if (cur.bter(res)) {
            res = cur;
        }
    }

    cout << res.dd << " ";
    if (res.mat == INF) {
        cout << 9 << endl;
    } else if (res.mat != 0) {
        cout << 6 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
