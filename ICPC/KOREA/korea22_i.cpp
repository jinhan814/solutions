#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	auto dfs = [&](const auto& self, int l, int r, int x) -> int {
		if (x > 3) return 4;
		if (l > r) return 0;
		if (s[l] == s[r]) return self(self, l + 1, r - 1, x);
		int r1 = self(self, l + 1, r, x + 1);
		int r2 = self(self, l, r - 1, x + 1);
		return min(r1, r2) + 1;
	};
	int res = dfs(dfs, 0, s.size() - 1, 0);
	if (res > 3) res = -1;
	cout << res << '\n';
}