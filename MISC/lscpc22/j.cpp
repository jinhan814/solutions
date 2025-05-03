#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t; cin >> s >> t;
	int m; cin >> m;

	auto get = [&](const auto& s) {
		vector res(26, 0);
		for (int i = 0, p = 1; i < s.size(); i++) {
			res[s[i] - 'a'] = add(res[s[i] - 'a'], p);
			p = mul(p, m);
		}
		return res;
	};

	auto a = get(s), b = get(t);
	int res = 0;
	for (int i = 0; i < 26; i++) res = add(res, mul(a[i], b[i]));
	cout << res << '\n';
}