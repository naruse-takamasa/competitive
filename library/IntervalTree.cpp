＃include<bits / stdc++.h>

    using namespace std;

template <typename T>
class IntervalTree
{
  public:
    using F = function<T(T, T)>;
    unsigned int size;
    vector<T> table;
    const F func;
    const T init;
    IntervalTree(int n, const F func, const T init) : func(func), init(init)
    {
        size = 1;
        while ((int)size < n)
            size <<= 1;
        table.assign(2 * size, init);
    }
    void set(int k, T &x)
    {
        table[size + k] = x;
    }
    void build()
    {
        for (int i = size - 1; i >= 0; --i)
        {
            table[i] = func(table[i * 2], table[i * 2 + 1]);
        }
    }
    void update(int k, const T &x)
    {
        k += size;
        table[k] = x;
        while (k >>= 1)
        {
            table[k] = func(table[k * 2], table[k * 2 + 1]);
        }
    }
    T query(int a, int b)
    {
        T L = init, R = init;
        for (a += size, b += size; a < b; a >>= 1, b >>= 1)
        {
            if (a & 1)
                L = func(L, table[a++]);
            if (b & 1)
                R = func(table[--b], R);
        }
        return func(L, R);
    }
    T operator[](const int k) const
    {
        return table[k + size];
    }
};