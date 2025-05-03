#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, pair(0, 0));
	vector mx(1 << 20, -1), mn(1 << 20, 1 << 20);
	for (auto& [l, r] : v) {
		cin >> l >> r;
		mx[l] = max(mx[l], r);
		mn[r] = min(mn[r], l);
	}
	sort(v.begin(), v.end());
	auto query = [&](int l, int r) {
		if (binary_search(v.begin(), v.end(), pair(l, r))) return 1;
		if (mx[l] >= r && mn[r] <= l) return 2;
		return -1;
	};
	int q; cin >> q;
	while (q--) {
		int l, r; cin >> l >> r;
		cout << query(l, r) << '\n';
	}
}