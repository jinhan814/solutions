#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;

		auto get_divisor = [](int n) {
			vector res(0, 0);
			for (int i = 1; i * i <= n; i++) {
				if (n % i) continue;
				res.push_back(i);
				if (i * i != n) res.push_back(n / i);
			}
			return res;
		};

		auto calc = [](int n) {
			int a = 0, b = 1 << 30;
			for (int i = 1; i * i <= n; i++) {
				if (n % i) continue;
				int j = n / i;
				if (gcd(i, j) == 1) a = i, b = j;
			}
			return pair(a, b);
		};

		int a = 0, b = 1 << 30;
		for (int g : get_divisor(n)) {
			if (g == n) continue;
			auto [ca, cb] = calc(n / g - 1);
			if (b - a > g * (cb - ca)) a = g * ca, b = g * cb;
		}
		cout << a << ' ' << b << '\n';
	}
}