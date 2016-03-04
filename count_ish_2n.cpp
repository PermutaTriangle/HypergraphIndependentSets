/*
 * This is an O(n 2^n) solution.
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
template <class T> int size(const T &x) { return x.size(); }
const int INF = 2147483647;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int n, m;
    ss >> n >> m;

    bool *valid = new bool[1<<n];
    rep(i,0,(1<<n)) {
        valid[i] = true;
    }

    rep(i,0,m) {
        getline(cin, line);
        ss.str(line);
        ss.clear();
        int mask = 0, cur;
        while (ss >> cur) {
            mask |= 1<<cur;
        }
        valid[mask] = false;
    }

    int *res = new int[n+1];
    memset(res, 0, sizeof(int)*(n+1));
    rep(i,0,(1<<n)) {
        if (valid[i]) {
            int t = i, cnt = 0;
            while (t) {
                cnt++;
                int b = t & (-t);
                if (!valid[i ^ b]) {
                    valid[i] = false;
                    break;
                }
                t ^= b;
            }
            if (valid[i])  {
                res[cnt]++;
            }
        }
    }

    rep(i,0,n+1) {
        cout << res[i] << endl;
    }

    delete[] valid;
    delete[] res;
    return 0;
}

