#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b, auto v) {
	sort(v.begin(), v.end());
	auto f = [&](int m, int x) {
		int res = 0;
		for (int i = 1, j = 0; i <= n; i++) {
			int p = a * i;
			if (i > m) p += x * (b - i + m);
			while (j < n && v[j] < p) j++;
			if (j < n) res++, j++;
		}
		return res;
	};
	int res = 0;
	for (int m = 0; m <= n; m++) {
		for (int x = 0; x < a; x++) {
			int val = f(m, x);
			res = max(res, val);
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int res = sol(n, a, b, v);
	cout << res << '\n';
}