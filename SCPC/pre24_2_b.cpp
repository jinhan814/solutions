#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int kth(int k) const {
		int ret = 0;
		for (int i = 20; i >= 0; i--) {
			int j = ret | 1 << i;
			if (j <= sz && tree[j] < k) ret = j, k -= tree[j];
		}
		return ret + 1;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int q, auto v, auto qs) {
	vector idx(n, 0);
	iota(idx.begin(), idx.end(), 1);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return v[i] < v[j]; });
	fenwick tree(n);
	for (int i = 1; i <= n; i++) tree.update(i, 1);
	sort(qs.begin(), qs.end());
	i64 ret = 0, acc = 0;
	for (int i = 0, j = 0; i < q; i++) {
		while (acc < qs[i]) {
			int cnt = tree.query(n);
			i64 val = v[idx[j]];
			if (j) val -= v[idx[j - 1]];
			if (acc + cnt * val >= qs[i]) break;
			acc += cnt * val;
			tree.update(idx[j], -1);
			j++;
		}
		int cnt = tree.query(n);
		i64 val = (qs[i] - acc) % cnt;
		if (val == 0) val = cnt;
		ret += tree.kth(val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, q; cin >> n >> q;
		vector v(n + 1, 0LL);
		vector qs(q, 0LL);
		for (int i = 1; i <= n; i++) cin >> v[i];
		for (int i = 0; i < q; i++) cin >> qs[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, q, v, qs) << '\n';
	}
}