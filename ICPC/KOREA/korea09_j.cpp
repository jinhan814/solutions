#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : par(n + 1, -1) {}
	int find(int x) {
		return par[x] < 0 ? x : par[x] = find(par[x]);
	}
	bool merge(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return 0;
		return par[b] = a, 1;
	}
private:
	vector<int> par;
};

auto sol = [](int n, int m, const auto& e) -> vector<int> {
	vector res(n + 1, 0);
	for (auto [a, b, c] : e) {
		if (a > 1) continue;
		if (res[b] && res[b] != c) return {};
		res[b] = c;
	}

	map buc{ pair(0, vector(0, 0)) };
	for (int i = 2; i <= n; i++) buc[res[i]].push_back(i);
	for (auto [a, b] : buc) if (b.size() > 2) return {};

	union_find uf(n + 1 << 1);
	for (auto [a, b] : buc) if (b.size() == 2) {
		uf.merge(b[0] << 1, b[1] << 1 | 1);
		uf.merge(b[0] << 1 | 1, b[1] << 1);
	}
	for (auto [a, b, c] : e) {
		if (a == 1) continue;
		if (abs(res[a] - res[b]) == c) {
			uf.merge(a << 1, b << 1);
			uf.merge(a << 1 | 1, b << 1 | 1);
		}
		else if (res[a] + res[b] == c) {
			uf.merge(a << 1, b << 1 | 1);
			uf.merge(a << 1 | 1, b << 1);
		}
		else return {};
	}

	for (int i = 2; i <= n; i++) {
		if (uf.find(i << 1) == uf.find(i << 1 | 1)) return {};
		if (uf.find(i << 1) != uf.find(2) && uf.find(i << 1 | 1) != uf.find(2)) {
			uf.merge(i << 1, 2);
			uf.merge(i << 1 | 1, 3);
		}
		if (uf.find(i << 1) != uf.find(2)) res[i] = -res[i];
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		vector e(m, array<int, 3>{});
		for (auto& [a, b, c] : e) {
			cin >> a >> b >> c;
			if (a > b) swap(a, b);
		}
		auto res = sol(n, m, e);
		if (res.empty()) {
			cout << n << '\n';
			cout << "impossible" << '\n';
		}
		else {
			cout << n << '\n';
			for (int i = 1; i <= n; i++) cout << res[i] << ' ';
			cout << '\n';
		}
	}
}