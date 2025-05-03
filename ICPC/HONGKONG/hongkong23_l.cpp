#include <bits/stdc++.h>
using namespace std;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, int x) {
		for (++i; i <= sz; i += i & -i) tree[i] += x;
	}
	int query(int i) const {
		int ret = 0;
		for (++i; i; i -= i & -i) ret += tree[i];
		return ret;
	}
	int query(int l, int r) const {
		return query(r) - query(l - 1);
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](int n, int m, int k, auto a, auto b, auto qu) -> bool {
	vector c(n, 0);
	for (int i = 0, p = 0; i < n; i++) {
		if (p < b.size() && a[i] == b[p]) p++;
		else c[i] = 1;
		if (i == n - 1 && p < b.size()) return 0;
	}

	vector idx(0, 0);
	for (int i = 0; i < n; i++) if (c[i]) idx.push_back(i);
	sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] > a[j]; });

	vector buc(n, 0);
	for (int i = 0; i < n; i++) buc[i] = i;
	sort(buc.begin(), buc.end(), [&](int i, int j) { return a[i] > a[j]; });

	multiset ms(qu.begin(), qu.end());
	set s{ -1, n };
	fenwick tree(n);
	for (int j = 0; int i : idx) {
		while (j < n && a[buc[j]] > a[i]) {
			if (!tree.query(buc[j], buc[j])) s.insert(buc[j]);
			j++;
		}
		int pos_l = *prev(s.lower_bound(i)) + 1;
		int pos_r = *s.lower_bound(i) - 1;
		int cnt = pos_r - pos_l + 1 - tree.query(pos_l, pos_r);
		if (ms.empty() || *ms.begin() > cnt) return 0;
		ms.erase(prev(ms.upper_bound(cnt)));
		tree.update(i, 1);
	}
	return 1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m, k; cin >> n >> m >> k;
		vector a(n, 0), b(m, 0), l(k, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < m; i++) cin >> b[i];
		for (int i = 0; i < k; i++) cin >> l[i];
		bool res = sol(n, m, k, a, b, l);
		cout << (res ? "YES" : "NO") << '\n';
	}
}