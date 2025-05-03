#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, 1LL << 60) {}
	void update(int i, i64 x) {
		tree[--i |= sz] = x;
		while (i >>= 1) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
	}
	i64 query(int l, int r) const {
		i64 ret = 1LL << 60;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = min(ret, tree[l++]);
			if (~r & 1) ret = min(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

auto normalize = [](int n, auto buc) {
	vector dp(n + 1, 0);
	for (auto [a, b] : buc) dp[b] = max(dp[b], a);
	vector res(0, array{ 0, 0 });
	for (int i = 1; i <= n; i++) {
		if (!dp[i]) continue;
		if (res.size() && res.back()[0] >= dp[i]) continue;
		res.push_back({ dp[i], i });
	}
	return res;
};

auto sol = [](int n, auto v, auto buc) {
	buc = normalize(n, buc);
	segtree tree(n);
	for (int i = 1; i <= n; i++) {
		int lo = -1, hi = buc.size();
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (buc[mid][1] < i) lo = mid;
			else hi = mid;
		}
		i64 dp = v[i];
		if (lo != -1) dp += tree.query(buc[lo][0], buc[lo][1]);
		tree.update(i, dp);
	}
	auto [l, r] = buc.back();
	return tree.query(l, r);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n + 1, 0);
	vector buc(m, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (auto& [a, b] : buc) cin >> a >> b;
	cout << sol(n, v, buc) << '\n';
}