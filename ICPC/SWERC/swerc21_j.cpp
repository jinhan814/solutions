#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;

		auto divisor = [](int n) {
			vector res(0, 0);
			for (int i = 1; i * i <= n; i++) {
				if (n % i) continue;
				res.push_back(i);
				if (i * i != n) res.push_back(n / i);
			}
			return res;
		};

		auto check = [&](int x) {
			if ((n - 1) % x == 0 && (m - 1) % x == 0) return 1;
			if (n % x == 0 && (m - 2) % x == 0) return 1;
			if (m % x == 0 && (n - 2) % x == 0) return 1;
			return 0;
		};

		set res{ 1 };
		for (int x : divisor(n + m - 2)) if (check(x)) res.insert(x);
		if (~n & 1 || ~m & 1) res.insert(2);

		cout << res.size();
		for (int x : res) cout << ' ' << x;
		cout << '\n';
	}
}