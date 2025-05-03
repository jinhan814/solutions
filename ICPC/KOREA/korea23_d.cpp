#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct frac {
	frac(i64 a, i64 b = 1) : a(a), b(b) { norm(); }
	frac operator+ (const frac& x) const { return frac(a * x.b + x.a * b, b * x.b); }
	frac operator- (const frac& x) const { return frac(a * x.b - x.a * b, b * x.b); }
	frac operator* (const frac& x) const { return frac(a * x.a, b * x.b); }
	frac operator/ (const frac& x) const { return frac(a * x.b, b * x.a); }
	bool operator== (const frac& x) const { return a * x.b == x.a * b; }
	auto operator<=> (const frac& x) const { return a * x.b <=> x.a * b; }
	auto get() const { return pair(a, b); }
private:
	i64 a, b;
	void norm() { i64 g = gcd(a, b); a /= g; b /= g; }
};

auto sol = [](int n, string s) {
	// <expr> := ( <expr> <expr> <expr> ) | <num>
	auto rec = [&](const auto& self, auto& it) -> frac {
		if (it - s.begin() >= n) return 0;
		if (isdigit(*it)) return *it++ - 48;
		if (*it != '(') return 0;
		frac a = self(self, ++it);
		frac b = self(self, it);
		frac c = self(self, it);
		if (it == s.end() || *it++ != ')') return 0;
		if (a == 0 || b == 0 || c == 0) return 0;
		return a + b / c;
	};
	auto it = s.begin();
	auto res = rec(rec, it);
	if (it != s.end()) res = 0;
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s(n, 0);
	for (int i = 0; i < n; i++) cin >> s[i];
	auto [a, b] = sol(n, s).get();
	if (!a) cout << -1 << '\n';
	else cout << a << ' ' << b << '\n';
}