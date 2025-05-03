#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int k, const auto& v) {
	double res = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		double p1 = (n - i) * (i + 1.) / (n * (n + 1) / 2);
		double p2 = (n - j) * (j + 1.) / (n * (n + 1) / 2);
		double p = p1 * p2;
		double t = pow(1 - 2 * p, k);
		if (v[i][j]) res += (1 + t) / 2;
		else res += (1 - t) / 2;
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, k; cin >> n >> k;
		vector v(n, vector(n, 0));
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> v[i][j];
		auto res = sol(n, k, v);
		cout << fixed << setprecision(5);
		cout << res << '\n';
	}
}