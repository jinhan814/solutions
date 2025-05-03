#include <bits/stdc++.h>
using namespace std;

auto count_days = [](int y, int m, int d) {
	auto leap = [](int y) { return y % 4 == 0 && (y % 100 || y % 400 == 0); };
	auto count_leaps = [](int y) { return y / 4 - y / 100 + y / 400; };
	vector month{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int res = y * 365 + count_leaps(y - 1);
	for (int i = 1; i < m; i++) res += month[i];
	if (m > 2 && leap(y)) res++;
	return res + d - 1;
};

auto conv = [](string a, string b) {
	int y = stoi(a.substr(0, 4));
	int m = stoi(a.substr(5, 2));
	int d = stoi(a.substr(8, 2));
	int hh = stoi(b.substr(0, 2));
	int mm = stoi(b.substr(3, 2));
	int ss = stoi(b.substr(6, 2));
	return count_days(y, m, d) + (hh * 3600 + mm * 60 + ss) / 86400.;
};

auto sol = [](int n, auto a, auto b, auto v) {
	if (n == 0) return 0;
	double t = conv(a[n - 1], b[n - 1]);
	double s1 = 0;
	double s2 = 0;
	for (int i = 0; i < n; i++) {
		double x = pow(0.5, (t - conv(a[i], b[i])) / 365);
		double y = pow(0.9, n - 1 - i);
		double p = max(x, y);
		s1 += p * v[i];
		s2 += p;
	}
	return int(s1 / s2 + 0.5);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, string{}), b(n, string{});
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> v[i];
	cout << sol(n, a, b, v) << '\n';
}