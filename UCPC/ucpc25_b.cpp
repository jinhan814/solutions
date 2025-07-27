#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto sol = [](int n, int m, int k, auto v) {
	vector p(n + 1, 0LL);
	for (int i = 0; i < n; i++) p[i + 1] = p[i] + v[i] - k;
	vector c = p;
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	auto f = [&](i64 x) {
		i64 ret = 0;
		fenwick tree(c.size());
		for (int i = 1; i <= n; i++) {
			int a = lower_bound(c.begin(), c.end(), p[i - 1]) - c.begin() + 1;
			int b = upper_bound(c.begin(), c.end(), p[i] - x) - c.begin();
			tree.update(a, 1);
			ret += tree.query(b);
		}
		return ret;
	};
	auto g = [&](i64 x) {
		i64 ret = 0;
		fenwick t1(c.size()), t2(c.size());
		for (int i = 1; i <= n; i++) {
			int a = lower_bound(c.begin(), c.end(), p[i - 1]) - c.begin() + 1;
			int b = upper_bound(c.begin(), c.end(), p[i] - x) - c.begin();
			t1.update(a, 1);
			t2.update(a, p[i - 1]);
			ret += t1.query(b) * p[i] - t2.query(b);
		}
		return ret;
	};
	i64 lo = 0, hi = 1LL << 60;
	while (lo + 1 < hi) {
		i64 mid = lo + hi >> 1;
		if (f(mid) >= m) lo = mid;
		else hi = mid;
	}
	return lo * (m - f(hi)) + g(hi) + p[n] + i64(n) * k;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, m, k, v) << '\n';
}