#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Convex hull optimization that returns maximal ax + b for a given x
 * Requires that the slopes of the inserted lines and queried points are nondecreasing
 * 
 */
class convex_hull_optimization {
    private:
    vector<long long> a, b;
    vector<int> id;
    int ptr = 0;
 
    int bad(int l1, int l2, long long _a, long long _b) {
      if ((a[l1] == _a) && (b[l1] == _b)) return 1;
      return ((_b - b[l1]) * (a[l1] - a[l2]) > (b[l2] - b[l1]) * (a[l1] - _a));
    }
    
    public:
    void add(long long _a, long long _b, int _id) {
        while ((int) a.size() >= 2 && bad((int) a.size() - 1, (int) a.size() - 2, _a, _b)) {
            a.pop_back();
            b.pop_back();
            id.pop_back();
        }
        a.push_back(_a);
        b.push_back(_b);
        id.push_back(_id);
    }
 
    pair<int, long long> query(long long x) {
        if (ptr >= (int) a.size()) {
            ptr = (int) a.size() - 1;
        }
        while (ptr < (int) a.size() - 1 && a[ptr + 1] * x + b[ptr + 1] >= a[ptr] * x + b[ptr]) {
            ptr++;
        }
        return {id[ptr], a[ptr] * x + b[ptr]};
    }
};
