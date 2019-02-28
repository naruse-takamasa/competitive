#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

class UnionFind {
  public:
    explicit UnionFind(int _n) : n(_n) {
        par.resize(static_cast<unsigned long>(_n));
        rank.resize(static_cast<unsigned long>(_n));
        sizes.resize(static_cast<unsigned long>(_n));
        for (int i = 0; i < _n; i++) {
            par[i] = i;
            rank[i] = 0;
            sizes[i] = 1;
        }
    }
    int find(int a) {
        if (par[a] == a) return a;
        return par[a] = find(par[a]);
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    void unite(int a, int b) {
        link(find(a), find(b));
    }
    int size(int a) {
        return sizes[find(a)];
    }
    void view() {
        for (int i = 0; i < n; i++) {
            cout << " par" << "[" << i << "]=" << par[i] << ((i == n - 1) ? "\n" : ",");
        }
        for (int i = 0; i < n; i++) {
            cout << "size" << "[" << i << "]=" << sizes[i] << ((i == n - 1) ? "\n" : ",");
        }
        cout << endl;
    }
  private:
    void link(int a, int b) {
        if (same(a, b)) return;
        if (rank[a] > rank[b]) {
            par[b] = a;
            sizes[a] += sizes[b];
            sizes[b] = 0;
        } else {
            par[a] = b;
            if (rank[a] == rank[b]) rank[b]++;
            sizes[b] += sizes[a];
            sizes[a] = 0;
        }
    }
    int n;
    vector<int> par;
    vector<int> rank;
    vector<int> sizes;
};
