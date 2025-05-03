#include <bits/stdc++.h>
using namespace std;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1, 1) {
		for (int i = 1; i <= sz; i++) {
			int j = i + (i & -i);
			if (j <= sz) tree[j] += tree[i];
		}
	}
	void update(int i, int x) {
		for (++i; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (++i; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int kth(int k) const {
		int res = 0;
		for (int i = 17; i >= 0; i--) {
			int j = res | 1 << i;
			if (j <= sz && tree[j] < k) k -= tree[res = j];
		}
		return res;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, auto v) {
	swap(v[0], v[v[n - 1] % (n - 1)]);
	vector res(n, 0);
	fenwick tree(n);
	for (int i = 0, p = 0; i < n; i++) {
		res[p] = v[i];
		tree.update(p, -1);
		if (i == n - 1) break;
		int k = (tree.query(p) + v[i]) % (n - 1 - i);
		if (k == 0) k = n - 1 - i;
		p = tree.kth(k);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	for (int x : res) cout << x << '\n';
}