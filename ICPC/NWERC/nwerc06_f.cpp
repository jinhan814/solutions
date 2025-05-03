#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector idx(n, 0);
	iota(idx.begin(), idx.end(), 0);
	while (idx.size()) {
		int mx = -1;
		for (int i : idx) mx = max(mx, v[i]);
		rotate(idx.begin(), idx.begin() + 1, idx.end());
		if (v[idx.back()] != mx) continue;
		if (idx.back() == m) return n - idx.size() + 1;
		idx.pop_back();
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << sol(n, m, v) << '\n';
	}
}