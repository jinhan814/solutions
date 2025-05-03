#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto f = [](i64 a, i64 b) { // \sum_{i = 1}^{a}{\min(a, b - i)}
	i64 ret = a * a;
	if (b - a < a) ret -= (2 * a - b) * (2 * a - b + 1) / 2;
	return ret;
};

auto sol = [](i64 a, i64 b, i64 c) {
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	i64 r1 = a * (a - 1) / 2 - a / 2;
	i64 r2 = f(a, b) - min(a, b / 2);
	return (4 * r1 + 2 * r2) * 4;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c; cin >> a >> b >> c;
	cout << sol(a, b, c) << '\n';
}