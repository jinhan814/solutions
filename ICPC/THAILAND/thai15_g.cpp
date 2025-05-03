#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

auto sol = [](auto v) {
	const int n = v.size();
	const int sz = (int)sqrt(v.back()) + 10;
	auto mul = [](int& a, int b) { a = 1LL * a * b % mod; };
	vector s(sz + 1, !1);
	for (int i = 2; i * i <= sz; i++) {
		if (s[i]) continue;
		for (int j = i * i; j <= sz; j += i) s[j] = 1;
	}
	vector res(n, 1);
	for (int i = 2; i <= sz; i++) {
		if (s[i]) continue;
		auto x = 1LL * i;
		while (x <= 1.1e14 / i) {
			x *= i;
			auto it = lower_bound(v.begin(), v.end(), x);
			if (it == v.end()) break;
			mul(res[it - v.begin()], i);
		}
	}
	for (int i = 1; i < n; i++) mul(res[i], res[i - 1]);
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0LL);
	for (int i = 0; i < n; i++) cin >> v[i];
	vector t = v; sort(t.begin(), t.end());
	vector res = sol(t);
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(t.begin(), t.end(), v[i]);
		cout << "Case " << i + 1 << ": ";
		cout << res[it - t.begin()] << '\n';
	}
}