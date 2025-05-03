#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct ds {
	void push(i64 x) { v.push_back(x - bias); }
	void update(int i, i64 x) { i = v.size() - i, v[i] = min(v[i], x - bias); }
	void shift(i64 x) { bias += x; }
	int size() const { return v.size(); }
	i64 operator[](int i) const { return v[v.size() - i] + bias; }
private:
	i64 bias;
	vector<i64> v;
};

auto sol = [](int n, i64 w, const auto& par, const auto& cost, const auto& buc) {
	int res = 0;
	vector adj(n + 1, vector(0, 0));
	for (int i = n; i >= 2; i--) {
		adj[par[i]].push_back(i);
		for (int l = 0, r = 0; l < buc[i].size(); l++) {
			while (r < buc[i].size() && buc[i][r] - buc[i][l] <= w) r++;
			res = max(res, r - l);
		}
	}
	vector dp(n + 1, ds{});
	for (int i = n; i >= 1; i--) {
		if (adj[i].size()) {
			int opt = adj[i][0];
			for (int j : adj[i]) {
				if (dp[opt].size() < dp[j].size()) opt = j;
			}
			for (int j : adj[i]) {
				if (j == opt) continue;
				for (int x = 1; x <= dp[j].size(); x++) {
					if (dp[j][x] > w) continue;
					res = max(res, x);
					while (1) {
						int y = res + 1 - x;
						if (y < 0 || y > dp[opt].size()) break;
						if (dp[opt][y] + dp[j][x] > w) break;
						res++;
					}
				}
				for (int x = 1; x <= dp[j].size(); x++) {
					dp[opt].update(x, dp[j][x]);
				}
			}
			for (int j = 0; j < buc[i].size(); j++) {
				int x = buc[i].size() - j;
				if (cost[i] - buc[i][j] > w) continue;
				res = max(res, x);
				while (1) {
					int y = res + 1 - x;
					if (y < 0 || y > dp[opt].size()) break;
					if (dp[opt][y] + cost[i] - buc[i][j] > w) break;
					res++;
				}
			}
			dp[opt].shift(cost[i]);
			swap(dp[i], dp[opt]);
		}
		for (int j = buc[i].size() - 1; j >= 0; j--) {
			dp[i].push(buc[i][j]);
		}
	}
	return res;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 w; cin >> w;
	vector par(n + 1, 0);
	vector cost(n + 1, 0LL);
	vector buc(n + 1, vector(0, 0LL));
	for (int i = 2; i <= n; i++) {
		cin >> par[i] >> cost[i];
		int k; cin >> k;
		buc[i].resize(k);
		for (i64& x : buc[i]) cin >> x;
	}
	cout << sol(n, w, par, cost, buc) << '\n';
}