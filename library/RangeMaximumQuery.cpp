#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class IntervalTree
{
  public:
	IntervalTree(int n)
	{
		size = 1;
		while (size < (unsigned int)n)
			size <<= 1;
		data.resize(2 * size - 1, 0);
	}
	void update(int indx, ll num)
	{
		indx += size - 1;
		data[indx] = num;
		while (indx)
		{
			indx = (indx - 1) / 2;
			data[indx] = max(data[2 * indx + 1], data[2 * indx + 2]);
		}
	}
	ll query(int a, int b, int k, int l, int r)
	{
		if (a >= r || b <= l)
			return 0;
		if (a <= l && b >= r)
			return data[k];
		return max(query(a, b, 2 * k + 1, l, (l + r) / 2), query(a, b, 2 * k + 2, (l + r) / 2, r));
	}
	ll query(int a, int b)
	{
		return query(a, b, 0, 0, size);
	}
	void look()
	{
		cerr << "===================================="
			 << "\n";
		int now = 1;
		for (int i = 0; i < (int)data.size(); i++)
		{
			cerr << data[i] << " ";
			if (i + 1 == now)
			{
				cerr << "\n";
				now += now + 1;
			}
		}
	}

  private:
	vector<ll> data;
	unsigned int size;
};