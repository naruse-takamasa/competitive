#include <bitset/stdc++.h>
using namespace std;

template <typename T>
class BIT {
  public:
    BIT(int size) {
        BITTable.assign(++size, 0);
    }
    T sum(int k) {
        T res = 0;
        for (++k; k > 0; k -= k & -k) {
            res += BITTable[k];
        }
        return res;
    }
    T sum(int l, int r) {
        if (l == 0) return sum(r);
        return sum(r) - sum(l - 1);
    }
    void update(int k, T x) { // b[k] += x;
        for (++k; k < (int)BITTable.size(); k += k & -k) BITTable[k] += x;
    }
  private:
    vector<T> BITTable;
};
