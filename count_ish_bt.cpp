/*
 * TODO
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <set>
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
    node(node *par) {
        parent = par;
        children = new node*[n];
        memset(children, 0, n * sizeof(node*));
        end = false;
    }
};

int *res;
void bt(int at, int cnt, vector<node*> nds) {
    if (at == n) {
        res[cnt]++;
        return;
    }
    // TODO: If size(nds) == 0, then quickly evaluate rest
    bt(at+1, cnt, nds);
    vector<node*> nxt(nds); // TODO: Throw out nodes that have no chance...
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

    node *root = new node(NULL);

    // TODO: Relabel vertices to maximize use of quick evaluation

    rep(i,0,m) {
        getline(cin, line);
        ss.str(line);
        ss.clear();
        int cur;
        set<int> path;
        while (ss >> cur) {
            path.insert(cur);
        }
        node *at = root;
        iter(it,path) {
            if (!at->children[*it]) {
                at->children[*it] = new node(at);
            }
            at = at->children[*it];
        }
        at->end = true;
    }

    res = new int[n+1];
    memset(res, 0, sizeof(int)*(n+1));
    bt(0, 0, vector<node*>(1,root));

    rep(i,0,n+1) {
        cout << res[i] << endl;
    }

    delete[] res;
    return 0;
}

