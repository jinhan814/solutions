#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector g(9, vector(9, 0));
	while (n--) {
		int a, b; cin >> a >> b;
		g[a - 1][b - 1] = 1;
	}

	auto conv = [&](int s) {
		vector res(9, 0);
		for (int i = 0; i < 9; i++) res[i] = s % 3, s /= 3;
		return res;
	};

	auto rev = [&](auto res) {
		int s = 0;
		for (int i = 8; i >= 0; i--) s = 3 * s + res[i];
		return s;
	};

	auto is_leaf = [&](auto res) -> bool {
		for (int i = 0; i < 3; i++) {
			if (res[3 * i] == 0) continue;
			int f = 1;
			for (int j = 0; j < 3; j++) if (res[3 * i] != res[3 * i + j]) f = 0;
			if (f) return 1;
		}
		for (int j = 0; j < 3; j++) {
			if (res[j] == 0) continue;
			int f = 1;
			for (int i = 0; i < 3; i++) if (res[j] != res[3 * i + j]) f = 0;
			if (f) return 1;
		}
		if (res[0] && res[0] == res[4] && res[4] == res[8]) return 1;
		if (res[2] && res[2] == res[4] && res[4] == res[6]) return 1;
		return 0;
	};
 
	vector dp(19'683, -1);
	auto dfs = [&](const auto& self, int s, int turn) -> int { // 0, 1, 2 : win, draw, lose
		int& ret = dp[s];
		if (ret != -1) return ret;
		vector res(3, 0), v = conv(s);
		for (int i = 0; i < 9; i++) {
			if (v[i]) continue;
			int f = 1;
			for (int j = 0; j < 9; j++) if (g[j][i] && !v[j]) f = 0;
			if (!f) continue;
			v[i] = turn;
			if (is_leaf(v)) res[2] = 1;
			else res[self(self, rev(v), 3 - turn)] = 1;
			v[i] = 0;
		}
		if (res[0] == 0 && res[1] == 0 && res[2] == 0) return ret = 1;
		return ret = res[2] ? 0 : res[1] ? 1 : 2;
	};
 
	int res = dfs(dfs, 0, 1);
	cout << "XEO"[res] << '\n';
}