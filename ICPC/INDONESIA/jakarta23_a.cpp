#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s[3];
	for (int i = 0; i < 3; i++) cin >> s[i];

	vector c(3, vector(3, 0));
	auto dfs = [&](const auto& self, int x, int y, int dep) -> string {
		if (dep == 3) return "";
		string res = "ZZZ";
		c[x][y] = 1;
		for (int d = 0; d < 8; d++) {
			int nx = x + "10001222"[d] - '1';
			int ny = y + "22100012"[d] - '1';
			if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
			if (c[nx][ny]) continue;
			res = min(res, self(self, nx, ny, dep + 1));
		}
		c[x][y] = 0;
		return s[x][y] + res;
	};

	string res = "ZZZ";
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) res = min(res, dfs(dfs, i, j, 0));
	cout << res << '\n';
}