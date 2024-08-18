#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

auto sol = [](int n, auto v) {
	int acc = reduce(v.begin(), v.end());
	vector res(acc + 1, 0);
	auto check = [&](int x) {
		if (res[x]) return res[x];
		for (int i = 0; i < n;) {
			if (v[i] > x) { res[x] = -1; break; }
			int j = i, s = v[i];
			while (j + 1 < n && s + v[j + 1] <= x) s += v[++j];
			res[x]++;
			i = j + 1;
		}
		return res[x];
	};
	auto dnc = [&](const auto& self, int l, int r) -> void {
		if (check(l) == check(r) || l + 1 == r) {
			for (int i = l; i < r; i++) res[i] = res[l];
			return;
		}
		int mid = l + r >> 1;
		self(self, l, mid);
		self(self, mid, r);
	};
	dnc(dnc, 1, acc);
	return res;
};

int main() {
	fastio;
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	int q; cin >> q;
	while (q--) {
		int x; cin >> x;
		if (res[x] == -1) cout << "Impossible" << '\n';
		else cout << res[x] << '\n';
	}
}