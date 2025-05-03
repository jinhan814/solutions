#include <bits/stdc++.h>
using namespace std;

auto sol(int n, int m) {
	vector res(n, vector(m, 0));
	int p = 0;
	auto f = [&](int i) { for (int j = 1; j < m; j += 2) res[i][j - 1] = res[i][j] = ++p; };
	auto g = [&](int i) { for (int j = 0; j < m; j++) res[i][j] = res[i + 1][j] = ++p; };
	if (m & 1) {
		m--;
		for (int i = 1; i < n; i += 2) res[i - 1][m] = res[i][m] = ++p;
	}
	if (n % 5 == 0) {
		for (int i = 0; i < n; i += 5) g(i), g(i + 3);
	}
	else if (n % 5 == 1) {
		f(0);
		for (int i = 1; i < n; i += 5) g(i), g(i + 3);
	}
	else if (n % 5 == 2) {
		f(0), f(n - 1);
		for (int i = 1; i < n - 1; i += 5) g(i), g(i + 3);
	}
	else if (n % 5 == 3) {
		f(0);
		for (int i = 1; i < n - 2; i += 5) g(i), g(i + 3);
		g(n - 2);
	}
	else if (n % 5 == 4) {
		g(0);
		for (int i = 2; i < n - 2; i += 5) g(i), g(i + 3);
		g(n - 2);
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	auto res = sol(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << res[i][j] << ' ';
		cout << '\n';
	}
}