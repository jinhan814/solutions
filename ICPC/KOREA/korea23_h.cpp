#include <bits/stdc++.h>
using namespace std;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] = max(tree[i], x);
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret = max(ret, tree[i]);
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, array{ 0, 0 });
	for (int i = 1; i <= n; i++) cin >> v[i][0];
	for (int i = 1; i <= n; i++) cin >> v[i][1];
	sort(v.begin() + 1, v.end());
	vector p(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		p[i] = p[i - 1] + max(v[i][0], v[i][1]);
	}
	fenwick tree(50'000);
	vector dp(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		dp[i] = tree.query(v[i][1]) + p[i - 1] + v[i][0] + v[i][1];
		tree.update(v[i][1], dp[i] - p[i]);
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		res = max(res, dp[i] + p[n] - p[i]);
	}
	cout << res << '\n';
}