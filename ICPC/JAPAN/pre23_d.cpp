#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (1) {
		int n; cin >> n;
		if (!n) break;
		string s; cin >> s;
		i128 mask = 0;
		for (int i = 0; i <= n; i++) {
			if (s[i] == 'x') continue;
			mask |= i128(1) << i;
		}
		auto rec = [&](const auto& self, int dep, int lim, int rem, i128 s) -> int {
			if ((mask & s) == mask) return dep;
			if (dep == 6) return 7;
			int ret = 7;
			for (int i = lim; i <= rem; i++) {
				int res = self(self, dep + 1, i, rem - i, s | s << i);
				ret = min(ret, res);
			}
			return ret;
		};
		cout << rec(rec, 0, 1, n, 1) << '\n';
	}
}