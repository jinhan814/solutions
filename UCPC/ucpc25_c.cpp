#include <bits/stdc++.h>
using namespace std;

auto gen_rand = [](int l, int r) {
	static mt19937 rd(0x814814);
	return uniform_int_distribution(l, r)(rd);
};

auto sol = [](int n, auto v) {
	auto f = [&](int x) {
		map c{ pair(0, 0) };
		for (int i = 0; i < n; i++) c[v[i] % x]++;
		int ret = 0;
		for (auto [a, b] : c) ret = max(ret, b);
		return ret;
	};
	int ret = f(2);
	for (int iter = 0; iter < 30; iter++) {
		int i = gen_rand(0, n - 1);
		int j = gen_rand(0, n - 1);
		int val = abs(v[i] - v[j]);
		for (int x = 2; x * x <= val; x++) {
			if (val % x) continue;
			while (val % x == 0) val /= x;
			ret = max(ret, f(x));
		}
		if (val > 1) ret = max(ret, f(val));
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	cout << sol(n, v) << '\n';
}