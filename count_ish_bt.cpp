/*
 * TODO
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
template <class T> int size(const T &x) { return x.size(); }
const int INF = 2147483647;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

int n;
struct node {
    node *parent;
    node **children;
    bool end;
    int mxchild;
    node(node *par) {
        parent = par;
        children = new node*[n];
        memset(children, 0, n * sizeof(node*));
        end = false;
        mxchild = -1;
    }
};

ll **nck, *res;
void bt(int at, int cnt, vector<node*> nds) {
    int idx = 0;
    while (idx < size(nds)) {
        if (nds[idx]->mxchild < at) {
            swap(nds[idx], nds[size(nds)-1]);
            nds.pop_back();
        } else {
            idx++;
        }
    }

    if (size(nds) == 0) {
        int left = n-at;
        for (int add = 0; add <= left; add++) {
            res[cnt + add] += nck[left][add];
        }
        return;
    }

    bt(at+1, cnt, nds);
    vector<node*> nxt(nds);
    rep(i,0,size(nds)) {
        if (nds[i]->children[at]) {
            if (nds[i]->children[at]->end) {
                return;
            }
            nxt.push_back(nds[i]->children[at]);
        }
    }
    bt(at+1, cnt+1, nxt);
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int m;
    ss >> n >> m;

    nck = new ll*[n+1];
    rep(i,0,n+1) {
        nck[i] = new ll[i+1];
        nck[i][0] = nck[i][i] = 1;
        rep(j,1,i) {
            nck[i][j] = nck[i-1][j-1] + nck[i-1][j];
        }
    }

    node *root = new node(NULL);
    vector<ii> ecnt(n);
    rep(i,0,n) ecnt[i].second = i;
    vector<set<int> > paths;
    rep(i,0,m) {
        getline(cin, line);
        ss.str(line);
        ss.clear();
        int cur;
        set<int> path;
        while (ss >> cur) {
            path.insert(cur);
        }
        paths.push_back(path);
        iter(it,path) {
            ecnt[*it].first++;
        }
    }

    sort(ecnt.rbegin(), ecnt.rend());
    // sort(ecnt.begin(), ecnt.end());
    vi newidx(n);
    rep(i,0,size(ecnt)) {
        newidx[ecnt[i].second] = i;
    }

    rep(i,0,size(paths)) {
        set<int> path;
        iter(it,paths[i]) {
            path.insert(newidx[*it]);
        }
        node *at = root;
        iter(it,path) {
            if (!at->children[*it]) {
                at->children[*it] = new node(at);
            }
            at->mxchild = max(at->mxchild, *it);
            at = at->children[*it];
        }
        at->end = true;
    }

    // TODO: Relabel vertices to maximize use of quick evaluation

    res = new ll[n+1];
    memset(res, 0, sizeof(ll)*(n+1));
    bt(0, 0, vector<node*>(1,root));

    rep(i,0,n+1) {
        cout << res[i] << endl;
    }

    rep(i,0,n+1) {
        delete[] nck[i];
    }
    delete[] nck;
    delete[] res;
    return 0;
}

