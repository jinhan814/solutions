#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	string s; cin >> s;
	vector p(n + 1, 0);
	for (int i = 0; i < n; i++) p[i + 1] = p[i] + (s[i] & 1);

	auto query = [&](int l, int r) {
		int len = r - l + 1;
		int c = p[r] - p[l - 1];
		if (len & 1 || c & 1) return pair(-1, -1);

		auto check = [&](int i) {
			assert(l <= i && i + len / 2 - 1 <= r);
			return p[i + len / 2 - 1] - p[i - 1] >= c / 2;
		};

		int lo = l, hi = l + len / 2;
		if (check(lo) && check(hi)) return pair(lo, lo + len / 2 - 1);
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (check(lo) == check(mid)) lo = mid;
			else hi = mid;
		}
		if (!check(lo)) lo++;
		return pair(lo, lo + len / 2 - 1);
	};

	while (q--) {
		int l, r; cin >> l >> r;
		auto res = query(l, r);
		if (res.first == -1) cout << -1 << '\n';
		else cout << res.first << ' ' << res.second << '\n';
	}
}