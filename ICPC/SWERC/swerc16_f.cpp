#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, root; cin >> n;
	vector p(n + 1, 0), a(n + 1, 0), b(n + 1, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		cin >> p[i] >> a[i] >> b[i];
		if (p[i] == -1) root = i;
		else adj[p[i]].push_back(i);
	}

	vector in(n + 1, 0), out(n + 1, 0);
	{
		int ord = 0;
		auto dfs = [&](const auto& self, int cur) -> void {
			in[cur] = ++ord;
			for (int nxt : adj[cur]) self(self, nxt);
			out[cur] = ord;
		};
		dfs(dfs, root);
	}

	int sz = 1 << 17;
	vector tree(sz << 1, vector(0, pair(0, 0LL)));
	for (int i = 1; i <= n; i++) tree[in[i] - 1 | sz].push_back({ a[i], b[i] });
	for (int i = sz - 1; i; i--) {
		const auto& a = tree[i << 1];
		const auto& b = tree[i << 1 | 1];
		int pa = 0, pb = 0;
		while (pa < a.size() && pb < b.size()) {
			if (a[pa].first < b[pb].first) tree[i].push_back(a[pa++]);
			else tree[i].push_back(b[pb++]);
		}
		while (pa < a.size()) tree[i].push_back(a[pa++]);
		while (pb < b.size()) tree[i].push_back(b[pb++]);
	}
	for (auto& v : tree) {
		for (int i = 1; i < v.size(); i++) v[i].second += v[i - 1].second;
	}

	auto calc = [](const auto& v, int lim) {
		if (v[0].first >= lim) return 0LL;
		int lo = 0, hi = v.size();
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (v[mid].first < lim) lo = mid;
			else hi = mid;
		}
		return v[lo].second;
	};

	auto query = [&](int l, int r, int lim) {
		auto res = 0LL;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) res += calc(tree[l++], lim);
			if (~r & 1) res += calc(tree[r--], lim);
		}
		return res;
	};

	for (int i = 1; i <= n; i++) {
		auto res = query(in[i] + 1, out[i], a[i]);
		cout << res << '\n';
	}
}