#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	auto rec = [&](const auto& self, int dep, auto v) -> int {
		if (dep > k) return -1;
		int res = 0;
		for (int i = 0; i < n; i++) {
			res += a[i] == v[i];
		}
		for (int i = 0; i < n; i++) {
			auto nv = v;
			rotate(nv.begin() + i, nv.begin() + i + 1, nv.end());
			nv[n - 1] = 0;
			res = max(res, self(self, dep + 1, nv));
		}
		for (int i = 0; i < n; i++) {
			auto nv = v;
			rotate(nv.begin() + i, nv.end() - 1, nv.end());
			nv[i] = 0;
			res = max(res, self(self, dep + 1, nv));
		}
		return res;
	};
	cout << rec(rec, 0, b) << '\n';
}