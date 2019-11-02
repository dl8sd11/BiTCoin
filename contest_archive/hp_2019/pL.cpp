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
const int MAXN = 102;

void GG(){cout<<"-1\n"; exit(0);}


struct edge{
	int u,v;
	bool is_bridge;
	edge(int u=0,int v=0):u(u),v(v),is_bridge(0){}
};
std::vector<edge> E;
std::vector<int> G[MAXN];// 1-base
int low[MAXN],vis[MAXN],Time;
int bcc_id[MAXN],bridge_cnt,bcc_cnt;// 1-base
int st[MAXN],top;//BCC用 
inline void add_edge(int u,int v){
	G[u].push_back(E.size());
	E.push_back(edge(u,v));
	G[v].push_back(E.size());
	E.push_back(edge(v,u));
}
void dfs(int u,int re=-1){//u當前點，re為u連接前一個點的邊 
    debug(u);
	int v;
	low[u]=vis[u]=++Time;
	st[top++]=u;
	for(size_t i=0;i<G[u].size();++i){
		int e=G[u][i];v=E[e].v;
		if(!vis[v]){
			dfs(v,e^1);//e^1反向邊 
			low[u]=std::min(low[u],low[v]);
			if(vis[u]<low[v]){
				E[e].is_bridge=E[e^1].is_bridge=1;
				++bridge_cnt;
			}
		}else if(vis[v]<vis[u]&&e!=re)
			low[u]=std::min(low[u],vis[v]);
	}
	if(vis[u]==low[u]){//處理BCC
		++bcc_cnt;// 1-base
		do bcc_id[v=st[--top]]=bcc_cnt;//每個點所在的BCC
		while(v!=u);
	}
}
inline void bcc_init(int n){
	Time=bcc_cnt=bridge_cnt=top=0;
	E.clear();
	for(int i=1;i<=n;++i){
		G[i].clear();
		vis[i]=0;
		bcc_id[i]=0;
	}
}

int n;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    bcc_init(n);


    REP (i, n) {
        int v;
        cin >> v;
        v++;
        int sz;
        cin >> sz;
        REP (j, sz) {
            int u;
            cin >> u;
            u++;
            debug(u, v);
            if (v > u) {
                add_edge(u, v);
            }
        }
    }

    REP1 (i, n) {
        if (!vis[i]) {
            debug(i);
            dfs(i);
        }
    }

    debug(bridge_cnt);
    vector<pair<int,int>> ans;
    for (auto v : E) {
        debug(v.u, v.v, v.is_bridge);
        if (v.is_bridge) {
            pair<int,int> cur = {v.u-1, v.v-1};
            if (cur.X > cur.Y) {
                swap(cur.X, cur.Y);
            }
            ans.emplace_back(cur);
        }
    }
    debug(ans);

    SORT_UNIQUE(ans);

    cout << SZ(ans) << endl;
    for (auto v : ans) {
        cout << v.X << " " << v.Y << endl;
    }

    return 0;
}
