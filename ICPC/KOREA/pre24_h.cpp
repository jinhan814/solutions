#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto v) {
	auto check = [&](int mask) -> bool {
		auto f = [&](int x) { return x < 1 || x > 13 ? 1 : (mask |= 1 << x, 0); };
		if (f(v[2])) return 0;
		if (f(v[3])) return 0;
		if (f(v[6])) return 0;
		if (f(v[7])) return 0;
		if (f(v[1] - v[7])) return 0;
		if (f(v[5] - v[3])) return 0;
		int a = v[0] - (v[5] - v[3]) - v[6];
		int b = v[4] - (v[1] - v[7]) - v[2];
		if (a != b || f(a)) return 0;
		return mask + 2 >> 14;
	};
	auto rec = [&](const auto& self, int dep, int mask) -> int {
		if (dep == 6) return check(mask);
		int res = 0;
		for (int x = 1; x <= 13; x++) {
			if (mask >> x & 1) continue;
			v["312120"[dep] - '0'] -= x;
			v["455667"[dep] - '0'] -= x;
			res += self(self, dep + 1, mask | 1 << x);
			v["312120"[dep] - '0'] += x;
			v["455667"[dep] - '0'] += x;
		}
		return res;
	};
	return rec(rec, 0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(8, 0);
	for (int i = 0; i < 8; i++) cin >> v[i];
	cout << sol(v) << '\n';
}