#include <bits/stdc++.h>
using namespace std;

auto get_fail = [](string s) {
	const int n = s.size();
	vector f(n, 0);
	for (int i = 1, j = 0; i < s.size(); i++) {
		while (j && s[i] != s[j]) j = f[j - 1];
		if (s[i] == s[j]) f[i] = ++j;
	}
	return f;
};

auto kmp = [](string s, string t) {
	const int n = s.size(), m = t.size();
	vector res(0, 0), f = get_fail(t);
	for (int i = 0, j = 0; i < n; i++) {
		while (j && s[i] != t[j]) j = f[j - 1];
		if (s[i] == t[j] && ++j == m) {
			res.push_back(i - m + 1);
			j = f[j - 1];
		}
	}
	return res;
};

auto calc = [](int n, int a, int b, int c) {
	auto f = [&](int a, int b) {
		return min(abs(a - b), n - abs(a - b));
	};
	int r1 = f(a, b) + f(a, c);
	int r2 = f(b, a) + f(b, c);
	int r3 = f(c, a) + f(c, b);
	return min({ r1, r2, r3 });
};

auto sol = [](string a, string b, string c) {
	const int n = a.size();
	int res = 1 << 30;
	for (int p = 0; p < n; p++) {
		string t(n, 0);
		for (int i = 0; i < n; i++) {
			if (a[i] == b[i]) t[i] = '#';
			else t[i] = 3 * 'B' - a[i] - b[i];
		}
		for (int x : kmp(c + c, t)) {
			res = min(res, calc(n, 0, p, x));
		}
		rotate(b.begin(), b.begin() + 1, b.end());
	}
	if (res >> 30) res = -1;
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string a, b, c; cin >> a >> b >> c;
	cout << sol(a, b, c) << '\n';
}