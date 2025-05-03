#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(2 * n, 0);
	for (int i = 0; i < 2 * n; i++) cin >> v[i];

	vector buc(0, array{ 0, 0 });
	for (int l = 0, r = 0; l < 2 * n; l = r) {
		while (r < 2 * n && v[l] >= v[r]) r++;
		buc.push_back({ l, r });
	}

	vector dp(buc.size(), vector(2 * n + 1, -1));
	auto dfs = [&](const auto& self, int i, int j) -> bool {
		if (j <= 0) return j == 0;
		if (i < 0) return 0;
		int& ret = dp[i][j];
		if (ret != -1) return ret; ret = 0;
		if (self(self, i - 1, j)) ret = 1;
		if (self(self, i - 1, j - (buc[i][1] - buc[i][0]))) ret = 1;
		return ret;
	};

	if (!dfs(dfs, buc.size() - 1, n)) return cout << -1 << '\n', 0;

	vector a(0, 0), b(0, 0);
	auto trace = [&](const auto& self, int i, int rem) -> void {
		if (i < 0) return;
		if (dfs(dfs, i - 1, rem - (buc[i][1] - buc[i][0]))) {
			self(self, i - 1, rem - (buc[i][1] - buc[i][0]));
			for (int j = buc[i][0]; j < buc[i][1]; j++) a.push_back(v[j]);
		}
		else {
			self(self, i - 1, rem);
			for (int j = buc[i][0]; j < buc[i][1]; j++) b.push_back(v[j]);
		}
	};
	trace(trace, buc.size() - 1, n);

	for (int x : a) cout << x << ' '; cout << '\n';
	for (int x : b) cout << x << ' '; cout << '\n';
}