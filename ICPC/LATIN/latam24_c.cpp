#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int mul(int a, int b) { return 1LL * a * b % mod; }

auto matmul = [](const auto& a, const auto& b) {
	const int n = a.size();
	vector res(n, vector(n, 0));
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++)
			res[i][j] = add(res[i][j], mul(a[i][k], b[k][j]));
	}
	return res;
};

auto matpow = [](auto x, int k) {
	const int n = x.size();
	vector res(n, vector(n, 0));
	for (int i = 0; i < n; i++) res[i][i] = 1;
	for (; k; k >>= 1) {
		if (k & 1) res = matmul(res, x);
		x = matmul(x, x);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, res = 0; cin >> n >> m;
	vector mat(m, vector(m, 0));
	for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) {
		int g = gcd(i + 1, j + 1);
		if (g == 1) mat[i][j] = 1;
	}
	mat = matpow(mat, n - 1);
	for (int i = 0; i < m; i++) for (int x : mat[i]) res = add(res, x);
	cout << res << '\n';
}