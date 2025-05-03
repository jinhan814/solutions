#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }

auto vectors(const int n, auto&& val) { return vector(n, val); }
auto vectors(const int n, auto&&... args) { return vector(n, vectors(args...)); }

auto is_divisible = [](string n, i64 k) {
	for (char c : n) k /= gcd(k, c - 48);
	return k == 1;
};

auto num_with_zero = [](string s) {
	auto dp = vectors(s.size(), 2, 3, -1);
	auto rec = [&](const auto& self, int i, int f1, int f2) -> int {
		if (i < 0) return f2 == 2;
		int& ret = dp[i][f1][f2];
		if (ret != -1) return ret; ret = 0;
		for (int x = 0; x < 10; x++) {
			if (!f1 && x > s[s.size() - 1 - i] - 48) break;
			int nf1 = f1 || (x < s[s.size() - 1 - i] - 48);
			int nf2 = f2 == 0 ? (x ? 1 : 0) : f2 == 1 ? (x ? 1 : 2) : 2;
			int res = self(self, i - 1, nf1, nf2);
			ret = add(ret, res);
		}
		return ret;
	};
	return rec(rec, s.size() - 1, 0, 0);
};

auto num_without_zero = [](string s, i64 k) {
	int a = 0, b = 0, c = 0, d = 0;
	while (k % 2 == 0) a++, k /= 2;
	while (k % 3 == 0) b++, k /= 3;
	while (k % 5 == 0) c++, k /= 5;
	while (k % 7 == 0) d++, k /= 7;
	if (k > 1) return 0;
	auto dp = vectors(s.size(), 2, 2, a + 1, b + 1, c + 1, d + 1, -1);
	auto rec = [&](const auto& self, int i, int f1, int f2, int a, int b, int c, int d) -> int {
		if (i < 0) return !(a | b | c | d);
		int& ret = dp[i][f1][f2][a][b][c][d];
		if (ret != -1) return ret; ret = 0;
		if (!f2) ret = self(self, i - 1, 1, 0, a, b, c, d);
		for (int x = 1; x < 10; x++) {
			if (!f1 && x > s[s.size() - 1 - i] - 48) break;
			int nf1 = f1 || x < s[s.size() - 1 - i] - 48;
			int nf2 = f2 || x;
			int na = a, nb = b, nc = c, nd = d, t = x;
			while (t % 2 == 0) na ? na-- : 0, t /= 2;
			while (t % 3 == 0) nb ? nb-- : 0, t /= 3;
			while (t % 5 == 0) nc ? nc-- : 0, t /= 5;
			while (t % 7 == 0) nd ? nd-- : 0, t /= 7;
			int res = self(self, i - 1, nf1, nf2, na, nb, nc, nd);
			ret = add(ret, res);
		}
		return ret;
	};
	return rec(rec, s.size() - 1, 0, 0, a, b, c, d);
};

auto sol = [](i64 k, string l, string r) {
	int l1 = num_with_zero(l);
	int r1 = num_with_zero(r);
	int l2 = num_without_zero(l, k);
	int r2 = num_without_zero(r, k);
	int res = is_divisible(l, k);
	res = add(res, sub(r1, l1));
	res = add(res, sub(r2, l2));
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 k; cin >> k;
	string l, r; cin >> l >> r;
	cout << sol(k, l, r) << '\n';
}